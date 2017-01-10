import smbus
import time
bus = smbus.SMBus(1)
address = 0x03

distance = 0

while True:
	try:
		byte = bus.read_byte(address)
		if byte!=0:
			if byte!=distance:
				distance = byte
				print "distance ", distance
				f = open('code/distance.txt', 'w')
				f.write(str(distance))
				f.close()
		time.sleep(.1);
	except Exception as e:
		bus = smbus.SMBus(1)
		print e, "not connected"
		pass
