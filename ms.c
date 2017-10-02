#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Sorter.h"

//typedef struct _CSVRow
//{
//	char* data;
//	int point;
//	char* string_row;
//}CSVRow

CSVRow* b=NULL;

void merge(int llimit,int mid,int rlimit,CSVRow* a)
{
	char str1[1000];
	char str2[1000];
	int ptr1=llimit,ptr2=mid+1;
	int i;
	for(i=llimit;ptr1<=mid && ptr2<=rlimit;i++)
	{
		int j=0;
		for(j=0;j<strlen(a[ptr1].data);j++)
		{
			str1[j]=tolower(a[ptr1].data[j]);
		}
		str1[j]='\0';
		for(j=0;j<strlen(a[ptr2].data);j++)
		{
			str2[j]=tolower(a[ptr2].data[j]);
		}
		str2[j]='\0';
		if(strcmp(str1,str2)==0)
		{
			if(a[ptr1].point<a[ptr2].point)
			{
				b[i]=a[ptr1];
				ptr1++;
			}
			else
			{
				b[i]=a[ptr2];
				ptr2++;
			}
		}
		if(strcmp(str1,str2)<0)
		{
			b[i].data=a[ptr1].data;
			b[i].point=a[ptr1].point;
			b[i].string_row=a[ptr1].string_row;
			ptr1++;
		}
		else
		{
			b[i].data=a[ptr2].data;
			b[i].point=a[ptr2].point;
			b[i].string_row=a[ptr2].string_row;
			ptr2++;
		}
	}
	while(ptr1<=mid)
	{
		b[i].data=a[ptr1].data;
		b[i].point=a[ptr1].point;
		b[i].string_row=a[ptr1].string_row;	
		i++;
		ptr1++;
	}
	while(ptr2<=rlimit)
	{
		b[i].data=a[ptr2].data;
		b[i].point=a[ptr2].point;
		b[i].string_row=a[ptr2].string_row;	
		i++;
		ptr2++;
	}
	for(i=llimit;i<=rlimit;i++)
	{
		a[i].data=b[i].data;
		a[i].point=b[i].point;
		a[i].string_row=b[i].string_row;
	}
	return;
}

void sort(int llimit,int rlimit,CSVRow* a)
{
	int mid;
	if(llimit<rlimit)
	{
		mid=(llimit+rlimit)/2;
		sort(llimit,mid,a);
		sort(mid+1,rlimit,a);
		merge(llimit,mid,rlimit,a);
	}
	return;
}

void callMe(int size,CSVRow* a)
{	
	int i;
	b=malloc(sizeof(CSVRow)*size);
	for(i=0;i<5;i++)
	{
		b[i].data=malloc(1000);
		b[i].point=i;
		b[i].string_row=malloc(1000);
	}
	printf("List before sorting\n");
	for(i=0;i<size;i++)
	{
		printf("%s ",a[i].data);
	}
	sort(0,size-1,a);
	printf("\nList after sorting\n");
	for(i=0;i<size;i++)
	{
		printf("%s ",a[i].data);
	}
	printf("\n");
	free(b);
	return;
}

int main(int argc, char** argv)
{
	CSVRow* a=malloc(5*sizeof(CSVRow));
	int i;
	for(i=0;i<5;i++)
	{
		a[i].data=malloc(1000);
		a[i].point=i;
		a[i].string_row=malloc(1000);
	}
	a[0].data="wq";
	a[1].data="poa";
	a[2].data="aa";
	a[3].data="ab";
	a[4].data="z";
	callMe(i,a);
	return 0;
}
