class PixyReader 
{ 
    public: 
    float propUp = 0;
    float propAcross = 0;
    float maxBound = 0;
    // reads the bounding boxes from the pixy
    // selects the biggest, and updates the public values
    void updatePixyVals(); 
}; 
