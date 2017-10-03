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
	printf("m\n");
	char * str1 = malloc(10000);
	char * str2 = malloc(10000);
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
		printf("0\n");
		if(strcmp(str1,str2)==0)
		{
			if(a[ptr1].point<a[ptr2].point)
			{
				strcpy(b[i].data,str1);
				b[i].point=a[ptr1].point;
				strcpy(b[i].string_row,a[ptr1].string_row);
				ptr1++;
			}
			else
			{
				strcpy(b[i].data,str2);
				b[i].point=a[ptr2].point;
				strcpy(b[i].string_row,a[ptr2].string_row);
				ptr2++;
			}
		}
		printf("1\n");
		if(strcmp(str1,str2)<0)
		{
			strcpy(b[i].data,str1);
			b[i].point=a[ptr1].point;
			strcpy(b[i].string_row,a[ptr1].string_row);
			ptr1++;
		}
		else
		{
			strcpy(b[i].data,str2);
			b[i].point=a[ptr2].point;
			strcpy(b[i].string_row,a[ptr2].string_row);
			ptr2++;
		}
		printf("%d|%s\n",i,b[i].data);
	}
	printf("e\n");
	while(ptr1<=mid)
	{
		strcpy(b[i].data,a[ptr1].data);
		b[i].point=a[ptr1].point;
		strcpy(b[i].string_row,a[ptr1].string_row);	
		i++;
		ptr1++;
	}
	printf("- %d|%s\n",1,b[1].data);
	printf("f\n");
	while(ptr2<=rlimit)
	{
		strcpy(b[i].data,a[ptr2].data);
		b[i].point=a[ptr2].point;
		strcpy(b[i].string_row,a[ptr2].string_row);	
		i++;
		ptr2++;
	}
	printf("-- %d|%s\n",llimit,b[llimit].data);
	printf("%d ",rlimit);
	printf("g\n");
	for(i=llimit;i<=rlimit;i++)
	{
		a[i].point=b[i].point;
		strncpy(a[i].data,b[i].data, strlen(b[i].data));
		strncpy(a[i].string_row,b[i].string_row,strlen(b[i].string_row));
	}
	printf("h\n");
	free(str1);
	free(str2);
	return;
}

void sort(int llimit,int rlimit,CSVRow* a,short type)
{
	printf("s\n");
	if(type==1)
	{
		int mid;
		if(llimit<rlimit)
		{
			mid=(llimit+rlimit)/2;
			sort(llimit,mid,a,type);
			sort(mid+1,rlimit,a,type);
			merge(llimit,mid,rlimit,a);
		}
	}
	else
	{
		int mid;
		if(llimit<rlimit)
		{
			mid=(llimit+rlimit)/2;
			sort(llimit,mid,a,type);
			sort(mid+1,rlimit,a,type);
			merge(llimit,mid,rlimit,a);
		}
	}
	return;
}

void callMe(int size,CSVRow* a,short type)
{	
	int i;
	b=malloc(sizeof(CSVRow)*size);
	for(i=0;i<size;i++)
	{
		b[i].data=malloc(10000);
		b[i].point=i;
		b[i].string_row=malloc(10000);
	}
	printf("%d List before sorting\n", size);
	for(i=0;i<size;i++)
	{
		printf("[%s]",a[i].data);
	}
	//printf("testing: list ended");
	sort(0,size-1,a,1);
	printf("\nList after sorting\n");
	for(i=0;i<size;i++)
	{
		printf("[%s]",a[i].data);
	}
	printf("\n");
	free(b);
	return;
}

int main(int argc, char** argv)
{
	int big=7;
	CSVRow* a=malloc(big*sizeof(CSVRow));
	int i;
	for(i=0;i<big;i++)
	{
		a[i].data=malloc(10000);
		a[i].point=i;
		a[i].string_row=malloc(10000);
		a[i].string_row="\0";
	}
	a[0].data="wq";
	a[1].data="poa";
	a[2].data="aa";
	a[3].data="ab";
	a[4].data="";
	a[5].data="z";
	callMe(big,a,1);
	return 0;
}
