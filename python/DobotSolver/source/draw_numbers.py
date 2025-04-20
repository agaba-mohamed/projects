from serial.tools import list_ports
import pydobot
import numpy as np
import time

PEN_UP_DISTANCE = 20

class Point:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y, self.z - other.z)

    def __mul__(self, scalar):
        return Point(self.x * scalar, self.y * scalar, self.z * scalar)

    def __truediv__(self, scalar):
        return Point(self.x / scalar, self.y / scalar, self.z / scalar)
    
    def __eq__(self, other):
        if isinstance(other, Point):
            return self.x == other.x and self.y == other.y and self.z == other.z
        return False

    def __repr__(self):
        return f"Point({self.x}, {self.y}, {self.z})"
    
    def to_list(self):
        return [self.x, self.y, self.z]

def get_grid_coordinates(top_left: Point, bottom_right: Point, z):
    x1 = top_left.x
    y1 = top_left.y
    x3 = bottom_right.x
    y3 = bottom_right.y

    xc = (x1 + x3)/2
    yc = (y1 + y3)/2
    xd = (x1 - x3)/2
    yd = (y1 - y3)/2

    x2 = xc - yd
    y2 = yc + xd
    x4 = xc + yd
    y4 = yc - xd

    point1 = Point(x1, y1, z)
    point3 = Point(x3, y3, z)
    point2 = Point(x2, y2, z)
    point4 = Point(x4, y4, z)

    return [point1, point2, point3, point4]

def get_cell_coordinates(grid, x, y):
    point1, point2, point3, point4 = grid
    grid_v_axis = point2 - point1
    grid_h_axis = point4 - point1
    cell_v_axis = grid_v_axis / 9
    cell_h_axis = grid_h_axis / 9
    return [point1 + cell_h_axis * x + cell_v_axis * y,
            point1 + cell_h_axis * x + cell_v_axis * (y + 1),
            point1 + cell_h_axis * (x + 1) + cell_v_axis * (y + 1),
            point1 + cell_h_axis * (x + 1) + cell_v_axis * y]

def get_current_position(device):
    x, y, z = device.pose()[:3]
    return Point(x, y, z)

def wait_until_done(device):
    old_pos = None
    new_pos = get_current_position(device)
    while new_pos != old_pos:
        time.sleep(0.1)
        old_pos = new_pos
        new_pos = get_current_position(device)

def get_square_coordinates(z):
    return [Point(180.0, -20.0, z),
        Point(220.0, -20.0, z),
        Point(220.0, 20.0, z),
        Point(180.0, 20.0, z)]

def get_number_1_coordinates(z):
    return [Point(200.0094, -14.0684, z),
        Point(187.8773, -2.0831, z),
        Point(212.233, -2.0831, z),
        Point(212.233, -9.4412, z),
        Point(212.233, 6.3906, z)]
    
def get_number_2_coordinates(z):
        return [Point(196.9082, -14.4904, z),
        Point(186.168, -1.5481, z),
        Point(196.2, 11.1614, z),
        Point(209.7234, -10.2786, z),
        Point(209.7234, 9.4506, z)]
        
def get_number_3_coordinates(z):
    return [Point(192.7664, -14.0065, z),
        Point(187.1917, -2.2485, z),
        Point(191.5306, 9.9195, z),
        Point(200.4166, -2.3148, z),
        Point(205.0922, 11.192, z),
        Point(212.5275, -1.3745, z),
        Point(207.3003, -12.7536, z)]
    
def get_number_4_coordinates(z):
    return [Point(187.8427, -3.3848, z),
        Point(204.9444, -13.7496, z),
        Point(204.9444, 3.0326, z),
        Point(212.5227, 3.0326, z)]

def get_number_5_coordinates(z):
    return [Point(188.306, 7.7472, z),
        Point(188.306, -11.4908, z),
        Point(200.3629, -11.4908, z),
        Point(196.0419, 7.8841, z),
        Point(209.7682, 8.8244, z),
        Point(208.6757, -12.3545, z)]

def get_number_6_coordinates(z):
    return [Point(189.0918, 5.5054, z),
        Point(195.1139, -12.0039, z),
        Point(209.9619, -12.0039, z),
        Point(212.6265, 6.6822, z),
        Point(201.7165, 6.5259, z),
        Point(203.1594, -11.8395, z)]
    
