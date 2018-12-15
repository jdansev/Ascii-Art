# Ascii Art
A real-time video to Ascii Art generator

<p align="left">
  <img src="./demo-ascii.gif" width="400" >
  <img src="./demo-original.gif" width="400" >
</p>

Written in C++ with the OpenCV library.

### Usage

#### clone this repo

```
git clone https://github.com/jdansev/ascii-art
cd ascii-art
```

#### compile
```
g++ asciiart.cpp -o asciiart `pkg-config --cflags --libs opencv` && ./asciiart
```
