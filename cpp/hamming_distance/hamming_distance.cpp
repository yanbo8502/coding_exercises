#include "../tools/tool.h"

class Solution {

public:

  int distance(int a, int b)
   {
          return  distance3( a,  b);
   }

   int distance1(int a, int b)
   {
          unsigned int xorr = a^b;
          int sum = 0;
          for( int i=0;i<32;i++)
          {
              unsigned int is1 = (xorr&(1<<i));
              //printf("%d,", is1);
              sum = sum +  (is1>0 ?1:0);
          } 
          // printf("\n");
          return sum;
   }

    int distance2(int a, int b)
   {
          unsigned int xorr = a^b;
          int sum = 0;
         while(xorr>0)
          {
              if(xorr%2 == 1)
              {
                  sum+=1;
              }
             xorr /= 2;
          } 
          // printf("\n");
          return sum;
   }

   int distance3(int x, int y) {
        int res = 0, exc = x ^ y;
        while (exc) {
            ++res;
            exc &= (exc - 1);
        }
        return res;
    }
}; 



void tobin(int a,char* str){
      char *p=(char*)&a,c=0,f=0,pos=-1;//p指向a的首地址
      for(int o=0;o<4;++o){
              for(int i=0;i<8;++i){ 
                    c=p[3-o]&(1<<(7-i));
                     if(!f&&!(f=c))
                        continue;
                     str[++pos]=c?'1':'0';
                }
        }
}


TEST_CASE("Testing hash distance 1") {
	    // set up
	Solution sol;
             int seed = 1024;
             srand((int)time(0));
             std::map<int, int> number_and_dis;
             std::vector<int> expected_dis;
             std::vector<int> bit_pos;
             for(int i=0;i<32;i++)
            {
                bit_pos.push_back(i);
            }
            for(int x=0;x<10;x++)
            {
                int dis = rand()%10;
                printf("%d\n", dis);
                std::random_shuffle(bit_pos.begin(), bit_pos.end());
                int mask = 0;
                for(int i=0;i<dis;i++)
                {
                            mask += 1<<bit_pos[i];
                }
                int target_number = mask^seed;
                number_and_dis[target_number] = dis;

            }

           for(auto iter = number_and_dis.begin(); iter != number_and_dis.end(); iter++)  
            {
                char str[33] = "00000000000000000000000000000000";
                //char* str = new char[32];
              
                int target_number = iter->first;
                int expect_dis = iter->second;
                // printf(str);
                tobin(seed,str);
                printf(str);
                printf("\n");
                tobin(target_number,str);
                printf(str);
                printf("\n");
                /*
                                 seed=0b00000000111111110000111111110000;
                 target_number=0b00001010111101110000111111110101;
                 expect_dis = 5
                 */
                 int dis = sol.distance(seed, target_number);
                 printf("%d == %d\n", dis, expect_dis);
                 REQUIRE(dis == expect_dis);
            }
	
  }

  TEST_CASE("Testing hash distance time cost") {
Solution sol;
             int seed = 1024;
             srand((int)time(0));
             std::map<int, int> number_and_dis;
             std::vector<int> expected_dis;
             std::vector<int> bit_pos;
             for(int i=0;i<32;i++)
            {
                bit_pos.push_back(i);
            }
            for(int x=0;x<10;x++)
            {
                int dis = rand()%10;
                printf("%d\n", dis);
                std::random_shuffle(bit_pos.begin(), bit_pos.end());
                int mask = 0;
                for(int i=0;i<dis;i++)
                {
                            mask += 1<<bit_pos[i];
                }
                int target_number = mask^seed;
                number_and_dis[target_number] = dis;

            }

            int i =0;
            long start = time(0);
          while(i<10000000)
          {
                for(auto iter = number_and_dis.begin(); iter != number_and_dis.end(); iter++)  
                {
                    int target_number = iter->first;
                    int expect_dis = iter->second;           
                     int dis = sol.distance(seed, target_number);
                     if(dis>20)
                     {
                            break;
                               printf("break when %d\n", dis);
                     }
                }
                i++;
          }
          long end = time(0);
          double duration = (end - start)*1.0;
          printf("100000000 simhash cost %f seconds\n", duration );
           

  }
  void func(map<int, int> number_and_dis, int seed);
  TEST_CASE("Testing hash distance time cost with multi thread") {
Solution sol;
             int seed = 1024;
             srand((int)time(0));
             std::map<int, int> number_and_dis;
             std::vector<int> expected_dis;
             std::vector<int> bit_pos;
             for(int i=0;i<32;i++)
            {
                bit_pos.push_back(i);
            }
            for(int x=0;x<10;x++)
            {
                int dis = rand()%10;
                printf("%d\n", dis);
                std::random_shuffle(bit_pos.begin(), bit_pos.end());
                int mask = 0;
                for(int i=0;i<dis;i++)
                {
                            mask += 1<<bit_pos[i];
                }
                int target_number = mask^seed;
                number_and_dis[target_number] = dis;

            }

 
            long start = time(0);

          vector<std::thread*> threads ;
          for(int i=0;i<5;i++)
          {
                std::thread *t = new thread(func, number_and_dis, seed);
                threads.push_back(t);
          }
          for(int i=0;i<5;i++)
          {
                threads[i]->join();
          }
          long end = time(0);
          double duration = (end - start)*1.0;
          printf("500000000 simhash cost %f seconds\n", duration );
           

  }

  void func(map<int, int> number_and_dis, int seed)
  {
       Solution sol;
        int i =0;
        while(i<10000000)
          {
                for(auto iter = number_and_dis.begin(); iter != number_and_dis.end(); iter++)  
                {
                    int target_number = iter->first;
                    int expect_dis = iter->second;           
                     int dis = sol.distance(seed, target_number);
                        //printf("%d: %d\n", target_number, seed);
                       //printf("%d == %d\n", dis, expect_dis);
                     if(dis>20)
                     {
                            break;
                               printf("break when %d\n", dis);
                     }
                      //REQUIRE(dis == expect_dis);
                }
                i++;
          }
  }