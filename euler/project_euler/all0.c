
#include "all.h"



// sum of consecutive integers
unsigned int sumInt(int n)
{
	unsigned int out;

	out = (n * (n + 1)) >> 1;
	return out;
}


// sum of squares of consecutive integers
unsigned int sumIntSquares(int n)
{
	unsigned int out;

	out = (n * (n + 1) * ((n << 1) + 1)) / 6;
	return out;
}


// floor function in division
int floorDivision(int n,int m)
{
	return (n / m);
}


// ceiling function in division
int ceilDivision(int n,int m)
{
	int out;

	out = n / m;
	if(n % m)
		out++;
	return out;
}


// finds the integer square root of a number
int sqrtInt(unsigned int i)
{
	int r;

	i = (i+1)>>1;
	for(r=0;i>r;i-=r++);
	return r;
}


// detects whether a number is prime or not
int isPrime(int i)
{
	int sqi,j;

	sqi = sqrtInt((unsigned int)i);
	for(j=2;j<=sqi;j++) 
		if((i % j) == 0) 
			return 0;
	return 1;
}


// finds the sum of the digits of the input integer
int digitSum(int n)
{
	int sum=0;

	for(;n;n/=10)
		sum += (n % 10);
	return sum;
}


// finds the sum of squares of the digits of the input integer
int digitSquareSum(int n)
{
	int i;
	int sum=0;

	for(;n;n/=10)
	{
		i = n % 10;
		sum += (i * i);
	}
	return sum;
}


