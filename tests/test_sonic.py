import smbus
import time
bus = smbus.SMBus(1)
address = 0x03

#bus.write_byte(address, 1); #no sound
bus.write_byte(address, 2); #with sound

while True:
	try:
		byte = bus.read_byte(address)
		if byte!=0:
			print byte
		time.sleep(1);
	except Exception as e:
		bus = smbus.SMBus(1)
		print e, "not connected"
		pass
