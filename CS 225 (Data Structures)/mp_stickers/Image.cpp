#include <iostream>
#include "Image.h"
#include <math.h>

using namespace std;
namespace cs225 {

  void Image::lighten(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l += 0.1;                          //Increasing l by .1
          if (pixel.l > 1) {
            pixel.l=1;}
      }
    }
  }

  void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l += amount;                       //Increase l by arg amount
          if (pixel.l > 1) {
            pixel.l=1;}
      }
    }
  }

  void Image::darken(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l -= 0.1;                         //Decrease l by .1
          if (pixel.l < 0) {
            pixel.l=0; }
      }
    }
  }

  void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l -= amount;                       //Decrease l by arg amount
          if (pixel.l < 0) {
            pixel.l=0; }
      }
    }
  }

  void Image::saturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s += 0.1;                          //Increase s by .1
          if (pixel.s > 1) {
            pixel.s=1; }
      }
    }
  }

  void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s += amount;                      //Increase s by arg amount
          if (pixel.s > 1) {
            pixel.s=1; }
      }
    }
  }

  void Image::desaturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s -= 0.1;                          //Decrease s by .1
          if (pixel.s < 0) {
            pixel.s = 0; }
      }
    }
  }

  void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s -= amount;                     //Decrease s by arg amount
          if (pixel.s < 0) {
            pixel.s = 0; }
      }
    }
  }

  void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s -= 0;                          //Turn image into greyscale by setting s as 0
      }
    }
  }

  void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          pixel.h += degrees;                 //Rotate the colour wheel by arg degrees
          while (pixel.h < 0){
            pixel.h+=360;
          }
          pixel.h = fmod(pixel.h, 360);
      }
    }
  }

  void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel & pixel = this->getPixel(x, y);
          if (pixel.h >= 140 && pixel.h <= 260) {
            pixel.h = 216;  }          
          else {
            pixel.h = 11; }
      }
    }
  }


  void  Image::scale(double factor) {
    PNG * original = new PNG(*this);
    this->resize(ceil(factor*width()),ceil(factor*height()));
        for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
          HSLAPixel &Pixel2 = this->getPixel(x,y);
          HSLAPixel &pixel = original->getPixel(ceil(x/factor), ceil(y/factor));
          Pixel2.h = pixel.h;
          Pixel2.s = pixel.s;
          Pixel2.l = pixel.l;
          Pixel2.a = pixel.a;
        }}

      if (factor > 1) {
      for (unsigned x = 0; x < (width()/factor); x++) {
        for (unsigned y = 0; y < (height()/factor); y++) {
          HSLAPixel & pixel = original->getPixel(x, y);    
          for (unsigned i =0; i < ceil(factor); i++){
            for (unsigned j =0; j < ceil(factor); j++){
                HSLAPixel & Pixel2 = this->getPixel(x*factor+i,y*factor+j);
                Pixel2.h = pixel.h;
                Pixel2.s = pixel.s;
                Pixel2.l = pixel.l;
                Pixel2.a = pixel.a;
            }}}}}

    delete original;
    original = NULL;
  }

  void Image::scale (unsigned w, unsigned h){
    double widthF = ((double)(w*1.0)) / ((double)width()*1.0);
    double heightF = ((double)(h*1.0)) / ((double)height()*1.0);
      if (widthF < heightF)
      scale(widthF);
    else scale(heightF);
  }
}
