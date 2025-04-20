from serial.tools import list_ports

import pydobot
import math

digit_scale = 2
sudoku_side = 72
uplift_pen_height = 20
round_step = 5

def do_round(device, pos1x, pos1y, pos2x, pos2y, z, r, steps=50, outward=True):
    diffX = pos2x - pos1x
    diffY = pos2y - pos1y
    dist = math.sqrt(diffX**2 + diffY**2)
    radius = dist / 2
    offset_factor = 1 if outward else -1
    centerX = (pos1x + pos2x) / 2 - offset_factor * (diffY / dist) * radius
    centerY = (pos1y + pos2y) / 2 + offset_factor * (diffX / dist) * radius
    start_angle = math.atan2(pos1y - centerY, pos1x - centerX)
    end_angle = math.atan2(pos2y - centerY, pos2x - centerX)

    if outward:
        while end_angle < start_angle:
            end_angle += 2 * math.pi
    else:
        while start_angle < end_angle:
            start_angle += 2 * math.pi
    
    for step in range(steps + 1):
        angle = start_angle + (end_angle - start_angle) * (step / steps)
        x = centerX + (math.sqrt(2) * radius * math.cos(angle))
        y = centerY + (math.sqrt(2) * radius * math.sin(angle))
        device.move_to(x, y, z, r, False)
    

