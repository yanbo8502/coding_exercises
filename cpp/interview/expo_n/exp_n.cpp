#include "../../tools/tool.h"

class Solution {
private:
    map<int, double> mid;
public:
    double exp(double x, int n) {
                 if(mid.count(n))
                {
                    return mid[n];
                }
    	   double result = 0.0;
                if(x==0)
                {
                    return 0;
                }
                if(n<0)
                {
                    x=1/x;
                    n=-n;
                }
                if(n==0)
                {
                    return 1;
                }
                if(n==1)
                {
                    return x;
                }

                int m = n/2;
                result = exp(x,m)*exp(x, (n-m));
                mid[n] = result;
    	 return result;      
    }
};

class Solution_v2 {

public:
 
//x^n = x^(2^n1 + 2^n2 + ... + 2^nk) = x^(2^n1) * x^(2^n2) *...*x^(2^nk), n1>n2>...>nk
    double exp(double x, int n) {

           double result = 0.0;
                if(x==0)
                {
                    return 0;
                }
                if(n<0)
                {
                    x=1/x;
                    n=-n;
                }
                if(n==0)
                {
                    return 1;
                }
                if(n==1)
                {
                    return x;
                }

                int m = n;
                int t = 1;
                while(m>0)
                {
                    m=m/2;
                    t=t*2;
                }

                double y = 1;
                m = n;
                while(t>1)
                {
                    t=t/2;
                    y=y*y;
                  
                    if(m>=t)
                    {
                        m=m-t;
                        y=y*x;
                    }
                }
                result = y;
                return result;      
    }
  
};

TEST_CASE("Testing x^n") {
	    // set up
	Solution_v2 sol;

	 // different sections
 
	SECTION("3^2") {
		double expected = pow(3,2);
                            double actual = sol.exp(3,2);
		REQUIRE( abs(actual - expected)< 0.0000001);
	}

            SECTION("3.3^11") {
                                 double expected = pow(3.3,11);
                                    double actual = sol.exp(3.3,11);
                REQUIRE( abs(actual - expected)< 0.00000001);
            }
	
  }