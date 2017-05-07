#include "../../tools/tool.h"

class Solution {

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
    	vector<string> result;
    	int visit[s.size()];
    	vector<vector<string>> next;
    	for(int i=0;i<s.size();i++)
    	{
    		visit[i] =0;
    		vector<string> v;
    		next.push_back(v);
    	}
    	wordBreak(s, 0, wordDict, visit, next);
    	result = next[0];
    	return result;
        
    }
    vector<string> wordBreak(string s, int pos, vector<string>& wordDict, int* visit, vector<vector<string>>& next) {
    	vector<string> partial;
    	string next_s = s.substr(pos);
    	for(int i=0;i<wordDict.size();i++)
    	{
    		string p = wordDict[i];
    		if(preMatch(next_s, p))
    		{
    			if(next_s.size() > p.size())
    			{
    				int next_pos = pos + p.size();
    				if(visit[next_pos] == 0)
    				{
    					cout<<next_pos<<endl;
    					vector<string> next_partial = wordBreak(s, next_pos, wordDict, visit, next);
    					for (int i = 0; i < next_partial.size(); ++i)
    					{
    						partial.push_back(p + " " + next_partial[i] );
    					}
    					visit[next_pos] = 1;
    					next[next_pos] = next_partial;
    				}
    				else
    				{
    					vector<string> next_partial = next[next_pos];
    					for (int i = 0; i < next_partial.size(); ++i)
    					{
    						partial.push_back(p + " " + next_partial[i] );

					}
    					
    				}
    			}
    			else
    			{
    				partial.push_back(p);
    			}
    			   			
    		}

    	}
    	next[pos] = partial;
    	return partial;
        
    }
    bool preMatch(string s, string p)
    {
    	if(p.size()>s.size())
    		return false;
    	for(int i=0;i<p.size();i++)
    	{
    		if(s[i] != p[i])
    		{
    			return false;
    		}
    	}

    	return true;
    }
};
class Solution_v2 {

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
    	vector<string> result;
    	int visit[s.size()+1];
    	vector<vector<string>> next;
    	for(int i=0;i<=s.size();i++)
    	{
    		visit[i] =0;
    		vector<string> v;
    		next.push_back(v);
    	}
             
    	for(int i=s.size() -1;i>=0;i--)
    	{		
                             vector<string> next_r;
    		string next_s = s.substr(i);

    		for(int k =0; k<wordDict.size();k++)
    		{
    			string p = wordDict[k];
    			if(!preMatch(next_s, p))
    			{
    				continue;
    			}
    			int next_pos = i + p.size();
    			vector<string> next_partial = next[next_pos];

    			
    			for(int j =0;j<next_partial.size();j++)
    			{
    				string part = p + " " + next_partial[j];
    				next_r.push_back( part);
    				cout<<i<<" "<<part<<endl;
    			}
    			if(next_pos == s.size())
    			{
    				next_r.push_back(p);
    				cout<<i<<" "<<p<<endl;
    			}
    			
    		}
    		next[i]=	    next_r;		 
    	}
    	result = next[0];
    	return result;
        
    }

     bool preMatch(string s, string p)
    {
    	if(p.size()>s.size())
    		return false;
    	for(int i=0;i<p.size();i++)
    	{
    		if(s[i] != p[i])
    		{
    			return false;
    		}
    	}

    	return true;
    }
  
};

