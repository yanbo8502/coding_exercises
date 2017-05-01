#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
/******unit test*****/
#define CATCH_CONFIG_MAIN
#include "../../tools/catch.hpp"
/***************/
using namespace std;
class A
{
public:
	A()
	{
		data="abc";
	}
	void print() const
	{
		cout<<"A:print():"<<data<<endl;
	}
private:
	string data;
friend void print(const A&  a);
};

void print(const A&  a)
{
	cout<<"print(const&  A):"<<a.data<<endl;
}

TEST_CASE("Testing class visibility") {
	    // set up
          A a;
	    // different sections
 
             SECTION("1") {
             	a.print();
                 
            }

            SECTION("2") {
             	print(a);
                 
            }
    }