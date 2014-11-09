#include <stdio.h>
#define MAX 50


// roman numeral to decimal number
int rom2dec(char r)
{
	switch(r)
	{
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	default:
		return 0;
	}
}


// roman to decimal
int decode(char *in,int *len)
{
	int sum,prev,pres,i;

	for(i=0,sum=0,prev=0;*(in + i);i++)
	{
		pres = rom2dec(*(in + i));
		if(prev < pres)
			sum -= (prev << 1);
		sum += pres;
		prev = pres;
	}
	*len = i;
	return sum;
}


// decimal to roman
void encode(char *out,int *len,int num)
{
	int i,val;

	// thousandth place
	val = num / 1000;	num -= (val * 1000);
	for(i=0;i<val;i++)
		*(out + i) = 'M';
	// hundredth place
	val = num / 100;	num -= (val * 100);
	switch(val)
	{
	case 0:
		break;
	case 3:
		*(out + i) = 'C';	i++;
	case 2:
		*(out + i) = 'C';	i++;
	case 1:
		*(out + i) = 'C';	i++;
		break;
	case 4:
		*(out + i) = 'C';	i++;	*(out + i) = 'D';		i++;
		break;
	case 5:
		*(out + i) = 'D';	i++;
		break;
	case 6:
		*(out + i) = 'D';	i++;	*(out + i) = 'C';		i++;
		break;
	case 7:
		*(out + i) = 'D';	i++;	*(out + i) = 'C';		i++;
		*(out + i) = 'C';		i++;
		break;
	case 8:
		*(out + i) = 'D';	i++;	*(out + i) = 'C';		i++;
		*(out + i) = 'C';		i++;	*(out + i) = 'C';		i++;
		break;
	case 9:
		*(out + i) = 'C';	i++;	*(out + i) = 'M';	i++;
		break;
	}
	// tenth place
	val = num / 10;		num -= (val * 10);
	switch(val)
	{
	case 0:
		break;
	case 3:
		*(out + i) = 'X';	i++;
	case 2:
		*(out + i) = 'X';	i++;
	case 1:
		*(out + i) = 'X';	i++;
		break;
	case 4:
		*(out + i) = 'X';	i++;	*(out + i) = 'L';		i++;
		break;
	case 5:
		*(out + i) = 'L';	i++;
		break;
	case 6:
		*(out + i) = 'L';	i++;	*(out + i) = 'X';		i++;
		break;
	case 7:
		*(out + i) = 'L';	i++;	*(out + i) = 'X';		i++;
		*(out + i) = 'X';		i++;
		break;
	case 8:
		*(out + i) = 'L';	i++;	*(out + i) = 'X';		i++;
		*(out + i) = 'X';		i++;	*(out + i) = 'X';		i++;
		break;
	case 9:
		*(out + i) = 'X';	i++;	*(out + i) = 'C';	i++;
		break;
	}
	// unit's place
	val = num;
	switch(val)
	{
	case 0:
		break;
	case 3:
		*(out + i) = 'I';	i++;
	case 2:
		*(out + i) = 'I';	i++;
	case 1:
		*(out + i) = 'I';	i++;
		break;
	case 4:
		*(out + i) = 'I';	i++;	*(out + i) = 'V';		i++;
		break;
	case 5:
		*(out + i) = 'V';	i++;
		break;
	case 6:
		*(out + i) = 'V';	i++;	*(out + i) = 'I';		i++;
		break;
	case 7:
		*(out + i) = 'V';	i++;	*(out + i) = 'I';		i++;
		*(out + i) = 'I';		i++;
		break;
	case 8:
		*(out + i) = 'V';	i++;	*(out + i) = 'I';		i++;
		*(out + i) = 'I';		i++;	*(out + i) = 'I';		i++;
		break;
	case 9:
		*(out + i) = 'I';	i++;	*(out + i) = 'X';	i++;
		break;
	}
	*(out + i) = 0;
	*len = i;
	return;
}


main()
{
	char rom[MAX],out[MAX];
	FILE *fp;
	int num,len1,len2,sum=0;

	fp = fopen("roman_for_p89.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%s",rom);
		num = decode(rom,&len1);
		encode(out,&len2,num);
		if(len2 < len1)
			sum += (len1 - len2);
	}
	fclose(fp);
	printf("%d\n",sum);
}