import smbus
import time
bus = smbus.SMBus(1)
address = 0x04

humidity = 0
temperature = 0

while True:
	#  bus.write_byte(address, 248)
	try:
		byte = bus.read_byte(address)
		print byte
		if byte!=0 and byte<200:
			if byte>101:
				if (byte-101!=temperature):
					temperature = byte-101
					print "Temperature ", temperature
					f = open('code/temperature.txt', 'w')
					f.write(str(temperature))
					f.close()
			else:
				if (byte!=humidity):
					humidity = byte
					print "Humidity ", humidity
					f = open('code/humidity.txt', 'w')
					f.write(str(humidity))
					f.close()
		time.sleep(1);
	except Exception as e:
		bus = smbus.SMBus(1)
		print e, "not connected"
		pass
