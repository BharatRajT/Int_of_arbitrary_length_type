//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

// intal is an integer of arbitrary length. It has two fields; s and n.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = malloc(n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		n++; //one extra for the + sign
	 	i->s = malloc(n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	i->s[n]='\0';
	i->n=n-1;
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

int compare(intal *a,intal *b) {
	if(a->n<b->n) return -1;
	else if(a->n==b->n) {
		if(strcmp(a->s+1,b->s+1)<0) return -1;
		else if(strcmp(a->s+1,b->s+1)==0) return 0;
		else return 1; }
	else return 1; }

void pad(intal* bi,int newNod) {
    	char *newData=malloc(newNod*sizeof(char)+1);
	newData[0]=bi->s[0];
    	memset(newData+1,'0',(newNod-bi->n)*sizeof(char));
    	memcpy(newData+(newNod-bi->n)+1,bi->s+1,bi->n*sizeof(char));
    	free(bi->s);
	bi->s=(char *)malloc(newNod+1);
    	memcpy(bi->s,newData,newNod+1);
    	bi->n=newNod; }

void split(intal *a,intal *a1,intal *a2) {
	a1->n=(a->n)/2;
    a2->n=a1->n;
    a1->s=malloc(a1->n*sizeof(char)+2);
    a2->s=malloc(a2->n*sizeof(char)+2);
    memcpy(a1->s+1,a->s+1,a1->n*sizeof(char));
    memcpy(a2->s+1,a->s+a1->n+1,a2->n*sizeof(char));
	delete_intal(&a);
	a1->s[0]=a2->s[0]='+';
	a1->s[a1->n+1]=a2->s[a2->n+1]='\0'; }

void power10(intal *a, int m) {
	int newNod=m+a->n;
	a->s=realloc(a->s,newNod*sizeof(char)+1);
	memset(a->s+a->n+1,'0',m*sizeof(char));
	a->n=newNod; }
	
// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b) {
	intal *sum;
	if(a->s[0]=='-') {
		if(b->s[0]=='+') {
			if(compare(b,a)>=0) {
				sum=subtract(b,a);
				sum->s[0]='+'; }
			else {
				sum=subtract(a,b);
				sum->s[0]='-'; } }
		else {
			sum=add(a,b);
			sum->s[0]='-'; } }
	else {
		if(b->s[0]=='-') {
			if(compare(a,b)>=0) {
				sum=subtract(a,b);
				sum->s[0]='+'; }
			else {
				sum=subtract(b,a);
				sum->s[0]='-'; } }
		else {
			sum=add(a,b);
			sum->s[0]='+'; } }
	return sum; }

intal* add(intal *a, intal *b) {
	intal *sum=malloc(sizeof(intal));
	if((a->n)>(b->n)) sum->n=(a->n)+1;
	else sum->n=(b->n)+1;
	sum->s=malloc(sum->n*(sizeof(char)+1));
	int i=0;
	int carry=0;
	int s=0;
	int ad,bd;
	int adi=0,bdi=0;
	for (i = -1; i >= -sum->n; --i) {
		ad=bd=0;
		if ((adi = a->n+i+1) >= 1) {
			ad=(a->s[adi])-'0'; }
		if ((bdi = b->n+i+1) >= 1) {
			bd=(b->s[bdi])-'0'; }
	s=ad+bd+carry;
	sum->s[sum->n+i+1]=(s%10)+'0';
	carry=s/10; }
	if (sum->s[1] == '0') {
		char* newData=malloc(((sum->n)-1)*sizeof(char)+1);
		memcpy(newData+1,sum->s+2,(--sum->n)*sizeof(char));
		free(sum->s);
		sum->s=newData; }
	return sum; }

