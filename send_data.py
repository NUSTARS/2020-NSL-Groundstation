import serial
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


def main():
    ser = connect(port, baud)
    while(not ser):
        time.sleep(5)
        ser = connect(port, baud)
        print("Trying to Connect")
    
    while(True):
        if not correct_pw:
            req_pw(ser)
            pw_resp = recv_data(ser)
            if pw_resp == password:
                correct_pw = 1

        else:
            # TODO: hook up API and make controller_inputs get the information for how to control the robot
            controller_inputs = "temp data"
            send_data(ser, controller_inputs)
            controller_resp = recv_data(ser)
        time.sleep(2)
    print("Connected")
    



if __name__== "__main__":
    main()