import cv2
import numpy as np
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

def get_sudoku_grid(frame, output_size=(450, 450)):
    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
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
        warped = cv2.warpPerspective(frame, M, output_size)
        
        return warped
    return None

def print_grid(grid_content):
    cell_size = max([len(cell_content) for cell_content in grid_content])
    print("-" * (9 * cell_size + 8))
    for i in range(8):
        for j in range(8):
            print(str(grid_content[j * 9 + i]).ljust(cell_size), end = "|")
        print(str(grid_content[8 * 9 + i]).ljust(cell_size))
        for j in range(8):
            print("-" * cell_size, end = ".")
        print("-" * cell_size)
    for j in range(8):
        print(str(grid_content[j * 9 + 8]).ljust(cell_size), end = "|")
    print(str(grid_content[8 * 9 + 8]).ljust(cell_size))
    print("-" * (9 * cell_size + 8))

def cut_cells(grid, cell_size=(50, 50), margin=0):
    # Calculate the size of each cell
    cell_width, cell_height = cell_size
    grid_height, grid_width = grid.shape[:2]
    grid_content = []
    
    # Loop through each cell in the grid
    for i in range(9):
        for j in range(9):
            # Calculate the coordinates of the cell
            x = i * cell_height
            y = j * cell_width
            
            # Extract the cell from the grid
            cell = grid[y + margin:y + cell_height - margin, x + margin:x + cell_width - margin]
            
            # Display the cell
            cv2.imshow(f"Cell {i * 9 + j}", cell)
            cv2.waitKey(1)  # Display each cell for 1 ms

            # Read content from the cell
            grid_content.append(ocr_cell(cell, 0.1, 0.1))
    # Print the grid content
    print_grid(grid_content)

def main():
    # Initialize the webcam
    ncam = 0
    cap = cv2.VideoCapture(0)

    while True:
        # Read a frame from the webcam
        ret, frame = cap.read()
        if not ret:
            break
        
        # Get the sudoku grid from the frame
        grid = get_sudoku_grid(frame)
        
        if grid is not None:
            # Display the grid
            cv2.imshow("Sudoku Grid", grid)
            
            # Display the individual cells if the user presses 'p'
            if cv2.waitKey(1) & 0xFF == ord('p'):
                cut_cells(grid, margin=8)
        
        # Display the original frame
        cv2.imshow("Webcam Feed", frame)
        
        # Break the loop if the user presses 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # Switch camera if the user presses 'c'
        if cv2.waitKey(1) & 0xFF == ord('c'):
            ncam += 1
            try:
                cap = cv2.VideoCapture(ncam)
            except:
                cv2.VideoCapture(0)
                ncam = 0

    # Release the webcam and close all OpenCV windows
    cap.release()
    cv2.destroyAllWindows()

main()
