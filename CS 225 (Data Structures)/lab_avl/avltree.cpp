/*
* @file avltree.cpp
* Definitions of the binary tree functions you'll be writing for this lab.
* You'll need to modify this file.
*/


using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if (t == NULL){
        return;
    }
    Node * h = t->right;
    t->right = h->left;
    h->left = t;
    t->height  = 1 + max(heightOrNeg1(t->left),heightOrNeg1(t->right));
    t = h;
    t->height  = 1 + max(heightOrNeg1(t->left),heightOrNeg1(t->right));

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * h = t->left;
    t->left = h->right;
    h->right = t;
    t->height  = 1 + max(heightOrNeg1(t->left),heightOrNeg1(t->right));
    t = h;
    t->height  = 1 + max(heightOrNeg1(t->left),heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{   if (subtree == NULL || (subtree->left == NULL && subtree->right == NULL)){
        return;
    }
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (balance <=-2){
        int left_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (left_balance<0){
            rotateRight(subtree);
        }
        else
        {
            rotateLeftRight(subtree);
        }

    }
    if (balance >=2){
        int right_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (right_balance>0){
            rotateLeft(subtree);
        }
        else
        {
            rotateRightLeft(subtree);
        }

    }
    subtree->height  = 1 + max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));

    // your code here
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
     if(subtree == NULL){  //base case
        subtree = new Node(key, value);
        subtree->height = 0;
        return;
         }

    else if(key > subtree->key){
    insert(subtree->right, key, value);

         }

    else if(key < subtree->key){
    insert(subtree->left, key, value);
     }
     else if(subtree->key == key){
        subtree->value = value;
     }
    rebalance(subtree);

     return;

    // your code here
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);

    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);


    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while(iop->right != NULL){
            iop = iop->right;
            }
            swap(subtree, iop);
            remove(subtree->left, key);
            rebalance(iop);
        } else {
            /* one-child remove */
            // your code here
            Node* l = subtree->left;
            Node* r = subtree->right;
            if(l){
                delete subtree;
                 subtree = l;
            }
            else{
              delete subtree;
              subtree = r;
            }
            rebalance(subtree);

        }
        // your code here
    }
}


/**


//template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here   done
    Node* imb = t->right;;
    t->right = imb-> left;
    imb ->left = t;
    //Update node heights
    t->height = heightOrNeg1(t);
    t = imb;
    t->height = heightOrNeg1(t);
    //Finish arrangement
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here   Done
    Node* imb = t-> left;
    t->left = imb-> right;
    imb ->right = t;
    //Update node heights
    t->height = heightOrNeg1(t);
    t = imb;
    t->height = heightOrNeg1(t);
    //Finish arrangement

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here   Done

    rotateLeft(t->right);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here done Done

   if(subtree == NULL || (subtree->left == NULL && subtree->right == NULL)){
     return;}

 int balanced = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
   if (balanced == 2) {
       int balancedRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
       if (balancedRight < 0) {
         rotateRightLeft(subtree);
       }
       else {
         rotateLeft(subtree);
     }
   }
   if (balanced == -2) {
       int balancedLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
       if (balancedLeft > 0) {
         rotateLeftRight(subtree);
       }
       else {
         rotateRight(subtree);
     }
   }
   subtree->height = 1 + (std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)));
   return; //

  //   if(Balance(subtree) <= -2){
     if(Balance(subtree->left) < 0 ){ //elbow
       rotateRight(subtree);}

     else {                           //stick
       rotateLeftRight(subtree);  }
     }

    else if(Balance(subtree) >= 2){
     if(Balance(subtree->right) > 0){  //stick
       rotateLeft(subtree);
     }
     else  { //elbow
       rotateRightLeft(subtree);
     }
   }
   subtree->height = heightOrNeg1(subtree);
   return;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){  //base case
    subtree = new Node(key, value);
    subtree -> height = 0;
    return;  }

    else if(key >= subtree->key){
    insert(subtree->right, key, value);  }

    else {
    insert(subtree->left, key, value);  }

    rebalance(subtree);
    return;

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);

    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);

    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            //no-child remove //
            // your code here
//            delete subtree;
            subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            // two-child remove //
            // your code here
  //         Node* iop = subtree->left;
            while(iop->right != NULL){
            iop = iop->right;
            }
            swap(iop, subtree);
            remove(subtree->left, key);
            rebalance(iop);

        } else {
            //one-child remove //
            // your code here

  //            Node* l = subtree->left;
              Node* r = subtree->right;
              if(l){
                  delete subtree;
                   subtree = l;
              }
              else{
                delete subtree;
                subtree = r;
              }
              rebalance(subtree);

        }
        // your code here
    }
    rebalance(subtree);

}
//
//Helper fns
//template <class K, class V>
int AVLTree<K, V> :: heightOrNeg1(const Node* node) const {
  if (node == NULL) {return -1;}
  else {return 1 + std::max(heightOrNeg1(node->left), heightOrNeg1(node->right));}
} //

//template <class K, class V>
int AVLTree<K, V>::Balance( Node* node)
{
    if(node == NULL){return 0;}
    return heightOrNeg1(node->right) - heightOrNeg1(node->left);
}
*/
