
	////// standard libraries //////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

	////// defined constants //////
// maximum possible string length
#define MAX_STRLEN 256
// limit to the number till which the primes will be checked
#define LIMIT_PRIME 1000000
// limit / 2
#define LEN_PRIME 500000
// limit to the number of prime divisors of a number
#define LIMIT_DIV 1000
// maximum possible digits with which we want to deal
#define MAX_DIGITS 20
// maximum possible digits in a hexadecimal number
#define MAX_HEX_DIGITS 30

	////// global variables //////
// array which stores the prime numbers
unsigned int primes[LEN_PRIME];
// number of primes stored
int numPrimes;
// prime divisors of a number
int priDiv[LIMIT_DIV][2];
// number of prime divisors
int numPriDiv;

	////// data-structures //////
// for hexdecimal numbers
typedef struct
{
	char dig[MAX_HEX_DIGITS];   // number
	int len;                    // number of digits
	char sign;                  // sign
} hexadec;

	////// functions //////
		// in all0.c //
// sum of consecutive integers
unsigned int sumInt(int n);
// sum of squares of consecutive integers
unsigned int sumIntSquares(int n);
// floor function in division
int floorDivision(int n,int m);
// ceiling function in division
int ceilDivision(int n,int m);
// finds the integer square root of a number
int sqrtInt(unsigned int i);
// detects whether a number is prime or not
int isPrime(int i);
// finds the sum of the digits of the input integer
int digitSum(int n);
// finds the sum of squares of the digits of the input integer
int digitSquareSum(int n);
// sum of factorial of the digits of the input integer
int digitFactorialSum(int num);
// finds the number of divisors of the input integer
int numDivisors(int i);
// finds the gcd of 2 numbers
int gcd(int a, int b);
// checks whether the input integer is palindrome or not
int ispalin(int a);
// convert the string to integer
int str2int(char *str);
// generates the prime numbers into the array 'primes'
void generatePrimeNumbers();
// show the primes from the 'start'th prime number till 'end'th
void showPrimeNumbers(int start,int end);
// decomposition of a number into its prime divisors
void generatePrimeDivisors(int n);
// show the prime divisors
void showPrimeDivisors();
// evaluate the euler totient function
int eulerTotient(int n);
// evaluate the ratio n/phi(n)
double eulerRatio(int n);
// checks if it is a bouncy number or not
int bouncyNumber(unsigned long int num);
// initialize a hexadecimal number
hexadec initHexadec();
// convert the string to hexadecimal number
hexadec str2hex(char *str);
// get a hexadecimal number from the user
hexadec getHexadec();
// display hexadecimal number
void showHexadec(hexadec in);
// add 2 hexadecimal numbers
hexadec addHexadec(hexadec a,hexadec b);
// check for a > b
int isGreater(hexadec a,hexadec b);
// check for a < b
int isLesser(hexadec a,hexadec b);
// check for a >= b
int isGreaterOrEqual(hexadec a,hexadec b);
// check for a <= b
int isLesserOrEqual(hexadec a,hexadec b);
// check for a == b
int isEqual(hexadec a,hexadec b);
// subtract 2 hexadecimal numbers
hexadec subHexadec(hexadec a,hexadec b);
// multiply 2 hexadecimal numbers
hexadec multHexadec(hexadec a,hexadec b);
// compute a^n
hexadec powHexadec(hexadec a,char pow);
// right shift
hexadec rightShiftHexadec(hexadec a,char loc);
// left shift
hexadec leftShiftHexadec(hexadec a,char loc);
// base ten to hexadecimal
hexadec ten2hex(int num);

