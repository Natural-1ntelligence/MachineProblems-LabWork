#include "shape.hpp"
/*intro paragraph
Team - rkadiri2, heshama2, yab2
This is the first c++ code we are writing. Over here we are attepting to find the max area and max volume of shapes.
*/
//Base class
//Please implement Shape's member functions
//constructor, getName()

Shape:: Shape(string name) {
  name_=name;
}
string Shape::getName(){
    //TODO
    return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//getArea(), getVolume(), operator+, operator-
//copy(), clear()

void Rectangle::copy(const Rectangle& other){
  spec[0]=other.spec[0];
  spec[1]=other.spec[1];
}
void Rectangle::clear(){

  delete(spec);
}
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
    spec = new double[2];
    spec[0] = width;
    spec[1] = length;
}
Rectangle::Rectangle(const Rectangle& other):Shape("Rectangle"){
    copy(other);
}
Rectangle::~Rectangle(){
    clear();
}
const Rectangle& Rectangle::operator = (const Rectangle& other){
    clear();
    copy(other);
    return *this;
}
double Rectangle::getArea()const{
  return (spec[0]*spec[1]);
}
double Rectangle::getVolume()const{

    return 0;
}
Rectangle Rectangle::operator + (const Rectangle& rhs){
  double a=spec[0]+rhs.spec[0];
  double b=spec[0]+rhs.spec[1];
  return Rectangle(a,b);
}

Rectangle Rectangle::operator - (const Rectangle& rhs){
  double width = std::max(0.0, spec[0]-rhs.getWidth());
  double length = std::max(0.0, spec[1]-rhs.getLength());
  return Rectangle(width, length);
}

// double * spec;
//spec[0] should be width
//spec[1] should be length
double Rectangle::getWidth()const{return spec? spec[0]:0;}
double Rectangle::getLength()const{return spec? spec[1]:0;}
void Rectangle::setWidth(double width){
    if (spec == NULL)
        return;

    spec[0] = width;
}
void Rectangle::setLength(double length){
    if (spec == NULL)
        return;

    spec[1] = length;
}


//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
void RectPrism::copy(const RectPrism& other){
    //TODO
    spec[0]=other.spec[0];
spec[1]=other.spec[1];
spec[2]=other.spec[2];

}
void RectPrism::clear(){
    //TODO
    delete(spec);

}
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
    spec = new double[3];
    spec[0] = length;
    spec[1] = width;
    spec[2] = height;
}
RectPrism::RectPrism(const RectPrism& other):Shape("RectPrism"){
    copy(other);
}
RectPrism::~RectPrism(){
    clear();
}
const RectPrism& RectPrism::operator = (const RectPrism& other){
    clear();
    copy(other);
    return *this;
}
double RectPrism::getVolume()const{
  return spec[0]*spec[1]*spec[2];
}
double RectPrism::getArea()const{
  return 2*((spec[1]*spec[0])+(spec[1]*spec[2])+(spec[0]*spec[2]));
  }
RectPrism RectPrism::operator + (const RectPrism& rhs){
  spec[0] = spec[0]+rhs.getWidth();
  spec[1] = spec[1]+rhs.getLength();
  spec[2] = spec[2]+rhs.getHeight();
  return RectPrism(spec[0],spec[1],spec[2]);
}

RectPrism RectPrism::operator - (const RectPrism& rhs){
  double w = std::max(0.0, spec[0]-rhs.getWidth());
  double l = std::max(0.0, spec[1]-rhs.getLength());
  double ht = std::max(0.0, spec[2]-rhs.getHeight());
  return RectPrism(w,l,ht);
}

// double * spec;
//spec[0] should be length
//spec[1] should be width
//spec[2] should be height
double RectPrism::getWidth()const{return spec? spec[1]:0;}
double RectPrism::getHeight()const{return spec? spec[2]:0;}
double RectPrism::getLength()const{return spec? spec[0]:0;}
void RectPrism::setWidth(double width){
    if (spec == NULL)
        return;

    spec[1] = width;
}
void RectPrism::setHeight(double height){
    if (spec == NULL)
        return;

    spec[2] = height;
}
void RectPrism::setLength(double length){
    if (spec == NULL)
        return;

    spec[0] = length;
}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
    //@@Insert your code here
	std::ifstream infile(file_name);    ifstream ifs (file_name, std::ifstream::in);
    double num_shapes = 0;
    ifs >> num_shapes;
	string name;
    vector<Shape*> shape_ptrs(num_shapes, NULL);
	double a, b, c;
	for (int i=0; i<num_shapes; i++){
		ifs >> name;
		if(name == "Rectangle"){
			ifs >> a >> b;
			shape_ptrs[i]=new Rectangle(a, b);
		}

		if(name == "RectPrism"){
			ifs >> a >> b >> c;
			shape_ptrs[i]=new RectPrism(a,b,c);
		}
           }

    ifs.close();
    return shape_ptrs;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
    double max_area = 0;
    //@@Insert your code here
    int i=0;
    for (i = 0; i < shapes.size(); i++) {
      if (shapes[i]->getArea()>max_area)
        max_area=shapes[i]->getArea();
    }

    return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
    double max_volume = 0;
    //@@Insert your code here
    int i=0;
    for (i = 0; i < shapes.size(); i++) {
      if (shapes[i]->getVolume()>max_volume)
        max_volume=shapes[i]->getVolume();
    }

    return max_volume;
}
