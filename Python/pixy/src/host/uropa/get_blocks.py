import serial
import struct
from pixy import *
from ctypes import *
import smbus
import time
# Pixy Python SWIG get blocks example #

print ("Pixy Python SWIG Example -- Get Blocks")
ser = serial.Serial('/dev/ttyACM1', 9600)
#write.timeout(2)
###for RPI version1, use "bus =smbus.SMBus(0)"
##bus = smbus.SMBus(1)
##
###The is the address we setup in the Arduino Program
###Slave Address 1
##address =0x04
##
###Slave Address 2
##address_2 = 0x05

##def writeNumber(value):
##    #bus.write_byte(address, value)
##    bus.write_byte(address_2,value)
##    print('YO')
##    #bus.write_byte_data(address, 0 , value)
##    return -1
##
##def readNumber():
##    #number = bus.read_byte(address)
##    number = bus.read_byte_data(address_2, 1)
##    return number
# Initialize Pixy Interpreter thread #
pixy_init()

class Blocks (Structure):
  _fields_ = [ ("type", c_uint),
               ("signature", c_uint),
               ("x", c_uint),
               ("y", c_uint),
               ("width", c_uint),
               ("height", c_uint),
               ("angle", c_uint) ]

blocks = BlockArray(100)
frame = 0
width = 320.0
height = 200.0
targetHeight = 40.0

# Wait for blocks #
while 1:

  count = pixy_get_blocks(100, blocks)

  if count > 0:
    # Blocks found #
    frame = frame + 1
    if frame % 100 == 0:
      print 'frame %3d:' % (frame)
      for index in range (0, count):
        print '[BLOCK_TYPE=%d SIG=%d X=%3d Y=%3d WIDTH=%3d HEIGHT=%3d]' % (blocks[index].type, blocks[index].signature, blocks[index].x, blocks[index].y, blocks[index].width, blocks[index].height)
        centroidX = blocks[index].x + blocks[index].width /2
        propAcross = centroidX * 1.0 / width
        propBottomDown = (blocks[index].y + blocks[index].height) * 1.0 / height
        turn = 2*propAcross - 1
	turn = max(min(turn, 1.0), -1.0)
        forward = (1-propBottomDown)
	forward = max(min(forward, 1.0), 0.0)
        print 'Turn: %f Forward: %f' % (turn, forward)
	if(forward < 0):
		forward = 0
	leftMotor = 1.0
	rightMotor = 1.0
	if(turn < 0):
		leftMotor = (1 + turn)
	if(turn > 0):
		rightMotor = (1 - turn)
	leftMotor = leftMotor * forward
	rightMotor = rightMotor * forward;
	print 'Left: %f Right: %f' % (leftMotor, rightMotor)
	

	leftInt = int(leftMotor * 100)
	rightInt = int(rightMotor * 100)
	transferInt = 100 * leftInt + rightInt
	transferString = str(transferInt) + "\n"
        ser.write(transferString)    
        print 'Wrote to serial: %s' % (transferString)
	#for index in data_list:
              #Sends to the Slaves
       # time.sleep(0.5)
              
        #writeNumber(int(0x0A))
        
