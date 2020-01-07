#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>

using std::cout;
using std::endl;

using std::vector;

using namespace cs225;



using std::vector;
using std::random_shuffle;



SquareMaze::SquareMaze(){
    _width = 0;
    _height = 0;
    maze = new vector<pair<bool,bool>>;


}

SquareMaze::~SquareMaze() {
    delete maze;
	maze = NULL;
	return;
}


void SquareMaze::makeMaze(int width, int height) {
    _height = height;
    _width = width;
    DisjointSets d;
    d.addelements(height*width);
    maze->resize(height*width);
    for (int i = 0; i < width * height; i++){
		(*maze)[i].first = true;
        (*maze)[i].second = true;
    }
    vector<int> temp;
    for(int t = 0; t<int(maze->size())*2; t++){
        temp.push_back(t);
    }
    srand(time(NULL));
    std::random_shuffle(temp.begin(), temp.end());

    for(vector<int>::iterator it = temp.begin();it !=temp.end(); it++){
        if(*it<int(maze->size())){
            if((*it+1)%width != 0){
                if(d.find(*it) != d.find(*it+1)){
					(*maze)[*it].first=false;
					d.setunion(*it, *it+1);
				}
            }
        }
        else{
            int cur_index = *it-int(maze->size());
            if((cur_index)/width < (height -1)){
                if(d.find(cur_index) != d.find(cur_index+width)){
					(*maze)[cur_index].second=false;
					d.setunion(cur_index, cur_index+width);
				}
            }
        }

        }

    }

bool SquareMaze::canTravel(int x, int y, int dir){
    if(dir==0){
        return !(*maze)[_width*y+x].first;

    }
    if(dir==1){
        return !(*maze)[_width*y+x].second;

    }
    if(dir==2){
        if(x>0)
        return !(*maze)[_width*y+x-1].first;
        else
        {
            return false;
        }


    }
    if(dir==3){
        if(y>0)
        return !(*maze)[_width*(y-1)+x].second;
        else
        {
            return false;
        }

    }
    return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){

    if(dir==0)
		(*maze)[inx(x,y)].first = exists;
	if(dir==1)
		(*maze)[inx(x,y)].second = exists;
    return;

}

vector<int> SquareMaze::solveMaze (){
    queue<pair<bool,bool>> q;
    queue<int> q2;

    vector<int> bottom;

    vector<int> res;

    vector<int> parent;
    pair<bool,bool> curr;

    int x = 0;
    int dist = 0;


    vector<bool> visited;
    visited.resize(_width*_height);
    bottom.resize(_width);
    parent.resize(_width*_height);
    for (int i = 0; i < _width*_height; i++) {
            visited[i] = false;
    }

    q.push((*maze)[x]);
    q2.push(x);

    visited[x] = true;

    while (!q.empty()) {
        curr = q.front();

        q.pop();

        x = q2.front();
        q2.pop();


        if (x/_width == (_height - 1))
        bottom[x%_width] = dist;

        if (canTravel(x%_width, x/_width, 0) && !visited[x+1]) {
        q.push((*maze)[x + 1]);
        q2.push(x+1);
        visited[x + 1] = true;
        parent[x+1] = x;
        }

        if (canTravel(x%_width, x/_width, 1) && !visited[x+_width]) {
        q.push((*maze)[x+_width]);
        q2.push(x+_width);
        visited[x+_width] = true;
        parent[x+_width] = x;
        }

        if (canTravel(x%_width, x/_width, 2) && !visited[x-1]) {
        q.push((*maze)[x-1]);
        q2.push(x-1);
        visited[x-1] = true;
        parent[x-1] = x;
        }

        if (canTravel(x%_width, x/_width, 3)) {
            if(!visited[x-_width]){
        q.push((*maze)[x-_width]);
        q2.push(x-_width);
        visited[x-_width] = true;
        parent[x-_width] = x;
        }
        }
        dist++;
    }

    int max_D = 0;
    int fin_bottom;
    for(int i = 0; i < _width; i++) {
        if(bottom[i] > max_D) {
            max_D = bottom[i];
            fin_bottom = i+_width*(_height-1);
        }
    }

    int cur = fin_bottom;
    int par;
    int dir;


    while(!(cur==0)) {
        par = parent[cur];

        if (par%_width == cur%_width) {
        if (par/_width + 1 == cur/_width)
            dir = 1;

        if (par/_width - 1 == cur/_width)
            dir = 3;
        }

        if (par/_width == cur/_width) {
        if (par%_width + 1 == cur%_width)
            dir = 0;

        if (par%_width - 1 == cur%_width)
            dir = 2;
        }

        res.insert(res.begin(), dir);
        cur = par;
    }



    return res;

}

