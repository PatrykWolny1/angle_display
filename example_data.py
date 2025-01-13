import serial
ser = serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=1)
ser.write(b"\x3E\x56\x00\x56")  # CMD_BOARD_INFO
response = ser.read(1024)
print(f"Response: {response}")
ser.close()
