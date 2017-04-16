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
#include <stack>
/******unit test*****/
#define CATCH_CONFIG_MAIN
#include "../../tools/catch.hpp"
/***************/
using namespace std;
 

class Solution {
public:
    bool isMatch(string s, string p) {

          int size_s = s.size();
          int size_p = p.size();
          if(p.size() ==0)
          {
                if(s.size() == 0)
                {
                      return true;
                }
                return false;
          }
          if(p.size() == 1)
          {
                   if(s.size() ==1 && (s[0] == p[0] || '.' == p[0]))
                   {
                         return true;
                   }

                   return false;
          }

          stack<pair<int, int>>  s2p;

          if(p[size_p -1]!='*' && p[size_p -1]!='.')
          {
                  if(size_s > 0 && s[size_s-1] != p[size_p-1])
                  {
                        return false;
                  }
          }

          //when p.size()>=2
          int j =0;
          int i =0;
          while( j < size_p)
          {
                if( j+1 < size_p && '*' == p[j+1])
                {                        
                        if( i == size_s)
                        {
                              j=j+2;
                        }                       
                        else if( '.' == p[j] || p[j] == s[i])
                        {         
                             s2p.push(make_pair(i+1,j + 2));
                             s2p.push(make_pair(i,j + 2));
                             i++;    
                        }
                        else
                        {
                             j=j+2;
                        }
                }
                else
                {
                      if( i == size_s)
                      {
                          if(s2p.empty())
                            {
                                   break;
                            }
                            else
                            {
                                    auto sp=s2p.top();
                                    s2p.pop();
                                    i= sp.first;
                                    j= sp.second;
                            }
                      } 
                      else if(s[i] == p[j] || '.' == p[j])
                     {
                            i = i + 1;
                            j = j + 1;
                     }
                     else
                     {
                            if(s2p.empty())
                            {
                                   break;
                            }
                            else
                            {
                                    auto sp=s2p.top();
                                    s2p.pop();
                                    i= sp.first;
                                    j= sp.second;
                            }
                     }                     
                }
          }

          if(i<size_s || j < size_p)
          {
               return false;;
          }

           return true;
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

              SECTION("aaaaaaaaaaaaab matches a*a*a*a*a*a*a*a*a*a*b") {
                    s = "aaaaaaaaaaaaab";
                    p = "a*a*a*a*a*a*a*a*a*a*b";
                    REQUIRE(sol.isMatch(s, p) );
             }

              SECTION(" aaba does not match ab*a*c*a") {
                    s = "aaba";
                    p = "ab*a*c*a";
                    REQUIRE(!sol.isMatch(s, p) );
             }

                SECTION(" ab does not match .*..") {
                    s = "ab";
                    p = ".*..";
                    REQUIRE(sol.isMatch(s, p) );
             }

              SECTION(" aaa does not match a*a") {
                    s = "aaa";
                    p = "a*a";
                    REQUIRE(sol.isMatch(s, p) );
             }
       
   }