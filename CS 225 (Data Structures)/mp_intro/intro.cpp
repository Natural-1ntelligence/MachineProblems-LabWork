#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG pic;
  pic.readFromFile(inputFile);
  cs225::PNG rotated(pic.width(), pic.height());

  for (unsigned x = 0; x < pic.width(); x++) {
    for (unsigned y = 0; y < pic.height(); y++) {
      rotated.getPixel(x,y)= pic.getPixel(pic.width()-1-x,pic.height()-1-y);
     }}
  rotated.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  //  width = 800;
    //height = 800;

    for (unsigned int x = 0; x < png.width(); x++) {
      for (unsigned int y = 0; y < png.height(); y++) {
        HSLAPixel & pixel = png.getPixel(x, y);

    if ((x < 2*png.width()/3) && (x > png.width()/3)) {


    pixel.h = 45 ;
    pixel.s = 100;
    pixel.l = 50;
    pixel.a = 1;
}
    if ((x < png.width()) && (x > 2*png.width()/3)) {
    pixel.h = 180 ;
    pixel.s = 100;
    pixel.l = 50;
    pixel.a = 1;
}
    if (x < png.width()/3) {


    pixel.h = 320 ;
    pixel.s = 100;
    pixel.l = 50;
    pixel.a = 1;
  }}
}
//for (unsigned int x = 0; x < 2*png.width()/3 && x> png.width()/3; x++) {
  //for (unsigned int y = 0; y < png.height() && y > png.height()/3; y++) {


//for (unsigned int x = 0; x < png.width() && x > 2*png.width()/3; x++) {
  //for (unsigned int y = 0; y < png.height() && y> 2*png.width()/3; y++) {




//for (unsigned int x = 0; x < png.width()/5; x++) {
  //for (unsigned int y = 0; y < png.width()/5; y++) {



  return png;
}
