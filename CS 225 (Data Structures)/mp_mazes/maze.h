#pragma once

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"


#include <math.h>
#include <utility>

#include <vector>

using namespace std;

using namespace cs225;



using std::vector;



class SquareMaze
{
    private:
        vector<pair<bool,bool>>* maze;
        int _width;
	    int _height;


    public:
        SquareMaze();
        ~SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir);
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze ();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution () ;
        PNG * drawCreativeMaze() ;
        int inx(int x, int y) const;


};
