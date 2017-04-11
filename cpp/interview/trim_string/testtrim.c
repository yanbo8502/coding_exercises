//评测题目: 字符串原地trim，即把首尾的空格去掉，如" abc def   "转换为“abc def”
// int trim(char* str)
// 要求参数str的地址不变
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int trim(char* str);
int main(int argc, char **argv)  
{
      char a[100] = " 33434 ";
      if(trim(a) >=0)
      {
           printf("%s\n", a);
      }
      else
      {
         printf("invalid input\n");
      }

      char a1[100] = " 3424 dsd  4 ";
      if(trim(a1) >=0)
      {
           printf("%s\n", a1);
      }
      else
      {
         printf("invalid input\n");
      }


      char a2[100] = " ";
      if(trim(a2) >=0)
      {
           printf("%s\n", a2);
      }
      else
      {
         printf("invalid input\n");
      }


      char a3[100] = " \0";
      if(trim(a3) >=0)
      {
           printf("%s\n", a3);
      }
      else
      {
         printf("invalid input\n");
      }
}

int trim(char* str)
{
    if(NULL == str)
    {
      return -1;
    }
    
    int first = 0;
    int end = 0;
    int size = strlen(str);
    bool blank=true;
    if(size == 0)
    {
        return -1;
    }

    for(int i=0;i<size;i++)
    {
       if( ' ' != str[i])
       {
          blank = false;
          break;
       }
    }

    if(blank)
    {
       return -1;
    }

    for(int i=0;i<size;i++)
    {
         if(str[i]!=' ')
         {
            break;
         }
         first++;
    }
    for(int i=size -1 ;i>=0;i--)
    {
         if(str[i]!=' ')
         {
            break;
         }
         end++;
    }
    for(int i=0;i<size - first -end;i++)
    {
        str[i]=str[i+first];
    }
    str[size-first-end]='\0';
    return 0;
}
  
 