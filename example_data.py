import serial
import time

def send_command(ser, command):
    """Send a command and read the response."""
    ser.flushInput()  # Clear the input buffer
    ser.write(command.encode('latin-1'))  # Send command
    time.sleep(0.2)  # Wait for the response
    response = ser.read(1024)  # Read up to 1024 bytes
    print(f"Sent: {command}")
    if response:
        print(f"Received: {response.hex()}")
        parse_response(response)
    else:
        print("No data received.")

def parse_response(response):
    """Parse the response from the device."""
    if len(response) < 4:
        print("Incomplete response")
        return

    # Parse header
    header = response[0]
    cmd_id = response[1]
    data_size = response[2]
    header_checksum = response[3]

    # Validate header
    if header != 0x3E or (cmd_id + data_size) % 256 != header_checksum:
        print("Invalid header or checksum")
        return

    # Parse payload
    payload = response[4:-1]  # Exclude the last byte (body checksum)
    body_checksum = response[-1]

    # Validate body checksum
    if sum(payload) % 256 != body_checksum:
        print("Invalid body checksum")
        return

    # Handle the payload
    print(f"Payload: {payload.hex()}")

# Open serial connection
ser = serial.Serial('/dev/ttyACM0', baudrate=115200, parity=serial.PARITY_EVEN, timeout=1)

# Send CMD_READ_PARAMS command
send_command(ser, "\x3E\x52\x01\x53\x01\x01")  # CMD_READ_PARAMS for Profile 1
# CMD_BOARD_INFO command
send_command(ser, "\x3E\x56\x00\x56")  # > V 0x00 0x56

# Close serial connection
ser.close()
