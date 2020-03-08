import serial
import sys
import time

port = "COM4"
baud = 9600
correct_pw = 0
password = "hello"

def connect(port, baud):
    try:
       ser = serial.Serial(port, baud, timeout=1)
       print("Connection established")
       return ser
    except:
        print("No Connection Established") 
        return 0

def is_connected(ser):
    try:
        ser.open()
        print("it is open")
        return 1
    except serial.SerialException:
        print("not open")
        return 0

def send_data(ser, data):
    if is_connected(ser):
        ser.write(data)

def recv_data(ser):
    data = ""
    if is_connected:
        ser.read(data)
    else:
        return None
    return data

def req_pw(ser):
    data = "Password Check"
    if is_connected(ser):
        ser.write(data)

# def main():
#     print("Yay")
#     ser = connect(port, baud)
#     while(not ser):
#         time.sleep(5)
#         ser = connect(port, baud)
#         print("Trying to Connect")
    
#     # while(True):
#     #     if not correct_pw:
#     #         req_pw(ser)
#     #         pw_resp = recv_data(ser)
#     #         if pw_resp == password:
#     #             correct_pw = 1

#     #     else:
#             # TODO: hook up with C++ and set controller_inputs to transmitted data from c++
#     controller_inputs = "hello"
#     send_data(ser, controller_inputs)
#     controller_resp = recv_data(ser)
#     time.sleep(2)
#     print("Connected")
def run_func(left_side, right_side, lift_arm, ice_hand, lock):
    print("run_func")
    print("Yay!")
    ser = connect(port, baud)

    # while(not ser):
    #     # time.sleep(1)
    #     ser = connect(port, baud)
    #     print("Trying to Connect")

    # controller_inputs = "hello"
    # send_data(ser, controller_inputs)
    # controller_resp = recv_data(ser)
    # time.sleep(2)
    # print("Connected")
    
def test_func():
    
    print("run_func")
    print("Yay!")
    ser = connect(port, baud)
    x = 0
    while(not ser):
        # time.sleep(1)
        ser = connect(port, baud)
        print("Trying to Connect")
        x +=1
        if(x>5):
            break

    controller_inputs = "hello"
    send_data(ser, controller_inputs)
    controller_resp = recv_data(ser)
    # time.sleep(2)
    print("Connected")

# def check_password():

    

# print("Yay!")
# ser = connect(port, baud)

# while(not ser):
#     # time.sleep(1)
#     ser = connect(port, baud)
#     print("Trying to Connect")

# controller_inputs = "hello"
# send_data(ser, controller_inputs)
# controller_resp = recv_data(ser)
# # time.sleep(2)
# print("Connected")
    


# if __name__== "__main__":
#     print("Executing!")
#     main()