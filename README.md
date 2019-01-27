# image-fold


Goal of the project is to create a "fully focused" image based 
on multiple pictures with different focus points. 

Dataset can be obtained from [here](grail.cs.washington.edu/projects/photomontage/data/bug.zip "Dataset"). 

## Complilation

Project can be compiled both with CMake and Make. Unfortunately *dlib* requires 
CMake to have exact location of dlib library, so please be aware of that 
(and change it adequatly in `CMakeList.txt` after downloading).
There is also a backup Makefile located in folder `backup_makefile` if CMake doesn't cooperate.

Project requires: `dlib`, `threads` libraries and `C++14`

## Running

Simply run executable file `transform`. As the result it will produce 
two _png_ images: **_focused_image.png_** and **_depth_map.png_**.

## Dataset

Example images with different focus points:
![alt text](https://imgur.com/a/vSucvHO)

![alt text](https://imgur.com/a/qi7W7NK)

## My result

Focused image
![alt text](https://imgur.com/a/Y4bXQH7)

