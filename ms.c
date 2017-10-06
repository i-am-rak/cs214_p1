#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Sorter.h"


void mergeStr(int llimit,int rlimit,int mid,CSVRow* arr,int size)
{
	int i;
	int k=0;
	CSVRow* help=malloc(sizeof(CSVRow)*size);
	for(i=0;i<size;i++)
	{
		help[i].data=malloc(100);
		help[i].point=i;
		help[i].string_row=malloc(1000);
	}
	int ptr1=llimit;
	int ptr2=mid;
	for(;ptr1<mid && ptr2<=rlimit;)
	{
		if(strcmp(arr[ptr1].data,arr[ptr2].data)==0)
		{
			if(arr[ptr1].point<arr[ptr2].point)
			{
				strcpy(help[k].data,arr[ptr1].data);
				help[k].point=arr[ptr1].point;
				strcpy(help[k].string_row,arr[ptr1].string_row);
				k++;
				ptr1++;
			}
			else
			{
				strcpy(help[k].data,arr[ptr2].data);
				help[k].point=arr[ptr2].point;
				strcpy(help[k].string_row,arr[ptr2].string_row);
				k++;
				ptr2++;
			
			}
		}
		else if(strcmp(arr[ptr1].data,arr[ptr2].data)<0)
		{
			strcpy(help[k].data,arr[ptr1].data);
			help[k].point=arr[ptr1].point;
			strcpy(help[k].string_row,arr[ptr1].string_row);
			k++;
			ptr1++;
		}
		else
		{
			strcpy(help[k].data,arr[ptr2].data);
			help[k].point=arr[ptr2].point;
			strcpy(help[k].string_row,arr[ptr2].string_row);
			k++;
			ptr2++;
		}
	}
	while(ptr1<mid)
	{
		strcpy(help[k].data,arr[ptr1].data);
		help[k].point=arr[ptr1].point;
		strcpy(help[k].string_row,arr[ptr1].string_row);
		k++;
		ptr1++;
	}
	while(ptr2<=rlimit)
	{
		strcpy(help[k].data,arr[ptr2].data);
		help[k].point=arr[ptr2].point;
		strcpy(help[k].string_row,arr[ptr2].string_row);
		k++;
		ptr2++;
	}
	for(i=llimit,k=0;i<=rlimit;i++,k++)
	{
		strcpy(arr[i].data,help[k].data);
		arr[i].point=help[k].point;
		strcpy(arr[i].string_row,help[k].string_row);
	}
	for(i=0;i<size;i++)
	{
		free(help[i].data);
		free(help[i].string_row);
	}
	free(help);
	return;
}

void mergeInt(int llimit,int rlimit,int mid,CSVRow* arr,int size)
{
	int i;
	int k=0;
	CSVRow* help=malloc(sizeof(CSVRow)*size);
	for(i=0;i<size;i++)
	{
		help[i].data=malloc(100);
		help[i].point=i;
		help[i].string_row=malloc(1000);
	}
	int ptr1=llimit;
	int ptr2=mid;
	for(;ptr1<mid && ptr2<=rlimit;)
	{
		if(strtol(arr[ptr1].data,NULL,10)==strtol(arr[ptr2].data,NULL,10))
		{
			if(arr[ptr1].point<arr[ptr2].point)
			{
				strcpy(help[k].data,arr[ptr1].data);
				help[k].point=arr[ptr1].point;
				strcpy(help[k].string_row,arr[ptr1].string_row);
				k++;
				ptr1++;
			}
			else
			{
				strcpy(help[k].data,arr[ptr2].data);
				help[k].point=arr[ptr2].point;
				strcpy(help[k].string_row,arr[ptr2].string_row);
				k++;
				ptr2++;
			
			}
		}
		else if(strtol(arr[ptr1].data,NULL,10)<strtol(arr[ptr2].data,NULL,10))
		{
			strcpy(help[k].data,arr[ptr1].data);
			help[k].point=arr[ptr1].point;
			strcpy(help[k].string_row,arr[ptr1].string_row);
			k++;
			ptr1++;
		}
		else
		{
			strcpy(help[k].data,arr[ptr2].data);
			help[k].point=arr[ptr2].point;
			strcpy(help[k].string_row,arr[ptr2].string_row);
			k++;
			ptr2++;
		}
	}
	while(ptr1<mid)
	{
		strcpy(help[k].data,arr[ptr1].data);
		help[k].point=arr[ptr1].point;
		strcpy(help[k].string_row,arr[ptr1].string_row);
		k++;
		ptr1++;
	}
	while(ptr2<=rlimit)
	{
		strcpy(help[k].data,arr[ptr2].data);
		help[k].point=arr[ptr2].point;
		strcpy(help[k].string_row,arr[ptr2].string_row);
		k++;
		ptr2++;
	}
	for(i=llimit,k=0;i<=rlimit;i++,k++)
	{
		strcpy(arr[i].data,help[k].data);
		arr[i].point=help[k].point;
		strcpy(arr[i].string_row,help[k].string_row);
	}
	for(i=0;i<size;i++)
	{
		free(help[i].data);
		free(help[i].string_row);
	}
	free(help);
	return;
}

void sortStr(int llimit,int rlimit,CSVRow* arr,int size)
{
	if(llimit<rlimit)
	{
		int mid=(llimit+rlimit)/2;
		sortStr(llimit,mid,arr,size);
		sortStr(mid+1,rlimit,arr,size);
		mergeStr(llimit,rlimit,mid+1,arr,size);
	}
	return;
}

void sortInt(int llimit,int rlimit,CSVRow* arr,int size)
{
	if(llimit<rlimit)
	{
		int mid=(llimit+rlimit)/2;
		sortInt(llimit,mid,arr,size);
		sortInt(mid+1,rlimit,arr,size);
		mergeInt(llimit,rlimit,mid+1,arr,size);
	}
	return;
}

void callMe(int size,char type,CSVRow* arr)
{
	if(type=='i')
	{
		sortInt(0,size-1,arr,size);
	}
	else
	{
		sortStr(0,size-1,arr,size);
	}
	return;
}

int main()
{
	int num=10;
	CSVRow* arr=malloc(sizeof(CSVRow)*num);
	int i;
	for(i=0;i<num;i++)
	{
		arr[i].data=malloc(1000);
		arr[i].point=i;
		arr[i].string_row=malloc(1000);
	}
	for(i=0;i<num;i++)
	{
		scanf("%s",arr[i].data);
	}
	printf("\n");
	sortStr(0,num-1,arr,num);
	for(i=0;i<num;i++)
	{
		printf("%s ",arr[i].data);
	}
	printf("\n");
	for(i=0;i<num;i++)
	{
		free(arr[i].data);
		free(arr[i].string_row);
	}
	free(arr);
	return 0;
}
