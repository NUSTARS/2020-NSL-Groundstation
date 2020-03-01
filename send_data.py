import serial
import time

port = "COM4"
baud = 9600

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
    if is_connected:
        ser.write(data)

def recv_data(ser):
    data = ""
    if is_connected:
        ser.read(data)
    else:
        return None
    return data

def main():
    
    while(not connect(port, baud)):
        time.sleep(5)
        print("Trying to Connect")
    
    while(True):
        send_data(ser, data)
        recv_data(ser)
    print("Connected.")
    



if __name__== "__main__":
    main()