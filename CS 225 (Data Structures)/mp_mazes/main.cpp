#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze sqm;
    sqm.makeMaze(100, 100);
    PNG* mazecanvas = sqm.drawCreativeMaze();
    mazecanvas->writeToFile("creative.png");
    cout << "Added maze" << endl;
    delete mazecanvas;
    return 0;
}
