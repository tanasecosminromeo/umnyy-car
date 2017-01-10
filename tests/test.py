import smbus
import time
bus = smbus.SMBus(1)
address = 0x04

#bus.write_byte(address, 245);
# time.sleep(.5);
# bus.write_byte(address, 247);
# time.sleep(.5);
# bus.write_byte(address, 241);
# time.sleep(.5);
# bus.write_byte(address, 247);
# time.sleep(.5);
sleep(10);

while True:
	for xx in [0, 96, 200]:
		for x in range(1+xx, 8+xx):
			print "Test %d" % (x)
			bus.write_byte(address, x)
			time.sleep(1)
			bus.write_byte(address, 0)
			time.sleep(.5)

	bus.write_byte(address, 0)

	for x in range(1, 6):
		try:
			byte = bus.read_byte(address)
			if byte!=0:
				print byte
			time.sleep(1);
		except Exception as e:
			bus = smbus.SMBus(1)
			print e, "not connected"
			pass