def get_number_7_coordinates(z):
    return [Point(189.4846, -13.3281, z),
        Point(189.4846, 6.147, z),
        Point(214.0704, -7.9155, z)]

def get_number_8_coordinates(z):
    return [Point(185.7417, -1.8878, z),
        Point(194.6328, 12.6065, z),
        Point(207.8197, -15.1003, z),
        Point(215.9033, -1.5958, z),
        Point(207.7745, 11.8198, z),
        Point(195.599, -14.4849, z),
        Point(185.7417, -1.8878, z)]

def get_number_9_coordinates(z):
    return [Point(202.2862, 6.1702, z),
        Point(203.7361, -15.1821, z),
        Point(187.3533, -13.0912, z),
        Point(188.8855, 5.15, z),
        Point(214.948, 5.8606, z),
        Point(214.7146, -12.3139, z)]

def transform_coordinates(reference_coords, old_square, new_square, z):
    # Convert points to homogeneous coordinates
    ref_points = np.array([[p.x, p.y, 1] for p in reference_coords])
    old_points = np.array([[p.x, p.y, 1] for p in old_square])
    new_points = np.array([[p.x, p.y, 1] for p in new_square])

    # Ensure old_points and new_points have compatible dimensions
    if old_points.shape != new_points.shape:
        raise ValueError("old_square and new_square must have the same number of points")

    # Calculate the transformation matrix from old_square to new_square
    A, _, _, _ = np.linalg.lstsq(old_points, new_points, rcond=None)
    new_coords = ref_points @ A

    # Convert back to 2D coordinates
    new_coords = [Point(p[0], p[1], z) for p in new_coords[:, :2]]

    return new_coords

def draw_number(n, x, y, grid_points, device):
    z = grid_points[0].z
    cell_points = get_cell_coordinates(grid_points, x, y)
    match (n):
        case 1:
            number_points = transform_coordinates(get_number_1_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 2:
            number_points = transform_coordinates(get_number_2_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 3:
            number_points = transform_coordinates(get_number_3_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 4:
            number_points = transform_coordinates(get_number_4_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 5:
            number_points = transform_coordinates(get_number_5_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 6:
            number_points = transform_coordinates(get_number_6_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 7:
            number_points = transform_coordinates(get_number_7_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 8:
            number_points = transform_coordinates(get_number_8_coordinates(z), get_square_coordinates(z), cell_points, z)
        case 9:
            number_points = transform_coordinates(get_number_9_coordinates(z), get_square_coordinates(z), cell_points, z)
        case _:
            number_points = []

    wait_until_done(device)
    curr_point = get_current_position(device)
    if number_points != []:
        device.move_to(*((curr_point + Point(0, 0, PEN_UP_DISTANCE)).to_list()), True)
        time.sleep(0.1)
        device.move_to(*((number_points[0] + Point(0, 0, PEN_UP_DISTANCE)).to_list()), True)
        time.sleep(0.1)
    for point in number_points:
        device.move_to(*(point.to_list()), True)
        time.sleep(0.1)

def main(grid_numbers):
    available_ports = list_ports.comports()
    print(f'Available ports: {[x.device for x in available_ports]}')
    if (len(available_ports) == 0):
        print("No cable detected")
        exit()
    port = available_ports[0].device

    device = pydobot.Dobot(port=port, verbose=False)

    device.speed(1000, 1000)

    # Wait for user to press Enter
    input("Move the robot arm to the top left corner of the square and press Enter...")
    top_left = get_current_position(device)
    print(f"Top left corner set to: {top_left}")

    input("Move the robot arm to the bottom right corner of the square and press Enter...")
    bottom_right = get_current_position(device)
    print(f"Bottom right corner set to: {bottom_right}")

    # Define the points of the square
    grid_points = get_grid_coordinates(top_left, bottom_right, (top_left.z + bottom_right.z) / 2)

    # Draw every missing number on the grid
    col_num = 0
    row_num = 0
    for col in grid_numbers:
        for num in col:
            if num > 0 and num < 10:
                draw_number(num, row_num, col_num, grid_points, device)
            row_num += 1
        col_num += 1
        row_num = 0
    col_num = 0

    curr_point = get_current_position(device)
    device.move_to(*((curr_point + Point(0, 0, PEN_UP_DISTANCE + 50)).to_list()), True)

    device.close()
