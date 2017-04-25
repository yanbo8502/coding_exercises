/*
https://leetcode.com/problems/wildcard-matching/#/description
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
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
/*V1
class Solution {
public:
    bool isMatch(string s, string p) {

    	int i=0;
    	int j =0;
    	int move_i = -1;
    	int move_j = 0;
    	int slen = s.size();
    	int plen = p.size();
    	bool match = false;
    	if(plen==0)
    	{
    		if(slen == 0)
    		{
    			return true;
    		}
    		return false;
    	}
    	while(i <slen)
    	{
 		if(j==plen && j == move_j)
 		{
 			break;
 		}
    		if(j< plen && p[j] =='*')
    		{	
    			j++;
    			move_j = j;
    			move_i = i;
    			match = true;
    			continue;
    		}
    		else  if(j< plen &&(p[j] == s[i] || p[j] == '?'))
    		{
    			match = true;
    			i++;
    			j++;
    			continue;
    		}
    		if(move_i > -1)
    		{
    			move_i ++;
    			i= move_i;
    			j= move_j;
    			match = false;
    		}
    		else
    		{
    			match = false;
    			break;	
    		}

    	}
    	if(i<slen && j ==plen)
    	{
    		if(p[j-1]=='*')
    		{
    			return true;
    		}
    		return false;
    	}
    	if(i==slen)
    	{
    		for(int k=j;k<plen;k++)
    		{
    			if(p[k]!='*')
    			{
    				return false;
    			}
    		}
    		return true;
    	}
    	

	 return false;
    }
};
*/

/*V2
class Solution {
public:
    bool isMatch(string s, string p) {
	int i=0;
    	int j =0;
    	int slen = s.size();
    	int plen = p.size();
    	int dp[slen + 1][plen + 1];
    	 if(plen==0)
    	{
    		if(slen == 0)
    		{
    			return true;
    		}
    		return false;
    	}
    	
    	for(i=0;i<=slen; i++)
    	{
    		for(j=0;j<=plen;j++)
    		{
    			dp[i][j] =0;
    		}

    	}
    	dp[0][0] = 1;
    	if(p[0] == '*')
    	{
    		dp[0][1] = 1;
    	}
	for(j=1; j<plen; j++)
    	{
    		if(p[j] == '*')	
    		{
    			dp[0][j+1] = dp[0][j];
    		}	
    	}

	for(j=0;j<plen;j++)
    	{
	    	for(i=0;i<slen; i++)
	    	{
   		
    			if(p[j] == '*')
    			{
    				dp[i + 1][j + 1] =  dp[i + 1][j]  || dp[i][j] || dp[i][j+1] ;
    			}
    			else if(p[j] == s[i] || p[j] == '?')
    			{
    				dp[i + 1][j + 1] =  dp[i][j];
    			}
    		}

    	}

    	int result =  dp[slen][plen];

    	return result;
    }
};
*/
/*V3, reduce space complexity*/
class Solution {
public:
    bool isMatch(string s, string p) {
	int i=0;
    	int j =0;
    	int slen = s.size();
    	int plen = p.size();
    	int dp[plen + 1];
    	 if(plen==0)
    	{
    		if(slen == 0)
    		{
    			return true;
    		}
    		return false;
    	}

    	dp[0] = 1;
    	
	for(j=0; j<plen; j++)
    	{
    		if(p[j] == '*')	
    		{
    			dp[j+1] = dp[j];
    		}
    		else{
    			dp[j+1]=0;
    		}	
    	}

    	int last =0;
    	int current = 0;
	for(i=0;i<slen; i++)
	{
		if(i!=0)
		{
			dp[0] = 0;
		}
		last = dp[0];
		for(j=0;j<plen;j++)
	    	{
			if(p[j] == '*')
    			{
    				current =  last  || dp[j] || dp[j+1] ;//dp[i+1] [j+1] = dp[i][j], dp[i+1][j], dp[i][j+1]
    			}
    			else if(p[j] == s[i] || p[j] == '?')
    			{
    				current = last;
    			}
    			else
    			{
    				current = 0;
    			}
    			last = dp[j+1];
    			dp[j+1] = current;
    		}

    	}

    	int result =  dp[plen];

    	return result;
    }
};

TEST_CASE("Testing Regx Matching") {
	// set up
            Solution sol;
            string s = "abcde";
            string p = "*";

	    // different sections
              SECTION("  matches  ") {
	s = "";
	p = "";
	REQUIRE(sol.isMatch(s, p) );
            }
             SECTION("aa matches aa") {
	s = "aa";
	p = "aa";
	REQUIRE(sol.isMatch(s, p) );
            }

             SECTION("ab matches ***ab") {
	s = "ab";
	p = "***ab";
	REQUIRE(sol.isMatch(s, p) );
            }

 
             SECTION("aa matches a*") {
	s = "aa";
	p = "a*";
	REQUIRE(sol.isMatch(s, p) );
            }

 
             SECTION("aa matches ?*") {
	s = "aa";
	p = "?*";
	REQUIRE(sol.isMatch(s, p) );
            }

 
             SECTION("aab matches aa?") {
	s = "aab";
	p = "aa?";
	REQUIRE(sol.isMatch(s, p) );
            }

 
             SECTION("aaaa matches ***a") {
	s = "aaaa";
	p = "***a";
	REQUIRE(sol.isMatch(s, p) );
            }

 
             SECTION("aabc*dg?as matches *?b**a*") {
	s = "aabc*dg?as";
	p = "*?b**a*";
	REQUIRE(sol.isMatch(s, p) );
            }

             SECTION("a does not matche  ") {
	        s = "a";
	        p = "";
	        REQUIRE(!sol.isMatch(s, p) );
              }

               SECTION("    matches  * ") {
	        s = "";
	        p = "*";
	        REQUIRE(sol.isMatch(s, p) );
              }

              SECTION("aa does not matche a") {
	        s = "aa";
	        p = "a";
	        REQUIRE(!sol.isMatch(s, p) );
              }

             SECTION("aa does not match aaa") {
	        s = "aa";
	        p = "aaa";
	        REQUIRE(!sol.isMatch(s, p) );
             }

             SECTION("abcde does not match ?*c") {
	        s = "abcde";
	        p = "?*c";
	        REQUIRE(!sol.isMatch(s, p) );
             }

             SECTION("abcdeaac does not match ab*e?c") {
	        s = "abcdeaac";
	        p = "ab*e?c";
	        REQUIRE(!sol.isMatch(s, p) );
             }

             SECTION("abcdeaac does not match **?**?b?*ac") {
	        s = "abcdeaac";
	        p = "**?**?b?*ac";
	        REQUIRE(!sol.isMatch(s, p) );
             }

     
   }