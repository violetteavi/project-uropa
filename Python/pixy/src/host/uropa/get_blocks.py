from pixy import *
from ctypes import *

# Pixy Python SWIG get blocks example #

print ("Pixy Python SWIG Example -- Get Blocks")

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
        turn = 2 * propAcross - 1
        forward = 2*(1-propBottomDown) - 1
        print 'Turn: %f Forward: %f' % (turn, forward)
