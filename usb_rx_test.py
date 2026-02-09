import serial
import time

PORT = "COM11"
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=1)

# ESP32 resets when the port opens
time.sleep(2)

print(f"Listening on {PORT} at {BAUD} baud...")

try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline()   # read until \n
            print("RAW:", data)
            try:
                print("TEXT:", data.decode("utf-8", errors="replace").rstrip())
            except Exception as e:
                print("DECODE ERROR:", e)
except KeyboardInterrupt:
    print("\nStopped by user")
finally:
    ser.close()
