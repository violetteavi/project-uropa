#include "PixyReader.h"

PixyReader::PixyReader()
{
  pixy.init();
}

bool PixyReader::updatePixyVals()
{
  uint16_t blocksRead = pixy.getBlocks();
  if(blocksRead > 0)
  {
    // find the largest block
    int largestBlockIndex = getLargestBlockIndex(blocksRead);
    latestBlock = pixy.blocks[largestBlockIndex];
    updatePixyValsBasedOnBlock(largestBlockIndex);
    updatesSinceLastSuccess = 0;
    return true;
  }
  else
  {
    updatesSinceLastSuccess++;
    return false;
  }
}

int PixyReader::getLargestBlockIndex(int blocksRead)
{
  int largestBlockIndex = 0;
  int maxDim = max(pixy.blocks[0].width, pixy.blocks[0].height);
  for (int j=1; j<blocksRead; j++)
  {
    int maxDimHere = max(pixy.blocks[j].width, pixy.blocks[j].height);
    if(maxDimHere > maxDim)
    {
      largestBlockIndex = j;
      maxDim = maxDimHere;
    }
  }
  return largestBlockIndex;
}

void PixyReader::updatePixyValsBasedOnBlock(int index)
{
  float centroidX = pixy.blocks[index].x;
  propAcross = centroidX / frameWidth;
  propAcross = max(0, min(1, propAcross));
  float centroidY = pixy.blocks[index].y;
  propDown = centroidY / frameHeight;
  propDown = max(0, min(1, propDown));
  maxBound = max(pixy.blocks[index].width, pixy.blocks[index].height);
}

