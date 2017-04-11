
#include <stdio.h>
#include <iostream>
using namespace std;

void quicksort(int *array, int  begin, int end);

int main(int argc, char **argv)  
{
         int a[10] = {6,5,3,7,2,8,5,8,2,4};
         quicksort(a,0,9);
         for(int i=0;i<10;i++)
         {
         	cout<<a[i]<<" ";
         }
}

void quicksort(int *array, int  begin, int end)
{
	if ((end - begin)<=1)
	{
		return;
	}
	int i=begin,j=end;
	int midde_index = (end + begin)/2;
	int middle= array[midde_index];
	array[midde_index]  = array[begin];

	while(i<j)
	{
		while ( j>i && array[j] >= middle)
		{
			j--;
		}
		array[i] = array[j];
		while ( i<j && array[i] <=middle)
		{
			i++;
		}
		array[j] = array[i];

	}
	array[i] = middle;
	quicksort(array, begin, i-1);
	quicksort(array, i+1, end);
	return;

}