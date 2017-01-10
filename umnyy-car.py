from SimpleWebSocketServer import SimpleWebSocketServer, WebSocket
import smbus
import time
import threading

bus = smbus.SMBus(1)
control = 0x04
distance = 0x03

#def stopit():
#  threading.Timer(1, stopit).start()
#  bus.write_byte(control, 0)
#stopit()

class SimpleEcho(WebSocket):

    def handleMessage(self):
		d = int(self.data)
		if d==38:
			bus.write_byte(control, 242)
		
		if d==40:
			bus.write_byte(control, 247)
				
		if d==37:
			bus.write_byte(control, 244)
			
		if d==39:
			bus.write_byte(control, 245)
			
		if d==18:
			bus.write_byte(control, 0)
			
		if d==1:
			bus.write_byte(distance, 1); #No sound
			
		if d==2:
			bus.write_byte(distance, 2); #With Sound
    #self.sendMessage(self.data)

    def handleConnected(self):
        print self.address, 'connected'

    def handleClose(self):
        print self.address, 'closed'

server = SimpleWebSocketServer('', 8000, SimpleEcho)
server.serveforever()
