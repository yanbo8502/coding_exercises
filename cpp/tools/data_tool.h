#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

struct Matrix
{
	int width;
	int height;
	int** data;
};

template<typename T>
struct TreeNode
{
	T value;
	TreeNode* left;
	TreeNode* right;
};



class Tool
{
public:
	static Matrix* getMatrix(string filename);
	static void split1(const  string& s, const string& delim, vector<string>& elems);
	static void split2(const  string& s, const string& delim, vector<string>& elems);
	static void split3(const  string& s, const string& delim, vector<string>& elems);
	static Matrix* getGraphMatrixFromEdgeFiles(string filename);
	template<typename T>
	static TreeNode<T>*  getTree(string filename);
	template<typename T>
	static bool compareTwoSets(vector<T> v1, vector<T> v2);
};
/*
从第1行开始表示矩阵每一行的数据，用逗号隔开。
*/
Matrix* Tool::getMatrix(string filename)
{
	Matrix* matrix = new Matrix();
	 char buffer[256];
   	 ifstream file(filename.c_str());
	if (! file.is_open())
	 {
		cout << "Error opening file"; exit (1);
	}
	int width=0;
	int height = 0;
	vector<vector<int>> matrix_v;
	while (!file.eof())
	{
		vector<int> row;
		file.getline(buffer,100);
		//cout<<buffer<< endl;
		string line(buffer);
		vector<string> elems;
		string delim = ",()";
		Tool::split3(line,  delim, elems);

		if(height>0 && width !=elems.size())
		{
			cout<<"invalid matrix in the file at line "<<height<<endl;
			throw "invalid matrix in the file!";			
		}
		for (int i = 0; i < elems.size(); ++i)
		{
			cout<<elems[i]<<" ";
			row.push_back(atoi(elems[i].c_str()));
		}
		cout<<endl;

		width = elems.size();

		height++;
		matrix_v.push_back(row);
	}
	cout<<"finish"<<endl;
	int **data;
	data = new int*[matrix_v.size()];
	for (int i = 0; i <matrix_v.size() ; ++i)
	{
		data[i] = new int[width];
		for (int j= 0; j< width; ++j)
		{
			data[i][j] = matrix_v[i][j];
		}
	}
	matrix->height = matrix_v.size();
	matrix->width =width;
	matrix->data = data;
	return matrix;
}
Matrix* Tool::getGraphMatrixFromEdgeFiles(string filename)
{
	Matrix* matrix = new Matrix();

	 ifstream file(filename.c_str());
	if (! file.is_open())
	 {
		cout << "Error opening file"; exit (1);
	}
	int size=0;
	int height = 0;
	 char buffer[256];
	if (!file.eof())
	{
		file.getline(buffer,100);
		//cout<<buffer<< endl;
		size = atoi(buffer);
	}

	int **data;
	data = new int*[size];
	for (int i = 0; i <size ; ++i)
	{
		data[i] = new int[size];
		for (int j= 0; j< size; ++j)
		{
			data[i][j] = -1;
		}
	}

	while (!file.eof())
	{
		file.getline(buffer,100);
		cout<<buffer<< endl;
		string line(buffer);
		vector<string> elems;
		string delim = ",()";
		Tool::split3(line,  delim, elems);
		if(3 !=elems.size())
		{
			cout<<"invalid edge row in the file at line "<<height<<endl;
			throw "invalid edge row in the file!";			
		}
		int i = atoi(elems[0].c_str());
		int j = atoi(elems[1].c_str());
		int w = atoi(elems[2].c_str());
		data[i][j] = w;
		height++;
		if(height>size)
		{
			break;
		}
	}

	matrix->height = size;
	matrix->width =size;
	matrix->data = data;
	return matrix;
}

