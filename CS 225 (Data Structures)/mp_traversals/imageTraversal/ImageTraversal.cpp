#include <cmath>
#include <iterator>
#include <iostream>
#include <vector> //ADDED

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
 double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
   double h = fabs(p1.h - p2.h);
   double s = p1.s - p2.s;
   double l = p1.l - p2.l;

   // Handle the case where we found the bigger angle between two hues:
   if (h > 180) { h = 360 - h; }
   h /= 360;

   return sqrt( (h*h) + (s*s) + (l*l) );
 }
 ImageTraversal::~ImageTraversal(){

 }
 /**
  * Default iterator constructor.
  */
 ImageTraversal::Iterator::Iterator() {
     traversor = NULL;
     end_traverse = true;
   /** @todo [Part 1] */
 }

 ImageTraversal::Iterator::~Iterator() {
   if (traversor!=NULL)
    { delete traversor;}
    traversor =NULL;
 }

 ImageTraversal::Iterator::Iterator(ImageTraversal *it , Point start_, PNG image_, double tolerance_){
   traversor = it;
   start = start_;
   tol = tolerance_;
   image = image_;
   w = image.width();
   h = image.height();



   traverse_complete.resize(w);

   for (int i =0; i< w ; i++ ){
     traverse_complete[i].resize(h);
   }
   for (int i =0; i< w ; i++ ){
     for (int j =0; j< h ; j++ ){
       traverse_complete[i][j] = false;
     }
   }
   if(it->empty()){
     end_traverse = true;
   }
   else{
     end_traverse = false;
   }
 }

 void ImageTraversal::Iterator::setEnd(bool x){
   end_traverse = true;
 }

 /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
 ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
   Point current = traversor->pop();
   int current_x = current.x;
   int current_y = current.y;


   traverse_complete[current_x][current_y] = true;

   HSLAPixel start_pixel = image.getPixel(start.x,start.y);

   if(current_x+1<w){
     if (traverse_complete[current_x+1][current_y] == 0){
       double t = calculateDelta(image.getPixel(current_x+1,current_y), start_pixel);
       if (t<tol){
         traversor->add(Point(current_x+1,current_y));
       }
     }
   }
   if(current_y+1<h){
     if (traverse_complete[current_x][current_y+1] == 0){
       double t = calculateDelta(image.getPixel(current_x,current_y+1), start_pixel);
       if (t<tol){
         traversor->add(Point(current_x,current_y+1));
       }
     }
   }
   if(current_x-1>=0){
     if (traverse_complete[current_x-1][current_y] == 0){
       double t = calculateDelta(image.getPixel(current_x-1,current_y), start_pixel);
       if (t<tol){
         traversor->add(Point(current_x-1,current_y));
       }
     }
   }
   if(current_y-1>=0){
     if (traverse_complete[current_x][current_y-1] == 0){
       double t = calculateDelta(image.getPixel(current_x,current_y-1), start_pixel);
       if (t<tol){
         traversor->add(Point(current_x,current_y-1));
       }
     }
   }
   while (!traversor->empty()) {
       if (traverse_complete[traversor->peek().x][traversor->peek().y] == true){
       Point p = traversor->pop();
       }
       else{
         break;
       }
   }
   if(traversor->empty()){
     setEnd(true);
   }


   /** @todo [Part 1] */

   return *this;
 }

 /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
 Point ImageTraversal::Iterator::operator*() {
   /** @todo [Part 1] */

   return traversor->peek();
 }

 /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
 bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
   /** @todo [Part 1] */

   if (end_traverse != other.end_traverse){
     return true;
   }
   else{
     return false;
   }
 }
