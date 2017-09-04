//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "intal.h"

int main(void) {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal* i3 = create_intal();
	intal* i4 = create_intal();

	read_intal(i1, "123456789");
	read_intal(i2, "+12");
	read_intal(i3, "-123");
	read_intal(i4, "0");

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");

	intal *c,*d,*e,*f,*g;
	c=add_intal(i1,i2);
	print_intal(c);
	printf("--> This is i1+i2\n");
	d=subtract_intal(i1,i2);
	print_intal(d);
	printf("--> This is i1-i2\n");
	e=multiply_intal(i1,i2);
	print_intal(e);
	printf("--> This is i1*i2\n");
	f=pow_intal(i1,i2);
	print_intal(f);
	printf("--> This is i1^i2\n");
	g=divide_intal(i1,i2);
	print_intal(g);
	printf("--> This is i1/i2\n");
	
	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");

	delete_intal(&i1);
	delete_intal(&i2);
	delete_intal(&i3);
	delete_intal(&i4);

	return 0;
}