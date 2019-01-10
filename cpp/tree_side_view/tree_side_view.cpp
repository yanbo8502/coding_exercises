#include "../tools/tool.h"


class Solution {

public:

  treenode* makeTree(vector<string>& nodes,vector<string>& rels)
  {
        map<string, treenode*> treenodes;
        vector<string> nodeshasparent;
        treenode* root =NULL;
        for (std::vector<string>::iterator i= nodes.begin(); i!= nodes.end(); ++i)
        {
              string node = *i;
              string delim = ",";
              vector<string> items;
              Tool::split2(node, delim, items);
              string id = items[0];
              treenode*  tn = new treenode();
              tn->value = items[1];
              treenodes[id] = tn;
        }

        for (std::vector<string>::iterator i= rels.begin(); i!= rels.end(); ++i)
        {
                string rel = *i;
                string delim = ",";
                vector<string> items;
                Tool::split2(rel, delim, items);
                string parentid = items[0];
                string leftid = "";
                string rightid  = "";
                if(items.size()>1)
                {
                    leftid = items[1];
                }
                if(items.size()>2)
                {
                    rightid = items[2];
                }
                treenode* parent = treenodes[parentid];
                if(leftid!="")
                {
                  parent->left = treenodes[leftid];
                  nodeshasparent.push_back(leftid);
                }
                if(rightid!="")
                {
                  parent->right = treenodes[rightid];
                  nodeshasparent.push_back(rightid);
                }
         }
        //find root
          for(auto iter = treenodes.begin(); iter != treenodes.end(); iter++)  
           {
                      string treenode_id = iter->first;
                      auto it = find(nodeshasparent.begin(), nodeshasparent.end(), treenode_id);
                      if ( nodeshasparent.end()==it)
                      {
                          root = iter->second;
                          break;
                      }              
            }

           return root;
  }

    void print(treenode* root)
    {
        int print_deep = 0; 
        print_recursive(root,  print_deep, 1);
    }

    string getSideView(treenode* root)
    {
        int print_deep = 0; 
        //return print_recursive(root,  print_deep, 1);
        //return print_recursive_vector(root,  print_deep, 1);
        return print_stack(root);
    }

      string print_stack(treenode* root)
      {
           string current_result = "";
            stack<pair<treenode*,int>> tovisit;

            tovisit.push( make_pair(root, 1));
            int current_deep = 1;
            int print_deep = 0;
            while(!tovisit.empty())
            {
                  auto cur = tovisit.top();
                  auto cur_node = cur.first;
                  auto cur_deep = cur.second;
                  tovisit.pop();
                  if(cur_deep>print_deep)
                  {
                         if(current_result!="")
                          {
                                current_result += "," + cur_node->value;
                          }
                          else
                          {
                               current_result =  cur_node->value;
                          }
                         print_deep++;
                  }
                  if(cur_node->left!=NULL)
                  {
                        tovisit.push(make_pair(cur_node->left, cur_deep+1 ));
                  }
                  if(cur_node->right!=NULL)
                  {
                      tovisit.push(make_pair(cur_node->right, cur_deep+1 ));
                  }

            }
            return current_result;
      }
      string print_recursive(treenode* root, int& print_deep, int current_deep)
     {
        string current_result = "";
          if(NULL == root)
         {
            return current_result;
         }

          if(current_deep>print_deep)
          {
                cout<<"["<<root->value<<"]"<<",";
                print_deep+=1;
                current_result =  root->value ;
          }
          else{
            cout<<root->value<<",";
          }
           if(NULL != root->right)
           {
                 string next =  print_recursive(root->right, print_deep,current_deep+1);
                 if (""!=next && ""!=current_result)
                 {
                    current_result += "," + next;
                }else if(""!=next)
                {
                    current_result = next;
                }
           }
           if(NULL != root->left)
           {
                  string next = print_recursive(root->left, print_deep,current_deep+1);
                  if (""!=next && ""!=current_result)
                 {
                    current_result += "," + next;
                }else if(""!=next)
                {
                    current_result = next;
                }
           }
           return current_result;
      }

    string print_recursive_vector(treenode* root, int& print_deep, int current_deep)
    {
       
        vector<string> printlist;
       print_recursive2(root,  print_deep, 1,printlist);
       string result="";
       for (std::vector<string>::iterator i = printlist.begin(); i != printlist.end(); ++i)
       {
           if(""!=result)
           {
                result+="," + *i;
           }
           else{
               result=*i;
           }
       }
       return result;
    }

      void print_recursive2(treenode* root, int& print_deep, int current_deep, vector<string>& result)
     {
          if(NULL == root)
         {
            return;
         }

          if(current_deep>print_deep)
          {
                cout<<"["<<root->value<<"]"<<",";
                print_deep+=1;
                result.push_back(root->value);
          }
          else{
            cout<<root->value<<",";
          }
           if(NULL != root->right)
           {
                  print_recursive2(root->right, print_deep,current_deep+1,result);
           }
           if(NULL != root->left)
           {
                  print_recursive2(root->left, print_deep,current_deep+1,result);
           }
      }

};


TEST_CASE("Testing tree right side view  1") {
	    // set up
	Solution sol;
       string nodes_text="1,a\n2,b\n3,c\n4,d\n5,e\n6,f\n7,g\n8,h\n9,i\n10,j\n11,k\n12,l\n13,m\n14,n";
       string rels_text = "1,2,3\n3,4,5\n4,6,\n2,7,\n7,8,\n8,9,10\n9,13,\n10,11,12\n13,14,";
       std::vector<string> nodes;
       std::vector<string> rels;
       string delim = "\n";
        Tool::split2(nodes_text, delim, nodes);
         Tool::split2(rels_text, delim, rels);
         treenode* root = sol.makeTree(nodes, rels);
         string result = sol.getSideView(root);
         string expected_result = "a,c,e,f,j,l,n";
      
          REQUIRE(expected_result == result);	
  }

 