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

            char* a1="123456789";
            char* a3;
            char* a4 = "1";
            char a2[10] = "123456789";
            A* aa;
            cout<<sizeof(a)<<endl;
            cout<<sizeof(aa)<<endl;
            cout<<sizeof(&a)<<endl;
            cout<<sizeof(a1)<<endl;
            cout<<sizeof(&a1)<<endl;
            cout<<sizeof(&a1[0])<<endl;
            cout<<sizeof(a1[0])<<endl;
            cout<<sizeof(a2)<<endl;
            cout<<sizeof(&a2)<<endl;
            cout<<sizeof(&a2[0])<<endl;
            cout<<sizeof(a2[0])<<endl;
            
            cout<<sizeof(a3)<<endl;
            cout<<sizeof(a4)<<endl;

    }