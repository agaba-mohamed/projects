from serial.tools import list_ports
dType.GetHOMEParams(api)
k = 5
uplift_pen_height = 20

def get_pose():
    pose = dType.GetPose(api)
    x, y, z, r = pose[0], pose[1], pose[2], pose[3]
    return x, y, z, r

def do_one(offset_x=0, offset_y=0):
    x, y, z, r = get_pose()
    x += offset_x
    y += offset_y

    # Aller au premier point
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 2 * k, y + k, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 2 * k, y + k, z, r, False)

    # Tracer le numéro 1
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 3 * k, y, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y - k, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y + k, z, r, False)

    # Retourner au point de base
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y + k, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z, r, True)

def do_four(offset_x=0, offset_y=0):
    x, y, z, r = get_pose()
    x += offset_x
    y += offset_y

    # Tracer le numéro 4
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 3 * k, y, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + k, y + k, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + k, y - k, z, r, False)

    # Retourner au point de base
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + k, y - k, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z, r, True)

def do_seven(offset_x=0, offset_y=0):
    x, y, z, r = get_pose()
    x += offset_x
    y += offset_y

    # Tracer le numéro 7
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 3 * k, y - k, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 3 * k, y + k, z, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 2.5 * k, y + k, z, r, False)

    # Retourner au point de base
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x + 2.5 * k, y + k, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z, r, True)

def next_number(offset_x=0, offset_y=0):
    x, y, z, r = get_pose()
    x += offset_x
    y += offset_y

    # Déplacer pour l'espacement entre les chiffres
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y - 3 * k, z + uplift_pen_height, r, False)
    dType.SetPTPCmd(api, dType.PTPMode.PTPMOVLXYZMode, x, y - 3 * k, z, r, True)

# Exécuter les fonctions avec des offsets appropriés
do_one()
next_number()
do_four(offset_y=-3 * k)
