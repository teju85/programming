// PROBLEM 162:
//     Hexadecimal numbers.
// USAGE:
//     exe/pe162.pes
//


// libraries
#include "all.h"



// main function for problem 162
int main(int argc,char *argv[])
{
/*
	// To check the functionalities of 'initHexadec', 'str2hex', 'showHexadec' and getHexadec'
	// usage: exe/pe69.pes <hex>
	// <hex> is a hexadecimal number
	hexadec a;
	showHexadec(initHexadec());
	a = str2hex(argv[1]);
	showHexadec(a);
	a = getHexadec();
	showHexadec(a);
*/

/*
	// To check the functionalities of 'isGreater', 'isGreaterOrEqual', 'isLesser', 'isLesserOrEqual' and 'isEqual'
	// usage: exe/pe69.pes <hex1> <hex2>
	// <hex1> and <hex2> are hexadecimal numbers
	hexadec a,b;
	a = str2hex(argv[1]);
	b = str2hex(argv[2]);
	printf("%d\n",isGreater(a,b));
	printf("%d\n",isGreaterOrEqual(a,b));
	printf("%d\n",isLesser(a,b));
	printf("%d\n",isLesserOrEqual(a,b));
	printf("%d\n",isEqual(a,b));
*/

/*
	// To check the functionalities of 'addHexadec', 'subHexadec', 'multHexadec', 'powHexadec', 'rightShiftHexadec',
	// 'leftShiftHexadec' and 'ten2hex'
	// usage: exe/pe69.pes <hex1> <hex2> <num>
	// <hex1> and <hex2> are hexadecimal numbers
	// <num> is a positive integer
	hexadec a,b;
	a = str2hex(argv[1]);
	b = str2hex(argv[2]);
	showHexadec(addHexadec(a,b));
	showHexadec(subHexadec(a,b));
	showHexadec(multHexadec(a,b));
	showHexadec(powHexadec(a,3));
	showHexadec(rightShiftHexadec(a,3));
	showHexadec(leftShiftHexadec(a,3));
	showHexadec(ten2hex(str2int(argv[3])));
*/

/*
	// actual solution (algo1, it was logically incorrect)
	// usage: exe/pe162.pes
	hexadec out,dd;
	int i;
	// initialization
	out = initHexadec();
	for(i=3;i<=16;i++)
	{
		dd = leftShiftHexadec(ten2hex((i-1)*(i-1)*(i-2)),(i-3));
		showHexadec(dd);
		out = addHexadec(out,dd);
	}
	// result
	showHexadec(out);
*/


	// actual solution (algo2)
	// usage: exe/pe162.pes
	hexadec out,dd1,dd2,dd3,d13;
	int n,i,tt;
	// initialization
	out = initHexadec();
	d13 = ten2hex(13);
	for(n=3;n<=16;n++)
	{
		out = addHexadec(out,leftShiftHexadec(ten2hex(2*(n-1)*(n-2)),(n-3)));
		for(i=n-2;i>=2;i--)
		{
			dd3 = multHexadec(ten2hex(3*(n-i)*(n-i-1)),powHexadec(d13,(i-1)));
			out = addHexadec(out,dd3);
		}
	}
	// result
	showHexadec(out);


	return 0;
}

