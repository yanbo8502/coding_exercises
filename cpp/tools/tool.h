
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <thread>  
#include <chrono>  
/******unit test*****/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "data_tool.h"

/***************/
using namespace std;

struct treenode{
	string value;
	treenode* left;
	treenode* right;
};