import pygame
import pygame.camera
from PIL import Image, ImageFilter, ImageOps, ImageDraw
import numpy as np
import cv2
import easyocr

# Initialize EasyOCR reader
reader = easyocr.Reader(['en'])

def ocr_cell(cell, force_text_threshold, force_low_text):
    # Convert the cell to grayscale
    gray = cv2.cvtColor(cell, cv2.COLOR_BGR2GRAY)
    
    # Use EasyOCR to perform OCR on the cell image
    results = reader.readtext(gray, detail=0, allowlist=["1", "2", "3", "4", "5", "6", "7", "8", "9"], text_threshold=force_text_threshold, low_text=force_low_text)
    if results and results[0].isdigit() and 1 <= int(results[0]) <= 9:
        return results[0]
    else:
        return ""

def capture_frame(cam):
    frame = cam.get_image()
    frame_array = pygame.surfarray.array3d(frame)
    frame_pil = Image.fromarray(frame_array.transpose((1, 0, 2)))
    return frame_pil

def get_sudoku_grid(frame, output_size=(450, 450)):
    # Convert frame to numpy format
    frame_np = np.array(frame)

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame_np, cv2.COLOR_BGR2GRAY)
    
    # Apply GaussianBlur to the grayscale image
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    
    # Use adaptive thresholding to create a binary image
    thresh = cv2.adaptiveThreshold(blurred, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 11, 2)
    
    # Find contours in the thresholded image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # Sort the contours by area and keep the largest one
    contours = sorted(contours, key=cv2.contourArea, reverse=True)
    
    # Assume the largest contour is the sudoku grid
    sudoku_contour = contours[0]
    
    # Get the perimeter of the contour
    peri = cv2.arcLength(sudoku_contour, True)
    
    # Approximate the contour to get a quadrilateral
    approx = cv2.approxPolyDP(sudoku_contour, 0.02 * peri, True)
    
    # If the approximated contour has 4 points, we can assume it's the sudoku grid
    if len(approx) == 4:
        # Get the points of the quadrilateral
        pts = approx.reshape(4, 2)
        
        # Order the points in a consistent order: top-left, top-right, bottom-right, bottom-left
        rect = np.zeros((4, 2), dtype="float32")
        s = pts.sum(axis=1)
        rect[0] = pts[np.argmin(s)]
        rect[2] = pts[np.argmax(s)]
        diff = np.diff(pts, axis=1)
        rect[1] = pts[np.argmin(diff)]
        rect[3] = pts[np.argmax(diff)]
        
        # Set up the destination points for the perspective transform with consistent output size
        dst = np.array([
            [0, 0],
            [output_size[0] - 1, 0],
            [output_size[0] - 1, output_size[1] - 1],
            [0, output_size[1] - 1]], dtype="float32")
        
        # Apply the perspective transform to get the top-down view of the grid
        M = cv2.getPerspectiveTransform(rect, dst)
        warped = cv2.warpPerspective(frame_np, M, output_size)

        # Convert warped frame back to Pillow format
        warped_pil = Image.fromarray(warped)
        
        return warped_pil
    return None

def cut_cells(grid, cell_size=(50, 50), margin=0):
    # Convert grid to numpy format
    grid_np = np.array(grid)

    # Calculate the size of each cell
    cell_width, cell_height = cell_size
    grid_height, grid_width = grid_np.shape[:2]
    grid_content = [[], [], [], [], [], [], [], [], []]
    
    # Loop through each cell in the grid
    for i in range(9):
        for j in range(9):
            # Calculate the coordinates of the cell
            x = i * cell_height
            y = j * cell_width
            
            # Extract the cell from the grid
            cell = grid_np[y + margin:y + cell_height - margin, x + margin:x + cell_width - margin]
            
            # Read content from the cell
            cell_content = ocr_cell(cell, 0.1, 0.1)
            if cell_content == '':
                int_cell_content = 0
            else:
                int_cell_content = int(ocr_cell(cell, 0.1, 0.1))
            grid_content[j].append(int_cell_content)

    print("\nGrid content:")
    for i in range(0, 9):
        for j in range(0, 9):
            print(str(grid_content[i][j]), end=" ")
        print()

    return grid_content

def main():
    pygame.init()
    pygame.camera.init()

    result = []

    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption("USB Webcam Feed")

    cam_list = pygame.camera.list_cameras()
    if not cam_list:
        raise ValueError("No cameras found.")

    cam = pygame.camera.Camera(cam_list[0], (640, 480))
    cam.start()

    running = True
    while running:
        frame = capture_frame(cam)
        grid = get_sudoku_grid(frame)

        frame_surface = pygame.image.frombuffer(frame.tobytes(), frame.size, frame.mode)
        screen.blit(frame_surface, (0, 0))

        if grid is not None:
            grid_surface = pygame.image.frombuffer(grid.tobytes(), grid.size, grid.mode)
            screen.blit(grid_surface, (0, 0))

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_q):
                running = False
            if event.type == pygame.KEYDOWN and event.key == pygame.K_p:
                result = cut_cells(grid, margin=8)
                user_input = input("Is the grid correct?\nEnter/y/yes = yes, other = no\n")
                if user_input == "" or user_input == "y" or user_input == "yes":
                    running = False

    cam.stop()
    pygame.quit()

    return result
