

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

/******unit test*****/
#define CATCH_CONFIG_MAIN
#include "../../tools/catch.hpp"
/***************/
using namespace std;


class Solution {
public:
    bool isMatch(string s, string p) {
          char * s1 = (char*)s.c_str();
           char* p1 = (char*)p.c_str();
          return isMatch1(s1,  p1);
    }

    bool isMatch1(char* s, char* p) {
          //cout<<s<<","<<p<<endl;
          if(strlen(s) == 0)
          {
                 if(strlen(p) == 0)
                 {
                 	return true;
                 }
                 else
                 {
                 	return false;
                 }	
          }

          if(strlen(p) == 0)
          {
          	 return false;
          }
          if(p[0]!='*' && p[0]!='.')
          {
          	  if(p[0] == s[0])
          	  {
          	  	return isMatch(++s, ++p);
          	  }
          	  return false;
          }
          if(p[0] == '.')
          {
          	return isMatch(++s, ++p);
          }

           if(p[0] == '*')
          {
          	if(isMatch(++s,  p))
          	{
          	     return true;
          	}
          	else
          	{
                      return isMatch(++s,  ++p);
          	}
          }
          return false;

    }
};



TEST_CASE("Testing Regx Matching") {
	    // set up
	     Solution sol;
	    string s = "abcde";
	    string p = "*";

	    // different sections
	    SECTION("abcde matches *") {
	        s = "abcde";
	        p = "*";
	        REQUIRE(sol.isMatch(s, p) );
	    }

	    SECTION("abcde matches *e") {
	        s = "abcde";
	        p = "*e";
	        REQUIRE(sol.isMatch(s, p) );
	    }

	    SECTION("abcde does not match **c") {
	        s = "abcde";
	        p = "**c";
	        REQUIRE(!sol.isMatch(s, p) );
	    }
   }