PNG * SquareMaze::drawMaze() const{

    PNG* res = new PNG((_width * 10) + 1, (_height * 10) + 1);
    HSLAPixel b(0, 1, 0, 1);

    for(int i = 10; i < (_width * 10) + 1; i++) {
       res->getPixel(i, 0) = b;
    }

    for(int i = 0; i < (_width * 10) + 1; i++) {
       res->getPixel(i, (_width * 10)) = b;
    }

    for(int i = 0; i < (_height * 10) + 1; i++) {
       res->getPixel(0, i) = b;
    }

    for(int x = 0; x < _width; x++) {
       for(int y = 0; y < _height; y++) {

          if((*maze)[inx(x,y)].first) {
            for(int k = 0; k <= 10; k++) {
               res->getPixel((x + 1) * 10, y * 10 + k) = b;
            }
          }

          if((*maze)[inx(x,y)].second) {
            for(int k = 0; k <= 10; k++) {
               res->getPixel(x * 10 + k, (y + 1) * 10) = b;
            }
          }
       }
    }

    return res;
}

PNG * SquareMaze::drawMazeWithSolution (){
    PNG* res = drawMaze();

    std::vector<int> sol = solveMaze();
    HSLAPixel r(0, 1, 0.5, 1);
    HSLAPixel w(0, 1, 1, 1);

    int x = 5;
    int y = 5;

    for(unsigned i = 0; i < sol.size(); i++) {
        if(sol[i] == 0) {
            for(int k = 0; k <= 10; k++) {
            res->getPixel(x + k, y) = r;
            }
            x += 10;
        }

        if(sol[i] == 1) {
            for(int k = 0; k <= 10; k++) {
            res->getPixel(x, y + k) = r;
            }
            y += 10;
        }

        if(sol[i] == 2) {

            for(int k = 0; k <= 10; k++) {
            res->getPixel(x - k, y) = r;
            }
            x -= 10;
        }

        if(sol[i] == 3) {

            for(int k = 0; k <= 10; k++) {
            res->getPixel(x, y - k) = r;
            }
            y -= 10;
        }
    }

    for(int i = 1; i <= 9; i++) {
        res->getPixel(x - 5 + i, y + 5) = w;
    }


    return res;

}

PNG * SquareMaze::drawCreativeMaze() { //errors present
  int w = _width * 10 + 1;
  int h = _height * 10 + 1;
  PNG* mycanvas = new PNG(w, h);

  for(int j = 0; j < int(h / 4); j++){
    HSLAPixel& p = mycanvas->getPixel(0, j);
    p.l = 0;  //Blacken
  }

  for(int j = 3 * int(h / 4); j < h; j++){
    HSLAPixel& p = mycanvas->getPixel(0, j);
    p.l = 0;  //Blacken
  }

  for(int i = 0; i < w/3; i++){
    HSLAPixel& p = mycanvas->getPixel(i, 0);
    p.l = 0;  //Blacken
}

  for(int i = 2* int(w/3); i < w; i++){
    HSLAPixel& p = mycanvas->getPixel(i, 0);
    p.l = 0;  //Blacken
}
return mycanvas;
}


int SquareMaze::inx(int x, int y) const
{
    return _width*y+x;
}
