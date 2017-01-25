#!/usr/bin/sh
video = $1

echo "Compiling false Image detection"
g++ -o d digiez.cpp EasyBMP.cpp



ffmpeg -i "$1" -vf fps=25 ./images/out%d.bmp

echo "counting photos"
numfiles=$(ls ./images -a | wc -l)
echo $numfiles

echo "Finding and move bad images"
./d 10 $numfiles

ffmpeg -r 25 -f image2 -i ./images/new%03d.bmp -vcodec libx265 -crf 25  -pix_fmt yuv420p ./Corrected.mkv


rm ./images/new*

