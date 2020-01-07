// partners: rkadiri2, yab2, heshama2
#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b);
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
	for(int g = 2; g < number; g++) { // Return 1 for prime n and 0 for nonprime n
		if(number%g==0)
			return 0;		// Checking Divisibility
	}
	return 1;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
	int out = 0;		// Keep 0 as default return
	for( int n = a; n <= b; n++) {
		for( int k = 2; k < n; k++) {
			if( is_prime(k) & is_prime(n/k) & (n%k == 0) ) {
				printf("%d\n", n);
				out = 1;	//Return 1 if we find a semiprime 
				break;		//Stops checking for semiprimes
			}
		}
	}
return out;
}

