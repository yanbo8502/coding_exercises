/*
Some examples:
 a → 1 (a)
abc → a  (a,b,c)
abbc→ 2 (bb)
abcaacca→ 4  (caac, acca)
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


/*v2 manchester algorithm original, easy to read and understand*/
class Solution {
public:
    int getLength(string s) {
        int  length = 1;
        string pad_str = getPaddingStr(s);
        int r[pad_str.size()];
        int R= -1;
        int Rcenter = 0;
       for(int i=0;i<pad_str.size(); i++)
       {
            r[i] = 0;
       }
       int n = pad_str.size();
        for(int i=0;i<n; i++)
       {
          
          if(i >= R )
          {
                  for(int j=1;j<n-i; j++)
                  {
                        if(i-j>=0 && pad_str[i+j]==pad_str[i-j])
                        {
                            r[i]++ ;
                        }
                        else
                        {
                            break;
                        }
                  }                 
          }
          else
          {
               int is = 2* Rcenter - i;
               r[i] = r[is] < (R-i + 1) ? r[is] : (R-i + 1);
               if(r[is] >  (R-i + 1))
               {
                    for(int j= R +1;j<n; j++)
                    {
                          if(2*i-j>=0 && pad_str[j]==pad_str[2*i-j])
                          {
                              r[i]++ ;
                          }
                          else
                          {
                              break;
                          }
                    }      
               }
          }
          if(i+r[i] - 1 > R)
          {
                R= i+r[i] - 1;
                Rcenter = i;
          }
          if(r[i]> length)
          {
                length = r[i];
          }
       }

        return length ;
      }

      string getPaddingStr(string s)
      {
            char* pad = new char[2*s.size() + 1];
            pad[0] = '*';
            for(int i=0;i<s.size();i++)
            {
                  pad[2*i + 1] = s[i];
                  pad[2*i + 2] = '*';
            }
            string res(pad);
            delete[] pad;
            return res;
      }
};

TEST_CASE("Testing Regx Matching") {
	    // set up
            Solution sol;
	    // different sections
 
             SECTION("abbccabacceae length is 7") {
                REQUIRE(sol.getLength("abbccabacceae") == 7 );
            }
            SECTION("abbccaacceae length is 6") {
                REQUIRE(sol.getLength("abbccaacceae") == 6);
            }

              SECTION("abc length is 1") {
                REQUIRE(sol.getLength("abc") == 1);
            }

             SECTION("abbccabaccccaacccceae length is 10") {
                REQUIRE(sol.getLength("abbccabaccccaacccceae") == 10 );
            }

             SECTION("abbccabacccccceae length is 10") {
                REQUIRE(sol.getLength("abbccabacccccceae") == 7 );
            }
   }