intal* subtract(intal *a,intal *b) {
	intal *diff=malloc(sizeof(intal));
	diff->n=(a->n);
	diff->s=malloc(diff->n*sizeof(char)+1);
	memcpy(diff->s,a->s,a->n*sizeof(char)+1);
	int num=0;
	int i=0;
	int d=0;
	int ad,bd;
	int adi=0,bdi=0;
	for(i=-1;i>=-diff->n;--i) {
		bd=0;
		adi=diff->n+i+1;
		ad=(diff->s[adi])-'0';
		bdi=b->n+i+1;
		if((b->n+i+1)>=1) {
			bd=(b->s[bdi])-'0'; }
		d=ad-bd;
		if(d<0) {
			--(diff->s[adi-1]);
			d+=10; }
		diff->s[adi] = d+'0'; }
	if(diff->s[1]=='0') {
		for(i=1;(i<diff->n)&&(diff->s[i]=='0');i++) num++;
		char* newData=malloc(((diff->n)-num)*sizeof(char)+1);
		memcpy(newData+1,diff->s+num+1,(diff->n-num)*sizeof(char));
		//newData[0]=diff->s[0];
		diff->n=diff->n-num;
		free(diff->s);
		diff->s=newData; }
	return diff; }

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal *a, intal *b) {
	intal *diff;
	if(a->s[0]=='-') {
		if(b->s[0]=='-') {
			if(compare(a,b)<=0) {
				diff=subtract(b,a);
				diff->s[0]='+'; }
			else {
				diff=subtract(a,b);
				diff->s[0]='-'; } }
		else {
			diff=add(a,b);
			diff->s[0]='-'; } }
	else {
		if(b->s[0]=='+') {
			if(compare(a,b)>=0) {
				diff=subtract(a,b);
				diff->s[0]='+'; }
			else {
				diff=subtract(b,a);
				diff->s[0]='-'; } }
		else {
			diff=add(a,b);
			diff->s[0]='+'; } }
	return diff; }

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b){
	int i,num=0;
	intal *c=create_intal();
	intal *d=create_intal();
	intal *e=create_intal();
	read_intal(c,a->s);
	read_intal(d,b->s);
	if(compare(a,b)<0) e=karatsuba(d,c);
	else e=karatsuba(c,d);
	if(((a->s[0]=='+')&&(b->s[0]=='+'))||((a->s[0]=='-')&&(b->s[0]=='-'))) e->s[0]='+';
	else e->s[0]='-';
	if(e->s[1]=='0') {
		for(i=1;(i<e->n)&&(e->s[i]=='0');i++) num++;
		char* newData=malloc(((e->n)-num)*sizeof(char)+1);
		newData[0]=e->s[0];
		memcpy(newData+1,e->s+num+1,(e->n-num)*sizeof(char));
		e->n=e->n-num;
		free(e->s);
		e->s=(char *)malloc(e->n+1+1);
		memcpy(e->s,newData,e->n+1);
		e->s[e->n+1]='\0'; }
	return e; }

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b) {
	intal *e=create_intal();
	char as=a->s[0],bs=b->s[0];
	a->s[0]=b->s[0]='+';
	int i,num=0;
	e=divide(a,b);
	a->s[0]=as;
	b->s[0]=bs;
	if(((as=='+')&&(bs=='+'))||((as=='-')&&(bs=='-'))) e->s[0]='+';
	else e->s[0]='-';
	if(e->s[1]=='0') {
		for(i=1;(i<e->n)&&(e->s[i]=='0');i++) num++;
		char* newData=malloc(((e->n)-num)*sizeof(char)+1);
		newData[0]=e->s[0];
		memcpy(newData+1,e->s+num+1,(e->n-num)*sizeof(char));
		e->n=e->n-num;
		free(e->s);
		e->s=(char *)malloc(e->n+1+1);
		memcpy(e->s,newData,e->n+1);
		e->s[e->n+1]='\0'; }
	return e; }

intal* divide(intal* a, intal* b){
	intal *res=malloc(sizeof(intal));
	if((b->n==1)&&(b->s[1]=='0')) return res;
	read_intal(res,"1");
	if(compare(a,b)==0) return res;
	read_intal(res,"0");
	if(compare(a,b)<0) return res;
	intal *one=create_intal();
	read_intal(one,"1");
	intal *temp=create_intal();
	read_intal(temp,a->s);
	while(compare(temp,b)>=0) {
		temp=subtract(temp,b);
		res=add_intal(res,one);
	}
	delete_intal(&one);
	delete_intal(&temp);
	return res;
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {
	intal *res=malloc(sizeof(intal));
	if(b->s[0]=='-') return res;
	read_intal(res,"1");
	if((b->n==1)&&(b->s[1]=='0')) return res;
	intal *temp=create_intal();
	read_intal(temp,b->s);
	intal *one=create_intal();
	read_intal(one,"1");
	while(!((temp->n==1)&&(temp->s[1]=='0'))) { //!((temp->n==1)&&(temp->s[1]=='0'))
		res=multiply_intal(res,a);
		temp=subtract_intal(temp,one);
	}
	delete_intal(&one);
	delete_intal(&temp);
	if(a->s[0]=='-') if(b->s[b->n]%2!=0) res->s[0]='-';
	return res;
}

intal* karatsuba(intal* a,intal* b) { //len(a)>len(b)
	intal *res=malloc(sizeof(intal));
	if (a->n == 1) {
		int prod=(a->s[1]-'0')*(b->s[1]-'0');
        char* ps=malloc(sizeof(char)*2);
       	sprintf(ps,"%d",prod);
       	read_intal(res,ps);
		res->s[0]='+';
		free(ps);
        return res; }
    intal* a1 = malloc(sizeof(intal));
    intal* a2 = malloc(sizeof(intal));
    intal* b1 = malloc(sizeof(intal));
    intal* b2 = malloc(sizeof(intal));
    intal* p1 = malloc(sizeof(intal));
    intal* p2 = malloc(sizeof(intal));
    intal* p3 = malloc(sizeof(intal));
    intal* aa = malloc(sizeof(intal));
    intal* bb = malloc(sizeof(intal));

	if (a->n%2!=0) {
     	pad(b,a->n+1);
     	pad(a,a->n+1); }
	else if(a->n!=b->n) pad(b,a->n);
	int m=a->n;
	int m2=m/2;
	split(a,a1,a2);
	split(b,b1,b2);
    aa=add(a1,a2);
    bb=add(b1,b2);
    p1=karatsuba(a1,b1);
    p2=karatsuba(a2,b2);
    if (aa->n<bb->n) pad(aa,bb->n);
    else if(aa->n>bb->n) pad(bb,aa->n);
    p3=karatsuba(aa,bb);
    a1=subtract(p3,p1);
    delete_intal(&p3);
    a2=subtract(a1,p2);
    delete_intal(&a1);
    power10(p1,m);
    power10(a2,m2);
    a1=add_intal(p1,a2);
    delete_intal(&p1);
    delete_intal(&a2);
    a2=add_intal(a1,p2);
    delete_intal(&p2);
    delete_intal(&a1);
	a2->s[0]='+';
	return a2; }