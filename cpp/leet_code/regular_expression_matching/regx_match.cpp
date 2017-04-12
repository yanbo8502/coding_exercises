/*
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

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
          int size_s = strlen(s);
          int size_p = strlen(p);

          if(size_p == 0)
          {
                if(size_s == 0)
                {
                      return true;
                }
            	 return false;
          }
          if(size_p == 1)
          {
                 if(size_s ==1 && (s[0] == p[0] || '.' == p[0]))
                 {
                       return true;
                 }

                 return false;
          }
          if(p[size_p -1]!='*' && p[size_p -1]!='.')
          {
                  if(size_s > 0 && s[size_s-1] != p[size_p-1])
                  {
                        return false;
                  }
          }

           if(p[1] == '*')
            {

                if(size_s >0 && (s[0] == p[0] || '.' == p[0]))
                {
                      if (isMatch(s +1 , p+2))
                      {
                            return true;
                      }

                       if(isMatch(s , p +2))
                       {
                            return true;
                       }

                       if(isMatch(s +1, p ))
                       {
                            return true;
                       }
                      return false;
                }
                else
                {
                      return  isMatch(s, p +2);
                }
            }
            else
            {
                   if(size_s>0 && (s[0] == p[0] || '.' == p[0]))
                   {
                          return   isMatch(s +1, p+1);
                   }
                   return false;
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
 
            SECTION("abcde matches .*e") {
                s = "abcde";
                p = ".*e";
                REQUIRE(sol.isMatch(s, p) );
            }

         
              SECTION("abcde does not matche *") {
	        s = "abcde";
	        p = "*";
	        REQUIRE(!sol.isMatch(s, p) );
              }

	       SECTION("abcde does not match .*c") {
	        s = "abcde";
	        p = ".*c";
	        REQUIRE(!sol.isMatch(s, p) );
	      }

              SECTION("aab  matches  c*a*b") {
                s = "aab";
                p = "c*a*b";
                REQUIRE(sol.isMatch(s, p) );
             }

             SECTION("aa matches a*") {
                  s = "aa";
                  p = "a*";
                 REQUIRE(sol.isMatch(s, p) );
           }

              SECTION("aab doesn't matches a*") {
                  s = "aab";
                  p = "a*";
                  REQUIRE(!sol.isMatch(s, p) );
             }
 
              SECTION("a matches ab*") {
                    s = "a";
                    p = "ab*";
                    REQUIRE(sol.isMatch(s, p) );
              }

              SECTION("bbba matches .*a*a") {
                    s = "bbba";
                    p = ".*a*a";
                    REQUIRE(sol.isMatch(s, p) );
             }

            SECTION("a does not match .*..a*") {
                  s = "a";
                  p = ".*..a*";
                  REQUIRE(!sol.isMatch(s, p) );
            }

              SECTION("aaaaaaaaaaaaab does not match a*a*a*a*a*a*a*a*a*a*c") {
                    s = "aaaaaaaaaaaaab";
                    p = "a*a*a*a*a*a*a*a*a*a*c";
                    REQUIRE(!sol.isMatch(s, p) );
             }
       
   }