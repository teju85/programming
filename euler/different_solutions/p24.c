#include <stdio.h>
#define max 20

int status[max];

int nth_element(int p, int i)
{
  int j,k=-1;
  for(j=0;j<=i+p+1;j++)
  {
      if(status[j] == 0)
		  k++;
      if( k == p)
	  {
		  status[j] = 1;
		  return j;
	  }
  }
  return j;
}

int fact(int i)
{
  if(i == 0) 
	  return 1;
  else
	  return i*fact(i-1);
}

main()
{
	int n,pos,i,del,c,dup;

  scanf("%d %d",&n,&pos);
  for(i=n;i>=1;i--)
  {
      c = fact(i);
      del = (pos - 1)/c;
      pos -= del*c;
      printf("%d",nth_element(del,n-i));
  }
  printf("%d\n",nth_element(0,n-i));
}