/*
  support typename string first
*/
template<typename T>
TreeNode<T>* Tool::getTree(string filename)
{
	TreeNode<T>* root = NULL;
	string root_key="";
	 char buffer[256];
   	 ifstream file(filename.c_str());
	if (! file.is_open())
	 {
		cout << "Error opening file"; exit (1);
	}
	int height = 0;
	map<string, TreeNode<T>*> node_map;
	while (!file.eof())
	{
		file.getline(buffer,100);
		//cout<<buffer<< endl;
		string line(buffer);
		vector<string> elems;
		string delim = ",";
		Tool::split3(line,  delim, elems);


		if(elems.size()<6)
		{
			cout<<"invalid three node line at line "<<height<<endl;
			throw "invalid three node line !";			
		}

		//root
		string key =  elems[0];
		if(0 == height)
		{
			root_key = key;
		}
		TreeNode<T>* node;
		auto it =node_map.find(key);
		if (it==node_map.end())
		{
			node = new TreeNode<T>();
			node->left = NULL;
			node->right= NULL;
			node_map[key] = node;
		}
		else
		{
			node = node_map[key];
		}
		node->value = elems[1];

		for (int i = 1; i <= 2; ++i)
		{
			string sub_key = elems[2*i];
			if(sub_key == "0")
			{
				continue;
			}
			if(sub_key == root_key)
			{
				root_key = key;
			}
			TreeNode<T>* node1 = NULL;
			 it =node_map.find(sub_key);
			if (it==node_map.end())
			{
				node1 = new TreeNode<T>();
				node1->left = NULL;
				node1->right= NULL;
				node_map[sub_key] = node1;
			}
			else
			{
				node1 = node_map[sub_key];
			}
			node1->value = elems[2*i+1];

			if(1 == i)
			{
				node->left = node1;	
			}
			else
			{
				node->right = node1;
			}

		}
		height++;
	}

	auto it =node_map.find(root_key);
	if ( node_map.end()!=it)
	{
		root = node_map[root_key];
	}
	return root;
}

void Tool::split1(const  string& s, const string& delim, vector<string>& elems)
{
	size_t pos = 0;
	size_t len = s.length();
	 size_t delim_len = delim.length();
	if (delim_len == 0) return;
	while (pos < len)
	{
		 int find_pos = s.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
}

void Tool::split2(const  string& source, const string& delim, vector<string>& elems)
{
	    size_t pos = 0;
	    size_t len = source.length();
	    size_t delim_len = delim.length();
	    if (delim_len == 0) return;
	    char *s = strdup(source.c_str());
	    const char * d =  delim.c_str();
	     elems.push_back(strtok(s, d));
	     char *p;
	    while((p = strtok(NULL, d)))
	     {

	     	 elems.push_back(p);
	     	
	     }
}

void Tool::split3(const  string& source, const string& delim, vector<string>& elems)
{
	    size_t pos = 0;
	    size_t len = source.length();
	    size_t delim_len = delim.length();
	    if (delim_len == 0) return;
	    char *s = strdup(source.c_str());
	    const char * d =  delim.c_str();
	     char *p;
	    while((p = strsep(&s, d)))
	     {
	     	if(*p==0)
	     	{
	     		continue;
	     	}
	     	 elems.push_back(p);
	     }
}

template<typename T>
bool Tool::compareTwoSets(vector<T> v1, vector<T> v2)
{
	if(v1.size()!=v2.size())
	{
		return false;
	}
	map<T, int> v1m;
	map<T, int> v2m;
	typedef typename std::vector<T>::iterator iterator;
	for (iterator i = v1.begin(); i != v1.end(); ++i)
	{
		string key = *i;
		auto it =v1m.find(key);
		if (it==v1m.end())
		{
			v1m[key] = 1;
		}
		else
		{
			v1m[key]++;
		}
	}

	for (iterator i = v2.begin(); i != v2.end(); ++i)
	{
		string key= *i;
		auto it =v2m.find(key);
		if (it==v2m.end())
		{
			v2m[key] = 1;
		}
		else
		{
			v2m[key]++;
		}
	}
	//compare v1m and v2m
	for( auto iter=v1m.begin();     iter!=v1m.end();   iter++)
	{
		T key= iter->first;

		 int value= iter->second;

		 auto it =v2m.find(key);
		if ( v2m.end()!=it)
		{
			if(v2m[key] != value)
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	 }

	 return true;

}