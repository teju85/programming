// PROBLEM 1111:
//     Number of truth tables for 6-bit inputs with a special property.
// USAGE:
//     exe/pe1111.pes
//


// libraries
#include "all.h"

// total number of possible input combinations
#define TOT_IP 64
// total number of input bits
#define IP_BITS 6



// main function for problem 82
int main(int argc,char *argv[])
{
  // actual solution
  // usage: exe/pe1111.pes
  unsigned char num[TOT_IP],num1[TOT_IP],limit;
  unsigned char uPairs[TOT_IP],graph[TOT_IP][TOT_IP];
  int i,j,k,unique,repeat,unused;

  // 'num'  for (a,b,c,d,e,f)
  // 'num1' for (b,c,d,e,f,a XOR (b AND c))
  //
  // 'uPairs' tells which are the pairs which are uniquely mapped wrt each other
  // Since we know that 'num' contains all unique numbers, this job becomes
  // essentially searching for uniques in 'num1'.
  // uPairs[i] = i         => this is a unique pair or in this list of 'repeated'
  //                          pairs, this is the last
  // uPairs[i] = j         => same value of 'num1[i]' can be found at 'num1[j]'

  // initialization
  limit = (1 << (IP_BITS - 2)) + (1 << (IP_BITS - 3));
  unique = repeat = unused = 0;
  for(i=0;i<TOT_IP;i++)
    for(j=0;j<TOT_IP;j++)
      graph[i][j] = 0;
  // generate the mapping between 'num' and 'num1'
  for(i=0;i<limit;i++)
    {
      num[i] = i;
      num1[i] = (num[i] << 1) & 63;
    }
  for(;i<TOT_IP;i++)
    {
      num[i] = i;
      num1[i] = (num[i] << 1) & 63;
      num1[i] |= 1;
    }
  // search for the uniques
  for(i=0;i<TOT_IP;i++)
    {
      uPairs[i] = i;
      for(j=i+1;j<TOT_IP;j++)
	{
	  if(num1[j] == num1[i])
	    {
	      uPairs[i] = j;
	      break;
	    }
	}
    }
  // get the graph
  for(i=0;i<TOT_IP;i++)
    graph[num[i]][num1[i]] = 1;
  // get the total number of numbers unused in 'num1'
  for(i=0;i<TOT_IP;i++)
    {
      for(j=0;j<TOT_IP;j++)
	{
	  if(num1[j] == i)
	    break;
	}
      if(j == TOT_IP)
	unused++;
    }
  // print the repetitions
  for(i=0;i<TOT_IP;i++)
    {
      if(uPairs[i] == i)
	{
	  fprintf(stdout,"Single: %2u %2u\n",num[i],num1[i]);
	  unique++;
	}
      else if(uPairs[i] == TOT_IP)
	continue;
      else
	{
	  j = i;
	  fprintf(stdout,"Repeats: %2u %2u\n",num[j],num1[j]);
	  repeat++;
	  while(uPairs[j] != j)
	    {
	      k = uPairs[j];
	      uPairs[j] = TOT_IP;
	      j = k;
	      fprintf(stdout,"         %2u %2u\n",num[j],num1[j]);
	      repeat++;
	    }
	  uPairs[j] = TOT_IP;
	}
    }
  // print the statistics
  fprintf(stdout,"Total number of unique pairs   : %2d\n",unique);
  fprintf(stdout,"Total number of repeated pairs : %2d\n",repeat);
  fprintf(stdout,"Total number of pairs          : %2d\n",TOT_IP);
  fprintf(stdout,"Total number of numbers unused : %2d\n",unused);
  return 0;
}
