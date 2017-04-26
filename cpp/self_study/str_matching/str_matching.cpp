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


/*v1 basic solution with time complexity of O(MN)*/
class Solution {
public:
    int find(string s, string p) {
        int  index = -1;
        int n = s.size();
        int m = p.size();
        int i=0;
        int j=0;
        if(m==0 && n== 0)
        {
              return 0;
        }
        for( i=0; i<n;i++)
        {
              if(i+m > n)
              {
                  break;
              }
              for( j=0;j<m; j++)
              {
                    if(i+j>=n || s[i+j] != p[j])
                    {
                            break;
                    }
              }
              if(j==m)
              {
                  index =i;
                  break;
              }
        }
        
        return index ;
      }

};

/*v2 KMP solution with time complexity of O(M+N)*/
class Solution_v2 {
public:
    int find(string s, string p) {
        int  index = -1;
        int n = s.size();
        int m = p.size();
        int i=0;
        int j=0;
        if(m==0 && n== 0)
        {
              return 0;
        }
        int * next = getNextArray(p);
        for(int k=0;k<m;k++)
        {
              cout<<next[k]<<" ";
        }
        cout<<endl;
        while(i<n)
        {

              if(j==m)
              {
                  index =i - m ;
                  break;
              }

               if( s[i] == p[j])
                {
                          i++;
                          j++;
                          continue;
                }
                j = next[j];
                if(j<0)
                {
                    j = 0;
                    i++;
                    continue;
                }
        }
        delete[] next;
        return index ;
      }

      int* getNextArray(string p)
      {
          int n = p.size();
          int* next = new int[n];
          if(n>0)
          {
              next[0] = -1;
          }
          for(int i=1; i<n; i++)
          {
              next[i] = 0;
              int k = next[i-1];
              char last = p[i-1];
              while(k>=0)
              { 
                  if(p[k] == last )
                  {
                        next[i] = k + 1;
                        break;
                  }
                  k= next[k];
              }
          }
          return next;
      }

};

TEST_CASE("Testing String Matching") {
	    // set up
            Solution_v2 sol;
	    // different sections
 
             SECTION("cab in abbccabacceae at 4") {
                REQUIRE(sol.find("abbccabacceae", "cab") == 4 );
            }
            SECTION("cabc not in abbccabacceae at ") {
                REQUIRE(sol.find("abbccabacceae", "cabc") == -1);
            }


             SECTION("ababc in abbcabaeababababcabacceae at 12") {
                REQUIRE(sol.find("abbcabaeababababcabacceae", "ababc") == 12 );
            }
            SECTION("ababc not in abbcabaeababababacabacceae") {
                REQUIRE(sol.find("abbcabaeababababacabacceae", "ababc") == -1);
            }

            SECTION(" empty in abc at 0") {
                REQUIRE(sol.find("abc", "") == 0);
            }

             SECTION("a not  in  empty") {
                REQUIRE(sol.find("", "a") == -1 );
            }

             SECTION("empty in empty") {
                REQUIRE(sol.find("", "") == 0 );
            }
   }