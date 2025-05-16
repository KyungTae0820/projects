#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int eqaulPaths_recursion(Node* node, int depth){
	if(node == NULL) return -1;
	if((node->left == NULL)&&(node->right == NULL)) return depth;
	int Ldepth = eqaulPaths_recursion(node->left, depth+1);
	int Rdepth = eqaulPaths_recursion(node->right, depth+1);
	if((Ldepth != -1)&&(Rdepth != -1)){
		if(Ldepth == Rdepth){
			return Ldepth;
		}
		return -2;
	}
	if(Ldepth != -1){
		return Ldepth;
	}
	return Rdepth;
}

bool equalPaths(Node * root)
{
    // Add your code below
	if(root == NULL) return true;
	else{
		return (eqaulPaths_recursion(root, 0) != -2);
	}
}

