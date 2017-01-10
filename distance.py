import smbus
import time
bus = smbus.SMBus(1)

address = 0x03
control = 0x04

cm = 0
i  = 0
ll = 0

while True:
	try:
		byte = bus.read_byte(address)
		if byte!=0:
			if i<10:
				i = i + 1
				if byte!=cm:
					cm = byte
					print "distance ", cm
					f = open('code/distance.txt', 'w')
					f.write(str(cm))
					f.close()
			if ll<8 and byte<8:
				bus.write_byte(control, 247)
				time.sleep(.2)
				bus.write_byte(control, 0)
				
			ll = byte
		time.sleep(.01);
	except Exception as e:
		bus = smbus.SMBus(1)
		print e, "not connected"
		pass
