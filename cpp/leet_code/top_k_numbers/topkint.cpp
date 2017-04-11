
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

/******unit test*****/
#define CATCH_CONFIG_MAIN
#include "../../tools/catch.hpp"
/***************/
using namespace std;

struct num_count
{
	int value;
	int count;
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
    	for(int i =0; i<nums.size(); i++)
    	{
    		int value = nums[i];
    		auto it = counts.find(value);
		if(it == counts.end()) {
		    //没找到
		    counts[value] = 1;
		}
		else {
		    //找到
		    counts[value]++;
		}
    	}

    	 for(auto it=counts.begin();it!=counts.end();++it)
       	{
       		num_count num;
       		num.value = it->first;
       		num.count = it->second;
       		//cout<<"key: "<<it->first <<" value: "<<it->second<<endl;
       		num_counts.push_back(num);
       	} 

       	int n = num_counts.size();
       	bigRootHeap(num_counts, n);
       	
       	for(int i=0; i < k; i++)
       	{
       		swap(num_counts, 0, n-1-i);
       		bigRootHeap(num_counts, n-i -1);
       	}
       	vector<int> result;
       	for(int i=0; i < k; i++)
       	{
       		result.push_back(num_counts[n-1-i].value);
       	}

       	return result;

    }

    void bigRootHeap(std::vector<num_count>& array,int n)
    {
    	for(int i=n/2;i>=0;i--)
    	{
    		if(2*i +1 < n && array[i].count < array[2*i +1].count)
    		{
    			swap(array, i, 2*i + 1);
    		}
    		 if(2*i +2 < n &&  array[i].count < array[2*i + 2].count)
    		{
    			swap(array, i, 2*i + 2);
    		}
    	}
    }

    void swap(std::vector<num_count>& array, int i, int j)
    {
    	num_count temp;
    	temp = array[i];
    	array[i] = array[j];
    	array[j]  = temp;
    }

private:
    std::map<int,int> counts;
    std::vector<num_count> num_counts;
};

/*
int main(int argc, char **argv)  
{
         int a[13] = {6,5,3,7,2,8,5,8,2,4, 8,3, 1};
         vector<int> nums;
         for(int i=0;i<13;i++)
         {
         	nums.push_back(a[i]);
         }
         Solution sol;
         vector<int> result = sol.topKFrequent(nums, 2); 
         for(int i=0;i<result.size();i++)
         {
         	cout<<result[i]<<" ";
         }
}
*/

TEST_CASE("Testing TopK") {
    // set up
     Solution sol;
     int topk = 2;

    // different sections
    SECTION("test 13 numbers with top 2") {
         int a[13] = {6,5,3,7,2,8,5,8,2,4, 8,3, 1};
         vector<int> nums;
         for(int i=0;i<13;i++)
         {
              nums.push_back(a[i]);
         }
         vector<int> result = sol.topKFrequent(nums, topk); 
        REQUIRE(result.size()==2);
       bool assert =  result[0] == 8;
        REQUIRE(assert);
        assert = result[1] == 2 || result[1] == 3 || result[1] == 5;
        REQUIRE(assert ==  true );
        for(int i=0;i<result.size();i++)
         {
            cout<<result[i]<<" ";
         }
    }

        SECTION("test 17 numbers with top 2") {
         int a[17] = {6,5,3,7,2,8,5,8,2,4, 8,3, 1, 3, 8, 1, 3};
         vector<int> nums;
         for(int i=0;i<17;i++)
         {
              nums.push_back(a[i]);
         }
         vector<int> result = sol.topKFrequent(nums, topk); 
        REQUIRE(result.size()==2);
        bool assert = result[0] == 3 || result[0] == 8;
        REQUIRE(result[0] == 8);
        assert =  result[1] == 3 || result[1] == 8;
        REQUIRE(assert ==  true );
        for(int i=0;i<result.size();i++)
         {
            cout<<result[i]<<" ";
         }
    }

}
