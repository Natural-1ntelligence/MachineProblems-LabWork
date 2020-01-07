#include <stdio.h>
#include <stdlib.h>

int main()
{
int row;

printf("Enter a row index: ");
scanf("%d",&row);

// Write your code here
// TEAM - yab2, heshama2, rkadiri2

printf("%d",1);// printing 1 as the first number in a row is always 1
printf(" ");//printing a space
unsigned long k=1; //k is defined as an unsigned long
double e; // e defined as double
double i; //i defined as double
for(i=1; i<row; i++)//calculating the columns 1 to n-1 that are printed
{
e=(row+1-i)/i;
k=k*e;
printf("%lu ",k); //printing the column value with a space
}
printf("%d\n", 1); //printing last column as 1 and entering a new line

return 0;
}
