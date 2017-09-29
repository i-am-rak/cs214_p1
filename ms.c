#include <stdio.h>
#include <string.h>
#include "Sorter.h"
#define max 10

typedef struct Thing_
{
	char* str;
	char* smthingElse;
	char* pointlessField;
	int position;
}Thing;

char* a[12] = {"aiu","c","","z","l","t","y","b","ab","w","r","i"};
char* b[11];

void merge(int llimit,int mid,int rlimit)
{
	int ptr1=llimit,ptr2=mid+1;
	int i;
	for(i=llimit;ptr1<=mid && ptr2<=rlimit;i++)
	{
      		if(strcmp(a[ptr1],a[ptr2])<0)
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

void sort(int llimit,int rlimit)
{
	int mid;
   	if(llimit<rlimit)
	{
      		mid=(llimit+rlimit)/2;
      		sort(llimit,mid);
      		sort(mid+1,rlimit);
	        merge(llimit,mid,rlimit);
  	}
   	return;
}

char* callMe(char* toSort,char* helper,int size)
{	int i;
	printf("List before sorting\n");
	for(i=0;i<=max;i++)
	{
		printf("%s ",a[i]);
	}
	sort(0,max);
	printf("\nList after sorting\n");
	for(i=0;i<=max;i++)
	{
      		printf("%s ",a[i]);
	}
	printf("\n");
	return "-1";
}

int main()
{ 

	callMe(NULL,NULL,max);
}
