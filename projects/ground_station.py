from dataclasses import dataclass

DATA_LENGTH = 255
ARM_UP = 119          # 'w'
ARM_DOWN = 115        # 's'
HAND_UP = 114         # 'r'
HAND_DOWN = 102       # 'f
UNLOCK =  117          # 'u'
                        # 3/13: change to one on/off bit and one forward/backward bit
FORWARD_UP = 0x3      # 0000 0011
BACKWARD_DOWN  = 0x2   # 0000 0010
PASSWORD = "hello"

@dataclass
class go_car:
    left_side: char
    right_side: char
    ice_hand: char
    lock: char
    checksum: char

def keyboard_io(car, c):
    switcher = {
        KEY_UP: 
    }