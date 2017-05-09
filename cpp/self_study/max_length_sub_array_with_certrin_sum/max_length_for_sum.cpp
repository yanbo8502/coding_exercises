#include "../../tools/tool.h"

class Solution {
private:
    map<int, int> sum_map;
public:
    int getMaxLength(int* a, int n, int sum) {
                int max_length = -1;
                int s[n];
                int sum_end = -1;
                for(int i=0;i<n;i++)
                {
                    s[i] = 0;
                }
                int acc_sum = 0;
                sum_map[0] = -1;
                for(int i=0;i<n;i++)
                {
                    acc_sum+=a[i];
                    int dif = acc_sum -  sum;
                    if(sum_map.count(dif))
                    {
                        int j = sum_map[dif]; 
                        int length = i-j;
                        if(length>max_length)
                        {
                            max_length = length;
                            sum_end = i;
                        }
                    }

                    if(sum_map.count(acc_sum) == 0)
                    {
                        sum_map[acc_sum] = i;
                    }
                }
                cout<<sum_end<<endl;
    	 return max_length;      
    }

};

TEST_CASE("Testing x^n") {
	    // set up
	Solution sol;
             int a[11] = {1,3,-2,4,-3,2,-2,5,9,-7,6};

	 // different sections
 
	SECTION("sum 2 ->length 6") {
		REQUIRE(sol.getMaxLength(a,11, 2) == 6);
	}

            SECTION("sum 9 ->length 9") {
                    REQUIRE(sol.getMaxLength(a,11, 9 ) == 9);
         }

         SECTION("sum 10 ->length10") {
                    REQUIRE(sol.getMaxLength(a,11, 10 ) == 10);
         }

         SECTION("sum 11 ->length  5") {
                    REQUIRE(sol.getMaxLength(a,11, 11 ) == 5);
         }

          SECTION("sum 12 ->length  9") {
                    REQUIRE(sol.getMaxLength(a,11, 12 ) == 9);
         }

          SECTION("sum 6 ->length  4") {
                      int a1[11] = {22,3,-2,4,-3,2,-2,5,9,-7,6};
                    REQUIRE(sol.getMaxLength(a1,11,23 ) == 3);
         }

         SECTION("sum 6 ->length  1") {
                     int a1[11] = {22,3,-2,4,-3,2,-2,5,9,-7,6};
                    REQUIRE(sol.getMaxLength(a1,11, 22 ) == 1);
         }

	
  }