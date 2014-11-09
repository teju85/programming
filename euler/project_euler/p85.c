#include <stdio.h>
#define MAX 100

// number of rectangles = mn(m+1)(n+1)/4

main()
{
	int limit,m,n,i,j,area;
	float err,min,f1,f2;

	printf("Enter the area: ");
	scanf("%d",&limit);
	min = limit;
	for(i=1;i<MAX;i++)
	{
		f1 = i;
		for(j=1;j<MAX;j++)
		{
			f2 = j;
			err = limit - (f1*f2*(f1+1)*(f2+1)/4);
			if(err < 0)
				err = -err;
			if(err < min)
			{
				min = err;
				m = i;
				n = j;
			}
		}
	}
	area = m * n;
	min = (m * n * (m + 1) * (n + 1)) / 4;
	printf("(m,n) = (%d,%d) .... area = %d .... no. of rectangles = %f\n",m,n,area,min);
}