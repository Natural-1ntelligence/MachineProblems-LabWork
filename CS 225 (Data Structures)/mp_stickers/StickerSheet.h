#pragma once
#include "Image.h"

using namespace std;
namespace cs225 {
class StickerSheet{
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();   //Destructor
    StickerSheet(const StickerSheet &other);  //Copy Ctor
    const StickerSheet& operator=(const StickerSheet &other);  //Assignment Operator
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    Image render() const;
    Image *picture;

  private:
    Image* *stickers;
    void _copy(StickerSheet const & other);
    void _destroy();
    unsigned sticker_max;
    unsigned sticker_ct;
    int *xPos;
    int *yPos;

    int *count;
    
};
}

 
