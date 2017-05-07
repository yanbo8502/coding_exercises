
#include <stdio.h>
#include <iostream>
#include "data_tool.h"
using namespace std;


int main(int argc, char **argv)  
{
	cout<<"hello world!"<<endl;
	Matrix* matrix = Tool::getMatrix("matrix.txt");
	
	for (int i = 0; i <matrix->height ; ++i)
	{
		for (int j= 0; j< matrix->width; ++j)
		{
			cout<<matrix->data[i][j]<<" ";
		}
		cout<<endl;
	}
	matrix = Tool::getGraphMatrixFromEdgeFiles("graph.txt");
	
	for (int i = 0; i <matrix->height ; ++i)
	{
		for (int j= 0; j< matrix->width; ++j)
		{
			cout<<matrix->data[i][j]<<" ";
		}
		cout<<endl;
	}

	TreeNode<string>* root = Tool::getTree<string>("tree.txt");

	vector<string> v1;
	vector<string> v2;
	vector<string> v3;
	v1.push_back("a");
	v1.push_back("abc");
	v1.push_back("ac");
	
	v2.push_back("abc");
	v2.push_back("ac");
	v2.push_back("a");

	v3.push_back("abc");
	v3.push_back("ac");
	v3.push_back("aa");
	cout<<Tool::compareTwoSets<string>(v1,v2)<<endl;
	cout<<Tool::compareTwoSets<string>(v1,v3)<<endl;
	
}