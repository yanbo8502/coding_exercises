
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


	
}