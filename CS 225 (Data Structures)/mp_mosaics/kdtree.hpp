/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim]<second[curDim]) { return true; }
    else if (first[curDim]>second[curDim]){ return false; }
    else{ return (first<second); }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    int current_dist = 0;
    int potential_dist = 0;

    for(int i = 0; i<Dim; i++){
      current_dist += pow((target[i]-currentBest[i]),2);
      potential_dist += pow((potential[i]-target[i]),2);
    }

    if (potential_dist<current_dist) { return true; }
    else if (potential_dist>current_dist) { return false; }
    else { return (potential<currentBest); }

    return false;
}
template <int Dim>
void KDTree<Dim>::sort(vector<Point<Dim>>& new_Points, int dim)
{
    unsigned min;
    for(unsigned i=0; i<new_Points.size()-1; i++){
      min = i;
      for(unsigned j = i+1 ; j<new_Points.size();j++){
        if (smallerDimVal(new_Points[j],new_Points[min],dim)) { min = j; }
      }
      if (min!=i){
        Point<Dim> temp = new_Points[i];
        new_Points[i] = new_Points[min];
        new_Points[min] = temp;
      }
    }
}

template <int Dim>
void KDTree<Dim>::makeTree(KDTreeNode*& N, vector<Point<Dim>> new_Points, int d){
    if(new_Points.size()==0){
      N=NULL;
      return;
    }
    if(new_Points.size()==1){
      N = new KDTreeNode(new_Points[0]);
      return;
    }
    sort(new_Points, d);
    int median_index = (new_Points.size()-1)/2;
    N = new KDTreeNode(new_Points[median_index]);
    if (median_index>0){
      auto first = new_Points.cbegin();
      auto last = new_Points.cbegin() + median_index;
      std::vector<Point<Dim>> left(first, last);
      makeTree(N->left,left, (d+1)%Dim);
    }
    auto first = new_Points.cbegin()+median_index+1;
    auto last = new_Points.cbegin() + new_Points.size();
    std::vector<Point<Dim>> right(first, last);
    makeTree(N->right,right,(d+1)%Dim );
    return;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    makeTree(root,newPoints,0);
    /**
     * @todo Implement this function!
     */
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {


  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {


  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {

  destroy_(root);

  /**
   * @todo Implement this function!
   */
}

template <int Dim>
void KDTree<Dim>::destroy_(KDTreeNode * N){
    if (N == NULL){
      return;
    }
    destroy_(N->right);
    destroy_(N->left);
    delete N;
    return;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    Point<Dim> currentBest = root->point;
    Point<Dim> q = query;
    find(root, currentBest, q, 0);
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::find(KDTreeNode* N, Point<Dim> &currentBest,Point<Dim> &q,  int d) const{
  if (N==NULL){
    return;
  }
  KDTreeNode* next;
  KDTreeNode* bactrace;
  if(smallerDimVal(N->point, q, d)){
    next = N->right;
    bactrace = N->left;
  }
  else{
    bactrace = N->right;
    next = N->left;
  }
  find(next, currentBest, q, (d+1)%Dim);

  if(shouldReplace(q, currentBest, N->point)){
    currentBest = N->point;
  }
  double curr_radius = 0;
  for(int i = 0; i<Dim; i++){
    curr_radius+=pow((currentBest[i]-q[i]),2);
  }
  double curr_dist = pow((N->point[d]-q[d]),2);

  if (curr_radius>=curr_dist){
    find(bactrace, currentBest,q,(d+1)%Dim);
  }
}
