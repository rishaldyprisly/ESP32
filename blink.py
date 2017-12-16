import machine
import time

led = machine.Pin(5, machine.Pin.OUT)

while True:
	led(0)
	time.sleep(0.5)
	led(1)
	time.sleep(0.5)