// sum of factorial of the digits of the input integer
int digitFactorialSum(int num)
{
	int i,sum;
	int aTemp[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

	for(i=0,sum=0;num;i++,num/=10)
		sum += aTemp[(num % 10)];
	return sum;
}


// finds the number of divisors of the input integer
//!!!!!!!!!!!!!!!!!!!!!!! haven't checked yet!!!!!!!!!!!!!!!!!!!!!!!!!!!
int numDivisors(int i)
{
	int no,j,k;

	for(j=2,no=2,k=i>>1;j<=k;j++)
	{
		if((i % j) == 0)
		{
			no += 2;
			k = i / j;
			if(j == k)
				no -= 1;
		}
	}
	return no;
}


// finds the gcd of 2 numbers
int gcd(int a, int b)
{
	int g;

	while(g!=0)
	{
		g = b % a;
		b = a;
		a = g;
	}
	return b;
}


// checks whether the input integer is palindrome or not
int ispalin(int a)
{
	int i,j,first,last;

	j = 10;
	for(i=1;(a/j!=0);i++,j*=10);
	j /= 10;
	for(;i>0;i-=2,j/=100)
	{
		first = a / j;
		last = a % 10;
		if(first != last)
			return 0;
		a = (a - (first * j)) / 10;
	}
	return 1;
}


// convert the string to integer
int str2int(char *str)
{
	int out,i,m,n;

	i = strlen(str) - 1;
	for(out=0,m=1;i>0;i--,m*=10)
    {
		n = (int) (str[i] - '0');
		if((n < 0) || (n > 9))
		{
			fprintf(stdout,"String: %s\n",str);
			fprintf(stdout,"The input string is not a valid integer.\n");
			exit(1);
		}
		out += (n * m);
    }
	// check for the negative sign
	if(str[i] == '-')
		out = -out;
	else
    {
		n = (int) (str[i] - '0');
		if((n < 0) || (n > 9))
		{
			fprintf(stdout,"String: %s\n",str);
			fprintf(stdout,"The input string is not a valid integer.\n");
			exit(1);
		}
		out += (n * m);
    }
	return out;
}


// generates the prime numbers into the array 'primes'
void generatePrimeNumbers()
{
	int i,j;

	// first prime
	primes[0] = 2;
	// remaining primes
	for(i=3,j=1;i<=LIMIT_PRIME;i+=2)
	{
		if(isPrime(i))
		{
			primes[j] = i;
			j++;
		}
	}
	// total number of primes detected
	numPrimes = j;
	return;
}


// show the primes from the 'start'th prime number till 'end'th
void showPrimeNumbers(int start,int end)
{
	int i;

	fprintf(stdout,"Number of primes: %d\n",numPrimes);
	for(i=start;i<=end;i++)
		fprintf(stdout,"%d. %d\n",i,primes[i]);
	return;
}


// decomposition of a number into its prime divisors
// You should call the function 'generatePrimeNumbers' in order to populate the prime number array, apriori.
// It returns the prime divisors along with their appropriate exponents in the array 'priDiv'.
// The number of prime divisors will be with 'numPriDiv'.
void generatePrimeDivisors(int n)
{
	int i,j,num,k,val;

	// initialization
	i = j = 0;
	val = n;
	// find the prime divisors
	while(n != 1)
	{
		if(!(n % primes[i]))
		{
			priDiv[j][0] = k = primes[i];
			n /= k;
			num = 1;
			while(!(n % k))
			{
				num++;
				n /= k;
			}
			priDiv[j][1] = num;
			j++;
		}
		i++;
	}
	// number of prime divisors
	numPriDiv = j;
	priDiv[j][0] = priDiv[j][1] = val;
	return;
}


// show the prime divisors
// should call 'generatePrimeDivisors' apriori
void showPrimeDivisors()
{
	int i;

	fprintf(stdout,"Prime Divisors of '%d' are:\n",priDiv[numPriDiv][0]);
	if(!numPriDiv)
	{
		fprintf(stdout," -None-\n");
		return;
	}
	fprintf(stdout,"%d^%d",priDiv[0][0],priDiv[0][1]);
	for(i=1;i<numPriDiv;i++)
		fprintf(stdout," * %d^%d",priDiv[i][0],priDiv[i][1]);
	fprintf(stdout,"\n");
	return;
}


// evaluate the euler totient function
// You should call the function 'generatePrimeNumbers' in order to populate the prime number array, apriori.
int eulerTotient(int n)
{
	int phi,i,j;

	// get the prime divisors
	generatePrimeDivisors(n);
	// evaluate the euler totient
	for(i=0,phi=1;i<numPriDiv;i++)
	{
		for(j=1;j<priDiv[i][1];j++)
			phi *= priDiv[i][0];
		phi *= (priDiv[i][0] - 1);
	}
	return phi;
}


// evaluate the ratio n/phi(n)
// You should call the function 'generatePrimeNumbers' in order to populate the prime number array, apriori.
double eulerRatio(int n)
{
	double ratio;
	int i;

	// get the prime divisors
	generatePrimeDivisors(n);
	// evaluate the euler ratio
	for(i=0,ratio=1;i<numPriDiv;i++)
		ratio *= ((double) priDiv[i][0]) / (priDiv[i][0] - 1);
	return ratio;
}


// checks if it is a bouncy number or not
// returns '1' if it is, else returns '0'
int bouncyNumber(unsigned long int num)
{
	char digits[MAX_DIGITS];
	int i,len,dec,inc;

	// find the digits
	len = num;
	for(i=0;len;len/=10,i++)
		digits[i] = len % 10;
	len = i;
	// decreasing number
	for(i=1,dec=1;i<len;i++)
	{
		if(digits[i] < digits[i-1])
		{
			dec = 0;
			break;
		}
	}
	// increasing number
	for(i=len-2,inc=1;i>=0;i--)
	{
		if(digits[i] < digits[i+1])
		{
			inc = 0;
			break;
		}
	}
	if(!dec && !inc)
		return 1;
	return 0;
}


// initialize a hexadecimal number
hexadec initHexadec()
{
	int i;
	hexadec out;

	for(i=0;i<MAX_HEX_DIGITS;i++)
		out.dig[i] = 0;
	out.len = 0;
	out.sign = 0;
	return out;
}


// convert the string to hexadecimal number
hexadec str2hex(char *str)
{
	hexadec out;
	int i,len,j,s,e;

	// initialization
	out = initHexadec();
	// negative number
	if(str[0] == '-')
	{
		out.sign = 1;
		len = strlen(str);
		out.len = len - 1;
		s = out.len;
		e = 1;
	}
	else
	{
		out.sign = 0;
		out.len = len = strlen(str);
		s = len - 1;
		e = 0;
	}
	for(i=s,j=0;i>=e;i--,j++)
	{
		switch(str[i])
		{
		case '0':
			out.dig[j] = 0;
			break;
		case '1':
			out.dig[j] = 1;
			break;
		case '2':
			out.dig[j] = 2;
			break;
		case '3':
			out.dig[j] = 3;
			break;
		case '4':
			out.dig[j] = 4;
			break;
		case '5':
			out.dig[j] = 5;
			break;
		case '6':
			out.dig[j] = 6;
			break;
		case '7':
			out.dig[j] = 7;
			break;
		case '8':
			out.dig[j] = 8;
			break;
		case '9':
			out.dig[j] = 9;
			break;
		case 'A':
			out.dig[j] = 10;
			break;
		case 'B':
			out.dig[j] = 11;
			break;
		case 'C':
			out.dig[j] = 12;
			break;
		case 'D':
			out.dig[j] = 13;
			break;
		case 'E':
			out.dig[j] = 14;
			break;
		case 'F':
			out.dig[j] = 15;
			break;
		default:
			fprintf(stdout,"Unknown format for hexadecimal numbers\n");
			exit(-1);
		}
	}
	return out;
}


// get a hexadecimal number from the user
hexadec getHexadec()
{
	char str[MAX_STRLEN];
	hexadec out;

	fprintf(stdout,"Give the hexadecimal number: ");
	fscanf(stdin,"%s",str);
	out = str2hex(str);
	return out;
}


// display hexadecimal number
void showHexadec(hexadec in)
{
	int i;

	if(in.sign)
		fprintf(stdout,"Hexadecimal number: -");
	else
		fprintf(stdout,"Hexadecimal number: ");
	if(in.len <= 0)
	{
		fprintf(stdout,"0\n");
		return;
	}
	for(i=in.len-1;i>=0;i--)
	{
		if(in.dig[i] == 10)
			fprintf(stdout,"A");
		else if(in.dig[i] == 11)
			fprintf(stdout,"B");
		else if(in.dig[i] == 12)
			fprintf(stdout,"C");
		else if(in.dig[i] == 13)
			fprintf(stdout,"D");
		else if(in.dig[i] == 14)
			fprintf(stdout,"E");
		else if(in.dig[i] == 15)
			fprintf(stdout,"F");
		else
			fprintf(stdout,"%d",in.dig[i]);
	}
	fprintf(stdout,"\n");
	return;
}


// add 2 hexadecimal numbers
hexadec addHexadec(hexadec a,hexadec b)
{
	hexadec out;
	int i,len;
	char carry,dd;

	len = (a.len < b.len)? b.len : a.len;
	// same polarity
	if(a.sign == b.sign)
	{
		// initialization
		out = initHexadec();
		// addition
		for(i=0,carry=0;i<len;i++)
		{
			dd = a.dig[i] + b.dig[i] + carry;
			out.dig[i] = dd & 0x0f;
			carry = (dd & 0xf0)? 1 : 0;
		}
		// length and sign of the resulting number
		out.len = len + carry;
		out.dig[i] = carry;
		out.sign = a.sign;
	}
	// different polarity
	else if(a.sign && !b.sign)
	{
		a.sign = 0;
		out = subHexadec(b,a);
	}
	else
	{
		b.sign = 0;
		out = subHexadec(a,b);
	}
	return out;
}


// check for a > b
int isGreater(hexadec a,hexadec b)
{
	int i,flag;

	if(a.len > b.len)
		return !a.sign;
	else if(a.len < b.len)
		return b.sign;
	else
	{
		for(i=a.len-1,flag=-1;i>=0;i--)
		{
			if(a.dig[i] < b.dig[i])
			{
				flag = 0;
				break;
			}
			else if(a.dig[i] > b.dig[i])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)
			return !a.sign;
		else if(flag == 0)
			return b.sign;
		else
			return 0;
	}
}


// check for a < b
int isLesser(hexadec a,hexadec b)
{
	int i,flag;

	if(a.len > b.len)
		return a.sign;
	else if(a.len < b.len)
		return !b.sign;
	else
	{
		for(i=a.len-1,flag=-1;i>=0;i--)
		{
			if(a.dig[i] < b.dig[i])
			{
				flag = 1;
				break;
			}
			else if(a.dig[i] > b.dig[i])
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
			return !b.sign;
		else if(flag == 0)
			return a.sign;
		else
			return 0;
	}
}


// check for a >= b
int isGreaterOrEqual(hexadec a,hexadec b)
{
	return !isLesser(a,b);
}


// check for a <= b
int isLesserOrEqual(hexadec a,hexadec b)
{
	return !isGreater(a,b);
}


// check for a == b
int isEqual(hexadec a,hexadec b)
{
	int i;

	if((a.sign == b.sign) && (a.len == b.len))
	{
		for(i=a.len-1;i>=0;i--)
			if(a.dig[i] != b.dig[i])
				return 0;
		return 1;
	}
	return 0;
}


// subtract 2 hexadecimal numbers
hexadec subHexadec(hexadec a,hexadec b)
{
	hexadec out;
	int i,len;
	char carry,dd;

	// if a >= b
	if(isGreaterOrEqual(a,b))
	{
		len = a.len;
		// both positive
		if(!a.sign && !b.sign)
		{
			// initialization
			out = initHexadec();
			// subtraction
			for(i=0,carry=0;i<len;i++)
			{
				dd = a.dig[i] - b.dig[i] + carry;
				if(dd < 0)
				{
					dd += 16;
					carry = -1;
				}
				else
					carry = 0;
				out.dig[i] = dd;
			}
			// sign of the resulting number
			out.sign = a.sign;
			// length of the resulting number
			for(i=MAX_HEX_DIGITS-1;i>=0;i--)
				if(out.dig[i] > 0)
					break;
			out.len = i + 1;
		}
		// both negative
		else if(a.sign && b.sign)
		{
			b.sign = 0;
			a.sign = 0;
			out = subHexadec(b,a);
		}
		// different polarity
		else
		{
			b.sign = 0;
			out = addHexadec(a,b);
		}
	}
	// a < b
	else
	{
		out = subHexadec(b,a);
		out.sign = !out.sign;
	}
	// check for -0
	if(out.sign && (out.len <= 1) && (out.dig[0] == 0))
		out.sign = 0;
	return out;
}


// multiply 2 hexadecimal numbers
hexadec multHexadec(hexadec a,hexadec b)
{
	hexadec out;
	int i,lenA,lenB;

	// scalar multiplication
	void scalarMult(char num)
	{
		int j,ij;
		unsigned char dd,dd1,carry;

		for(j=0,carry=0,ij=i;j<lenA;j++,ij++)
		{
			dd = (a.dig[j] * b.dig[i]) + carry;
			carry = (dd & 0xf0) >> 4;
			dd1 = out.dig[ij] + (dd & 0x0f);
			out.dig[ij] = (dd1 & 0x0f);
			carry += ((dd1 & 0xf0) >> 4);
		}
		if(carry)
		{
			out.len = ij + 1;
			out.dig[ij] = carry;
		}
		else
			out.len = ij;
		return;
	}

	// initialization
	out = initHexadec();
	lenA = a.len;
	lenB = b.len;
	// main loop
	for(i=0;i<lenB;i++)
		scalarMult(b.dig[i]);
	// sign
	out.sign = (a.sign == b.sign)? 0 : 1;
	return out;
}


// compute a^n
hexadec powHexadec(hexadec a,char pow)
{
	hexadec out;
	char i;

	// initialization
	out.sign = 0;
	out.len = 1;
	out.dig[0] = 1;
	// main loop
	for(i=1;i<=pow;i++)
		out = multHexadec(out,a);
	return out;
}


// right shift
hexadec rightShiftHexadec(hexadec a,char loc)
{
	hexadec out;
	int i;

	// initialization
	out = initHexadec();
	// shift
	for(i=loc;i<a.len;i++)
		out.dig[i-loc] = a.dig[i];
	// length and sign
	out.len = a.len - loc;
	out.sign = a.sign;
	return out;
}


// left shift
hexadec leftShiftHexadec(hexadec a,char loc)
{
	hexadec out;
	int i;

	// initialization
	out = initHexadec();
	// shift
	for(i=0;i<a.len;i++)
		out.dig[i+loc] = a.dig[i];
	// length and sign
	out.len = a.len + loc;
	out.sign = a.sign;
	return out;
}


// base ten to hexadecimal
hexadec ten2hex(int num)
{
	hexadec out;
	int j;

	// initialization
	out = initHexadec();
	// sign
	if(num < 0)
	{
		out.sign = 1;
		num = -num;
	}
	else
		out.sign = 0;
	// conversion
	for(j=0;num;j++,num>>=4)
		out.dig[j] = (num & 0xf);
	// length
	out.len = j;
	return out;
}

