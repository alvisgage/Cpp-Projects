#include <iostream>
#include <string.h>
#include <cmath>
#include <cstdlib>
using namespace std;
bool isSquare(long int sum);
main(int argc, char* argv[])
{
	
	long int i;							/* starting index for each proc*/
	long int limit;						/* ending index*/
	long long arr[2];					/* (j+i)(j-i)*/
	long long n;			/* product of two primes*/
	
        cin >> n;

	
	bool square = false;
        i = 0;
        limit = (n * n)/3;
	while(!(square) && i < limit)
	{		    												 
		i++;
		if (isSquare(n + (i * i))){  /* if n + i^2 is a square*/
			square = true; 
		}	 
	}	 

	if (square){/* found square */
		//set j+i, j-1
		arr[0] = long((sqrt(n+(i*i)) + i));
		arr[1] = long((sqrt(n+(i*i)) - i));
	}  	

	

	
	    
		cout << arr[0] << ", " << arr[1] << endl;
	

		
}

bool isSquare(long sum)
{
	bool result = false;
	int mod = sum % 16;
	if (mod == 0 || mod == 1 || mod == 4 || mod == 16)
	{
		if(pow(double(sqrt(sum) + .1),2) ==  sum){
			result = true;
		}
	}
	return result;
}
