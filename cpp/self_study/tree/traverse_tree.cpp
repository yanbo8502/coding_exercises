#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
/******unit test*****/
#define CATCH_CONFIG_MAIN
#include "../../tools/catch.hpp"
#include "../../tools/data_tool.h"
/***************/
using namespace std;


/*v2 manchester algorithm original, easy to read and understand*/
class Solution {
public:
    void xianxu(TreeNode<string>* root) {
    	if(root == NULL)
    	{
    		return;	
    	}
    	xianxu(root->left);
    	cout<<root->value<<" ";
    	xianxu(root->right);
    }
};


TEST_CASE("print tree nodes") {
	    // set up
	Solution sol;
	    // different sections
 	TreeNode<string>* root = Tool::getTree<string>("../../tools/tree.txt");
	SECTION("xianxu") {
		sol.xianxu(root);
	 }
}