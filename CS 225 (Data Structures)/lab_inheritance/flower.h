/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once
#include "shape.h"
#include "triangle.h"
#include "circle.h"
#include "drawable.h"
#include "rectangle.h"
#include "vector2.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Rectangle* stem;                                      //Ex5 REPLACED Shape with Rectangle*
    Circle* pistil; // center piece of flower             //Ex5 REPLACED Shape woth Circle*
    Triangle* leaf;                                       //Ex5 REPLACED Shape with Triangle*

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;
    void clear();
  public:
    Flower(const Vector2& center);
    void draw(cs225::PNG* canvas) const;
    ~Flower();
};
