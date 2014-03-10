// Paradygmat_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>

int a,b,c;
float d,x1r,x2r,x1u,x2u;

int _tmain(int argc, _TCHAR* argv[])
{

	

	a=0; b=0, c=0;

	//----------------------------------------------------------------------

	if(a == 0) printf(" "); else{
		if(a == 1) printf(" xx"); else{
			if(a == -1) printf(" -xx"); else{
				printf("%d xx",a);
			}
		}
	}

	if(b == 0) printf(" "); else{
		if(b == 1) printf("+x"); else{
			if(b == -1) printf("-x"); else{
				if(b > 0) printf("+%dx",b); else printf("-%dx",b);
			}
		}
	}

	if(c == 0) printf(" "); else{
			if(c > 0) printf("+%d",c); else printf("%d",c);
	}

	printf("=0");

	//------------------------------------------------------------------------------------

	if(a != 0) {
		d=b*b-4*a*c;
		printf("\n d=%f\n",d);
	

	if(d > 0){
		x1r=(-(float)b-sqrt(d))/(2*a);
		x2r=(-(float)b+sqrt(d))/(2*a);
		printf("x1r=%f, x2r=%f\n",x1r,x2r);
	}else if(d == 0){
		x1r=-(float)b/(2*a);
		printf("x1r=%f\n",x1r);
	}else{
		x1r=-(float)b/(2*a);
		x2r=x1r;
		x1u=-sqrt(-d)/(2*a);
		x2u=-x1u;

		//---------------------------

		if(x1r == 0) printf(" "); else printf("%f",x1r);
		if(x1u == 0) printf(" \n"); else if(x1u < 0) printf("%f*i\n",x1u); else printf("+%f*i\n",x1u);

		if(x2r == 0) printf(" "); else printf("%f",x2r);
		if(x2u == 0) printf(" \n"); else if(x2u < 0) printf("%f*i\n",x2u); else printf("+%f*i\n",x2u);

		//-------------------------
	}

		if(a == 0){
			if(b != 0){
				x1r=-c/b;
				printf("x1r=%f",x1r);
			} else if(b == 0 && c !=0){
				printf("R-nie sprzeczne");
			}else if(b == 0 && c == 0){
				printf("R-nie nieoznaczone");
			}
		}

	};



	getchar();
	return 0;
}
