#!/bin/bash

echo
echo "vortex"
echo "by ShadowNetter"
echo
echo "cloning into repo..."
git clone https://github.com/ShadowNetter-Official/vortex
cd vortex
echo "done"
echo "installing..."
cd src
gcc -o vortex main.c cs50.c -lcrypt -lm
sudo cp vortex /bin/
echo
echo "done"
echo
echo "to uninstall do: "
echo "sudo rm /bin/vortex"
echo
