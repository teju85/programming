// PROBLEM 82:
//     Travelling in a square with minimal path.
// USAGE:
//     exe/pe82.pes
//


// libraries
#include "all.h"

// size of the cost matrix
#define SIZE_MAT 5
// maximum possible value in the matrix
#define MAX_MAT 300000



// main function for problem 82
int main(int argc,char *argv[])
{

	// actual solution
	// usage: exe/pe82.pes
	int i,j,minSum,col,row,up,down,right,min,prev;
	int mat[SIZE_MAT][SIZE_MAT],path[SIZE_MAT];
	FILE *fp;
	// get the cost matrix
	fp = fopen("data/pe82.txt","r");
	if(fp == NULL)
	{
		fprintf(stdout,"A data file by the name 'data/pe82.txt' is required by this program\n");
		exit(1);
	}
	for(i=0;i<SIZE_MAT;i++)
		for(j=0;j<SIZE_MAT;j++)
			if(!j)
				fscanf(fp,"%d",&mat[i][j]);
			else
				fscanf(fp,",%d",&mat[i][j]);
	fclose(fp);
	// initialization
	for(i=0;i<SIZE_MAT;i++)
		path[i] = mat[i][0];
	// dynamic programming on each of the starting points
	for(i=0;i<SIZE_MAT;i++)
	{
		row = i;
		col = 0;
		prev = -1;
		while(col != end)
		{
			// previous was upper
			if(prev == 0)
			{
				up = ((row - 1) < 0)? MAX_MAT : mat[row-1][col];
				down = MAX_MAT;
			}
			// previous was down
			else if(prev == 1)
			{
				up = MAX_MAT;
				down = ((row + 1) >= SIZE_MAT)? MAX_MAT : mat[row+1][col];
			}
			else
			{
				up = ((row - 1) < 0)? MAX_MAT : mat[row-1][col];
				down = ((row + 1) >= SIZE_MAT)? MAX_MAT : mat[row+1][col];
			}
			// right
			if((col + 1) == SIZE_MAT)
			{
				path[i] += mat[row][col+1];
				break;
			}
			else
				right = mat[row][col+1];
			// find the minimum among them
			min = up;
			min = (min > down)? down : min;
			min = (min > right)? right : min;
			// next step
			if(min == up)
			{
				row--;
				prev = 0;
			}
			else if(min == down)
			{
				row++;
				prev = 1;
			}
			else
			{
				col++;
				prev = 2;
			}
			// add the path
			path[i] += min;
		}
	}
	// find the minimal case
	for(i=1,minSum=path[0];i<SIZE_MAT;i++)
		if(minSum > path[i])
			minSum = path[i];
	fprintf(stdout,"Minimal path sum is %d\n",minSum);

	return 0;
}

