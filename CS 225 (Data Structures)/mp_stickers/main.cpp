#include "Image.h"
#include "StickerSheet.h"
using namespace cs225;

int main() {
  Image corn;
   corn.readFromFile("corn.png");

   Image Il;
   Il.readFromFile("illini.png");
   Image almam;
   almam.readFromFile("almam.png");
   Image i;
   i.readFromFile("i.png");

   StickerSheet final(corn, 3);
   final.addSticker(Il, 700, 350);
   final.addSticker(almam, 25, 350);
   final.addSticker(i, 25, 25);

   Image picture = final.render();
 picture.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  return 0;
}
