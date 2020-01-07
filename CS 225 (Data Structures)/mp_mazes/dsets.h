/* Your code here! */


#pragma once

#include <math.h>

#include <vector>

using namespace std;


using std::vector;



class DisjointSets
{
    private:
        vector<int> sets;

    public:
        DisjointSets();
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
};