def do_one():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # Go to first point
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z, r, True)
    
    # Number 1
    device.move_to(x + 3 * digit_scale, y, z, r, False)
    device.move_to(x, y, z, r, False)
    device.move_to(x, y - digit_scale, z, r, False)
    device.move_to(x, y + digit_scale, z, r, False)

    # Return to base point
    device.move_to(x, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_two():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # Go to first point
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z, r, True)
    
    # Number 2
    do_round(device, x + 2 * digit_scale, y + digit_scale, x + 3 * digit_scale, y, z, r, round_step, False)
    do_round(device, x + 3 * digit_scale, y, x + 2 * digit_scale, y - digit_scale, z, r, round_step, False)
    device.move_to(x, y + digit_scale, z, r, False)
    device.move_to(x, y - digit_scale, z, r, False)

    # Return to base point
    device.move_to(x, y - digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_three():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # Go to first point
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x + 3 * digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x + 3 * digit_scale, y + digit_scale, z, r, True)
    
    # Number 3
    device.move_to(x + 3 * digit_scale, y - digit_scale, z, r, False)
    device.move_to(x + 2 * digit_scale, y, z, r, False)
    do_round(device, x + 2 * digit_scale, y, x + digit_scale, y - digit_scale, z, r, round_step, False)
    do_round(device, x + digit_scale, y - digit_scale, x, y, z, r, round_step, False)
    do_round(device, x, y, x + digit_scale, y + digit_scale, z, r, round_step, False)

    # Return to base point
    device.move_to(x + digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_four():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # First point useless. Already there

    # Number 4
    device.move_to(x + 3 * digit_scale, y, z, r, False)
    device.move_to(x + digit_scale, y + digit_scale, z, r, False)
    device.move_to(x + digit_scale, y - digit_scale, z, r, False)

    # Return to base point
    device.move_to(x + digit_scale, y - digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_five():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # Go to first point
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x + 3 * digit_scale, y - digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x + 3 * digit_scale, y - digit_scale, z, r, True)
    
    # Number 5
    device.move_to(x + 3 * digit_scale, y + digit_scale, z, r, False)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z, r, False)
    device.move_to(x + 2 * digit_scale, y, z, r, False)
    do_round(device, x + 2 * digit_scale, y, x + digit_scale, y - digit_scale, z, r, round_step, False)
    do_round(device, x + digit_scale, y - digit_scale, x, y, z, r, round_step, False)
    device.move_to(x, y + digit_scale, z, r, False)

    # Return to base point
    device.move_to(x, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_six():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # Go to first point
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x + 3 * digit_scale, y - digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x + 3 * digit_scale, y - digit_scale, z, r, True)
    
    # Number 6
    device.move_to(x + 3 * digit_scale, y, z, r, True)
    do_round(device, x + 3 * digit_scale, y, x + 2 * digit_scale, y + digit_scale, z, r, round_step, True)
    device.move_to(x + digit_scale, y + digit_scale, z, r, True)
    do_round(device, x + digit_scale, y + digit_scale, x, y, z, r, round_step, True)
    do_round(device, x, y, x + digit_scale, y - digit_scale, z, r, round_step, True)
    do_round(device, x + digit_scale, y - digit_scale, x + 2 * digit_scale, y, z, r, round_step, True)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z, r, False)

    # Return to base point
    device.move_to(x + 2 * digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_seven():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # First point useless. Already there

    # Number 7
    device.move_to(x + 3 * digit_scale, y - digit_scale, z, r, False)
    device.move_to(x + 3 * digit_scale, y + digit_scale, z, r, False)
    device.move_to(x + 2.5 * digit_scale, y + digit_scale, z, r, False)

    # Return to base point
    device.move_to(x + 2.5 * digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_eight():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # First point useless. Already there

    # Number 8
    do_round(device, x, y, x + digit_scale, y - digit_scale, z, r, round_step, True)
    device.move_to(x + 2 * digit_scale, y + digit_scale, z, r, True)
    do_round(device, x + 2 * digit_scale, y + digit_scale, x + 3 * digit_scale, y, z, r, round_step, False)
    do_round(device, x + 3 * digit_scale, y, x + 2 * digit_scale, y - digit_scale, z, r, round_step, False)
    device.move_to(x + digit_scale, y + digit_scale, z, r, True)
    do_round(device, x + digit_scale, y + digit_scale, x, y, z, r, round_step, True)

    # Return useless. Already there

def do_nine():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # Go to first point
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x + 2 * digit_scale, y - digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x + 2 * digit_scale, y - digit_scale, z, r, True)
    
    # Number 9
    do_round(device, x + 2 * digit_scale, y - digit_scale, x + digit_scale, y, z, r, round_step, False)
    do_round(device, x + digit_scale, y, x + 2 * digit_scale, y + digit_scale, z, r, round_step, False)
    do_round(device, x + 2 * digit_scale, y + digit_scale, x + 3 * digit_scale, y, z, r, round_step, False)
    do_round(device, x + 3 * digit_scale, y, x + 2 * digit_scale, y - digit_scale, z, r, round_step, False)
    device.move_to(x + digit_scale, y - digit_scale, z, r, False)
    do_round(device, x + digit_scale, y - digit_scale, x, y, z, r, round_step, False)
    do_round(device, x, y, x + digit_scale, y + digit_scale, z, r, round_step, False)

    # Return to base point
    device.move_to(x + digit_scale, y + digit_scale, z + uplift_pen_height, r, False)
    device.move_to(x, y, z + uplift_pen_height, r, False)
    device.move_to(x, y, z , r, True)

def do_zero():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    # First point useless. Already there

    # Number 0
    do_round(device, x, y, x + digit_scale, y - digit_scale, z, r, round_step, True)
    device.move_to(x + 2 * digit_scale, y - digit_scale, z, r, True)
    do_round(device, x + 2 * digit_scale, y - digit_scale, x + 3 * digit_scale, y, z, r, round_step, True)
    do_round(device, x + 3 * digit_scale, y, x + 2 * digit_scale, y + digit_scale, z, r, round_step, True)
    device.move_to(x + digit_scale, y + digit_scale, z, r, True)
    do_round(device, x + digit_scale, y + digit_scale, x, y, z, r, round_step, True)

    # Return useless. Already there

def print_number(nb):
    for i in range (len(nb)):
        print(i)
        print(nb[i])
        match (nb[i]):
            case '1':
                do_one();
            case '2':
                do_two();
            case '3':
                do_three();
            case '4':
                do_four();
            case '5':
                do_five();
            case '6':
                do_six();
            case '7':
                do_seven();
            case '8':
                do_eight();
            case '9':
                do_nine();
            case _:
                do_zero();
        next_number()



def next_number():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()

    device.move_to(x, y, z + uplift_pen_height , r, False)
    device.move_to(x, y - 3 * digit_scale, z + uplift_pen_height , r, False)
    device.move_to(x, y - 3 * digit_scale, z , r, True)

def go_to_box(origin_x, origin_y, x, y):
    (act_x, act_y, z, r, j1, j2, j3, j4) = device.pose()
    device.move_to(act_x, act_y, z + uplift_pen_height , r, True)
    device.move_to(origin_x + 4 * digit_scale * x, origin_y + 4 * digit_scale * y, z + uplift_pen_height , r, False)
    device.move_to(origin_x + 4 * digit_scale * x, origin_y + 4 * digit_scale * y, z , r, False)

def draw_box():
    (x, y, z, r, j1, j2, j3, j4) = device.pose()
    print(f'x:{x} y:{y}')
    device.move_to(x, y + sudoku_side, z, r, True)
    print(f'x:{device.pose()[0]} y:{device.pose()[1]}')
    device.move_to(x + sudoku_side, y + sudoku_side, z, r, True)
    print(f'x:{device.pose()[0]} y:{device.pose()[1]}')
    device.move_to(x + sudoku_side, y, z, r, True)
    print(f'x:{device.pose()[0]} y:{device.pose()[1]}')
    device.move_to(x, y, z, r, True)

available_ports = list_ports.comports()
print(f'available ports: {[x.device for x in available_ports]}')
if (len(available_ports) == 0):
    print("Branche le câble Troudbal !")
    exit()
port = available_ports[0].device

device = pydobot.Dobot(port=port, verbose=False)

(x, y, z, r, j1, j2, j3, j4) = device.pose()



device.speed(500, 500)


draw_box()


device.close()