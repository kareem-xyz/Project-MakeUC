# Arduino Code Setup
import serial
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)

# Reads arudino data continuosly, not sure how this will work in a flask app yet.
def readserial(comport, baudrate):
    ser = serial.Serial(comport, baudrate, timeout=0.1)         # 1/timeout is the frequency at which the port is read

    while True:
        data = ser.readline().decode().strip()
        if data:
            print(data)
            
# Function to read data from the Arduino ONCE
def read_from_arduino():
    if arduino.in_waiting > 0:
        data = arduino.readline().decode('utf-8').strip()  # Read a line and decode it
        return data
    return None