/* Your code here! */

#include "dsets.h"

#include <math.h>

#include <vector>

using namespace std;

#include <iostream>

using std::vector;



DisjointSets::DisjointSets(){
    sets.resize(0);
}

void DisjointSets::addelements(int num){
    int cur_size = sets.size();
    int next_size = cur_size + num;
    sets.resize(next_size);
    for(unsigned i = cur_size; i<sets.size(); i++){
        sets[i] = -1;
    }
}

int DisjointSets::find(int elem){
    if (sets[elem]<0){
        return elem;
    }
    else{
        return find(sets[elem]);
    }
}



void DisjointSets::setunion(int a, int b){
    if (sets[b]>0){
        setunion(a, find(b));
        return;
    }
    int curr_root = find(a) ;

    if((sets[b]<0)&(sets[a]>0)){
        sets[b] = a;
        sets[curr_root] = sets[curr_root] - 1;
        return;        
    }
    else if(sets[b]<sets[a]){
        sets[b] = sets[b]+sets[a];
        sets[a] = b; 
        return;
    }
    else if(sets[a]<=sets[b]){
        sets[a] = sets[b] + sets[a];
        sets[b] = a; 
        return;
    }
    cout<<sets[a]<<","<<sets[b]<<","<<a<<","<<b<<","<<endl;
    cout<<"dafaq"<<endl;
    return;
}


int DisjointSets::size(int elem){
    int root = find(elem);
    return (sets[root]*-1);
}
