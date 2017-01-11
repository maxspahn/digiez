#!/usr/bin/sh


echo "Executing false Image detection"


ffmpeg -i ~/Videos/natureCut.mkv -vf fps=24 ~/Pictures/video/images/out%d.bmp


cd ~/Pictures/video
./d 10

ffmpeg -r 24 -f image2 -i ~/Pictures/video/images/new%03d.bmp -vcodec libx265 -crf 25  -pix_fmt yuv420p ~/Videos/test.mp4


rm ~/Pictures/video/images/new*
rm ~/Pictures/video/images/out*

