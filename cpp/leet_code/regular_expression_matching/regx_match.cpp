/*
https://leetcode.com/problems/regular-expression-matching/
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

/*v1 use stack instaed of recursive
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
*/
/*vcompare
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();

        // Iterative dynamic programming. Time: O(m^2 n), Space: O(m).
        vector<int> dp = vector<int>();
        for (int i = 0; i < m; i++) {
            dp.push_back(0);
        }
        dp.push_back(1);

        for (int j = n - 1; j >= 0; j--) {
            if (j == 0 || p[j] != '*') {
                for (int i = 0; i < m; i++) {
                    dp[i] = (p[j] == '.' || p[j] == s[i]) && dp[i + 1];
                }
                dp[m] = 0;
                continue;
            }

            --j;
            for (int i = 0; i < m + 1; i++) {
                for (int matchLen = 0; matchLen <= m - i; matchLen++) {
                    if (matchLen != 0 && p[j] != '.' && p[j] != s[i + matchLen - 1]) {
                        dp[i] = 0;
                        break;
                    }

                    if (dp[i + matchLen]) {
                        dp[i] = 1;
                        break;
                    }
                }
            }
        }

        return dp[0];
    }
};
*/

/*v2 */
class Solution {
public:
    bool isMatch(string s, string p) {
        int slen = s.length();
        int plen = p.length();
        int dp[slen+1][plen+1];
      
        for(int i=0; i<=slen; i++)
        {
           for(int j=0;j<=plen; j++)
          {
             dp[i][j] = 0;
          }
           
        }

          dp[0][0] = 1;
        for(int i=1; i<=slen; i++)
        {
            dp[i][0] = 0;
        }

        for(int j=0;j<plen; j++)
        {
              if(j-1>=0 && p[j-1]!='*' && p[j]=='*')
              {
                    dp[0][j+1] = dp[0][j] || dp[0][j-1];
              }
        }

        for(int i=0; i<slen; i++)
        {
             for(int j=0;j<plen; j++)
            {
                   if(j-1>=0 && p[j-1]!='*' && p[j]=='*')
                  {
                          dp[i+1][j+1] = ((s[i]==p[j-1] || p[j-1] == '.')&& (dp[i][j] || dp[i][j+1]) ) || dp[i+1][j] || dp[i+1][j-1];
                  }
                  else if(p[j] == s[i] || p[j] == '.')
                  {
                        dp[i+1][j+1] =  dp[i][j];
                  }
            }
             
        }
/*
        cout<<"start:"<<endl;
        for(int i=0; i<=slen; i++)
        {
           for(int j=0;j<=plen; j++)
          {
               cout<<dp[i][j]<<" ";
          }
           cout<<endl;
        }
        
     */   
        return dp[slen][plen];

      }
};

TEST_CASE("Testing Regx Matching") {
	    // set up
            Solution sol;
            string s = "abcde";
            string p = "*";

	    // different sections
 
             SECTION("a*e matches a**e") {
                s = "a*e";
                p = "a**e";
                REQUIRE(sol.isMatch(s, p) );
            }

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
       
              SECTION(" aaa does not match ab*a") {
                    s = "aaa";
                    p = "ab*a";
                    REQUIRE(!sol.isMatch(s, p) );
             }
   }