#include <stdio.h>

// a + b + c = p
// a^2 + b^2 = c^2
// which means that
// 2 * (c^2 + ab + bc + ca) = p^2     =>    'p' must be EVEN

main()
{
	int a,b,c,p,limit,max=0,num,final=1;

	printf("Enter the limit: ");
	scanf("%d",&limit);
	for(p=2;p<limit;p+=2)
	{
		num = 0;
		for(a=1;a<p;a++)
		{
			for(b=1;b<p;b++)
			{
				c = p - a - b;
				if((c * c) == (a * a) + (b * b))
					num++;
			}
		}
		if(max < num)
		{
			max = num;
			final = p;
		}
	}
	printf("for p = %d number of solns. = %d\n",final,max);
}