class Solution_v3 {

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        stack<int> pos_his;
        stack<int> next_pos_his;
        vector<string> result;
        int visit[s.size()+1];
        vector<vector<string>> next;
        for(int i=0;i<=s.size();i++)
        {
            visit[i] =0;
            vector<string> v;
            next.push_back(v);
        }
        next_pos_his.push(0);
        visit[0] = 1;
        while(!next_pos_his.empty())
        {  
            bool hit = false;     
            int i = next_pos_his.top();
            

             visit[i] = 1;
            cout<<i<<endl;
            string next_s = s.substr(i);
            //cout<<next_s<<endl;
             vector<string> next_r;
      
            for(int k =0; k<wordDict.size();k++)
            {
                    string p = wordDict[k];
                    if(!preMatch(next_s, p))
                    {
                         continue;
                    }
                    
                    int next_pos = i + p.size();
                    if(next_pos<s.size())
                    {
                             vector<string> next_partial = next[next_pos];
                             for(int j =0;j<next_partial.size();j++)
                             {
                                    string part = p + " " + next_partial[j];
                                    next_r.push_back( part);
                                   // cout<<i<<" "<<part<<endl;
                             }
                    }
                        
                  
                     if(next_pos == s.size())
                    {
                        next_r.push_back(p);
                        continue;
                    }

                    if(next_pos < s.size() && visit[next_pos] == 0)
                    {
                        next_pos_his.push(next_pos);
                        hit = true;
                    }               
            }
            next[i] = next_r;
            if(hit == false)
            {
                next_pos_his.pop();
            }
         
        }
        
        result = next[0];
        return result;
        
    }

     bool preMatch(string s, string p)
    {
        if(p.size()>s.size())
            return false;
        for(int i=0;i<p.size();i++)
        {
            if(s[i] != p[i])
            {
                return false;
            }
        }

        return true;
    }
  
};

TEST_CASE("Testing worrd breaking 2") {
	    // set up
	Solution_v3 sol;
	string s = "catsanddog";
	string dict_array[5] = {"cat", "cats", "and","sand", "dog"};
	vector<string> dict;
	for(int i=0;i<5;i++)
	{
		dict.push_back(dict_array[i]);
	 // different sections
	}
 
	SECTION("catsanddog") {
		string result_array[2] = {"cats and dog", "cat sand dog"};
		vector<string> expect_result;
		for(int i=0;i<2;i++)
		{
			expect_result.push_back(result_array[i]);
		 // different sections
		}
		vector<string> result = sol.wordBreak(s, dict);
		cout<<"print word break results:"<<endl;
		for (int i = 0; i < result.size(); ++i)
		{
			/* code */
			cout<<result[i]<<endl;
		}
		cout<<"done"<<endl;

		cout<<"print expected results:"<<endl;
		for (int i = 0; i < expect_result.size(); ++i)
		{
			/* code */
			cout<<expect_result[i]<<endl;
		}
		cout<<"done"<<endl;
		REQUIRE(Tool::compareTwoSets<string>(result, expect_result) );
	}

	SECTION("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") {
		s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	               //s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaa";
                            string dict_array1[10] = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
		dict.clear();
		for(int i=0;i<10;i++)
		{
			dict.push_back(dict_array1[i]);
		 // different sections
		}
		
		vector<string> result = sol.wordBreak(s, dict);
		cout<<"print word break results:"<<endl;
		for (int i = 0; i < result.size(); ++i)
		{
			
			cout<<result[i]<<endl;
		}
		cout<<"done"<<endl;
	}

    SECTION("aaaaaaa") {
        s="aaaaaaa";
        string dict_array3[2] = {"aaaa","aaa"};
        dict.clear();
        for(int i=0;i<2;i++)
        {
            dict.push_back(dict_array3[i]);
         // different sections
        }
        string result_array3[2] = {"aaaa aaa", "aaa aaaa"};
       vector<string> expect_result;
        for(int i=0;i<2;i++)
        {
            expect_result.push_back(result_array3[i]);
         // different sections
        }
        vector<string> result = sol.wordBreak(s, dict);
        cout<<"print word break results:"<<endl;
        for (int i = 0; i < result.size(); ++i)
        {
            /* code */
            cout<<result[i]<<endl;
        }
        cout<<"done"<<endl;

        cout<<"print expected results:"<<endl;
        for (int i = 0; i < expect_result.size(); ++i)
        {
            /* code */
            cout<<expect_result[i]<<endl;
        }
        cout<<"done"<<endl;
        REQUIRE(Tool::compareTwoSets<string>(result, expect_result) );
    }
  }