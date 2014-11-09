
#include <stdio.h>



// integer square root
int sqrtInt(int in)
{
	int out;

	in = (in + 1) >> 1;
	for(out=0;in>out;in-=out++);
	return out;
}


// whether a number is perfect square or not
int isPerfectSquare(int in)
{
	int i;

	i = sqrtInt(in);
	if(in == (i * i))
		return 1;
	return 0;
}


// whether all these are perfect squares or not
int conditionCheck(int x,int y,int z)
{
	if(isPerfectSquare(x+y) && isPerfectSquare(x-y) && isPerfectSquare(y+z) && isPerfectSquare(y-z)
		&& isPerfectSquare(x+z) && isPerfectSquare(x-z))
		return 1;
	return 0;
}


// main function
int giveTheNumbers(int limit)
{
	int x,y,z;

	for(z=1;z<=limit;z++)
		for(y=z+1;y<=limit;y++)
			for(x=y+1;x<=limit;x++)
				if(conditionCheck(x,y,z))
					return (x+y+z);
	return 0;
}


// main
int main(int argc,char *argv[])
{
	int limit;

	while(1)
	{
		printf("LIMIT (Press '0' to exit) -> ");
		scanf("%d",&limit);
		if(limit <= 0)
			break;
		printf("%d\n",giveTheNumbers(limit));
	}
	return 0;
}