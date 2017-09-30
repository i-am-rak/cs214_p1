#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Sorter.h"
#define max 10

//typedef struct _CSVRow
//{
//	char* data;
//	int point;
//	char* string_row;
//}CSVRow

char** b=NULL;

void merge(int llimit,int mid,int rlimit,char* a[])
{
	char str1[100];
	char str2[100];
	int ptr1=llimit,ptr2=mid+1;
	int i;
	for(i=llimit;ptr1<=mid && ptr2<=rlimit;i++)
	{
		int j=0;
		for(j=0;j<strlen(a[ptr1]);j++)
		{
			str1[j]=tolower(a[ptr1][j]);
		}
		str1[j]='\0';
		for(j=0;j<strlen(a[ptr2]);j++)
		{
			str2[j]=tolower(a[ptr2][j]);
		}
		str2[j]='\0';
		//if(strcmp(str1,str2)==0)
//		{
		//	if(a[ptr1].point<a[ptr2].point)
		//	{
		//		b[i]=a[ptr1];
		//		ptr1++;
		//	}
		//	else
		//	{
		//		b[i]=a[ptr2];
		//		ptr2++;
		//	}
//		}
		if(strcmp(str1,str2)<0)
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
	while(ptr1<=mid)
	{
		b[i]=a[ptr1];
		i++;
		ptr1++;
	}
	while(ptr2<=rlimit)
	{
		b[i]=a[ptr2];
		i++;
		ptr2++;
	}
	for(i=llimit;i<=rlimit;i++)
	{
		a[i]=b[i];
	}
}

void sort(int llimit,int rlimit,char* a[])
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

char* callMe(int size,char* a[])
{	
	CSVRow* help[size-1];
	int i;
	printf("List before sorting\n");
	for(i=0;i<=size;i++)
	{
		printf("%s ",a[i]);
	}
	sort(0,max,a);
	printf("\nList after sorting\n");
	for(i=0;i<=max;i++)
	{
		printf("%s ",a[i]);
	}
	printf("\n");
	return "-1";
}

int main(int argc, char** argv)
{
	char* a[11] = {"aiu","c","z","l","t","y","b","ab","w","r","i"};
	b=malloc(sizeof(b)*10);
	callMe(max,a);
	free(b);
	return 0;
}
