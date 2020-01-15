#!/bin/sh
# launcher.sh
# navigate to home directory, then to this directory, then execute python script, then back home

cd /
cd /home/pi/Documents/SeniorDesign/project-uropa/Python/pixy/build/uropa
sudo python get_blocks.py
cd /