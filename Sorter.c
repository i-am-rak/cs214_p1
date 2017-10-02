#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Sorter.h"

CSVRow* b=NULL;

void mergeInt(int llimit,int mid,int rlimit,CSVRow* a)
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
		if(strtol(str1,NULL,10)==strtol(str2,NULL,10))
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
		if(strtol(str1,NULL,10)<strtol(str2,NULL,10))
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

void sort(int llimit,int rlimit,CSVRow* a,short type)
{
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
			mergeInt(llimit,mid,rlimit,a);
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
	//printf("%d List before sorting\n", size);
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


int main(int argc, char ** argv){

	int file_count = 0;
	char c = 0;
	int i = 0;
	char * str_file = malloc(10);
	char * token = malloc(10);
	int row_position = 0;

	if(stdin == NULL){
		fprintf(stderr, "ERROR: <No Input In STDIN>\n");	
		free(token);
		free(str_file);			
		return 0;
	}
	
	if(argv[1] == NULL){
		fprintf(stderr, "ERROR: <Expected -c \"item\">\n");	
		free(token);
		free(str_file);
		return 0;
	}

	if(argv[1][0] != '-' && argv[1][1] != 'c' && argv[2] == NULL){
		fprintf(stderr, "ERROR: <Expected -c \"item\">\n");
		free(token);
		free(str_file);
		return 0;
	}
	
	token = strdup(argv[2]);

	//fprintf(stdout, "%s\n", token);	
				
	c = getc(stdin);
	while (c != EOF) {
		//printf("%c\n",c);
		str_file = realloc(str_file, (i+1) * sizeof(char));	
		str_file[i] = c;
		if(c == '\n'){
			file_count++;
		}
		i++;
		c = getc(stdin);
    }
        
	str_file[i] = '\0';
	
	CSVRow *movies = malloc(file_count * sizeof(CSVRow));
	//token = strtok(str_file, "\n");
	
	for(int j = 0; j < file_count; j++){
		movies[j].data = malloc(1000);
		movies[j].point = j;
		movies[j].string_row = malloc(1000);
	}

	int temp = 0;
	int count = 0;
	int index = 0;
	int comma_position_max = 0;
	int p1 = 0;
	int p2 = 0;
	int char_found = 0;
	int comma_number = 0;
	char * check_token = malloc(1000);
	c = 0;

	for(int j = 0; j < i; j++){
		if(str_file[j] == '\n'){
			//printf("a\n");
			movies[count].string_row = strndup(str_file+temp,j-temp+1);
			movies[count].string_row[j-temp+1] = '\0';
			if (count == 0){
				c = movies[count].string_row[index];
				for(index = 0; c != '\n' ; index++){
					//fprintf(stdout, "%c\n", c);
					c = movies[count].string_row[index];
					if(c == ','){
						comma_position_max++;
						if(index == p1 || index == p1+1){
							check_token = "NULL";
						}
						else{
							strncpy(check_token, movies[count].string_row+p1,index-p1);
							check_token[index-p1] =  '\0';
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
						}
						if(strcmp(check_token,token) == 0){
							char_found = 1;
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
							break;
						}
						p1 = index+1;
						
					}
				}
				if(char_found == 0){
					fprintf(stderr, "ERROR: <Selected item was not found in parameters>\n");
					free(check_token);
					free(movies);
					free(token);
					free(str_file);

					return 0;
				}
				//fprintf(stdout,"%d : %d\n",char_found , comma_position_max);
				//fprintf(stdout, "[%s] : [%s] \n",token, check_token);
				strcpy(movies[count].data, token);
				movies[count].data[strlen(token)+1] = '\0';
			}
			else{
				//fprintf(stdout, "%d \n ", count);
				comma_number = 0;
				index = 0;
				p1 = 0;
				c = movies[count].string_row[index];
				for(index = 0; c != '\n' ; index++){
					//fprintf(stdout, "%c\n", c);
					c = movies[count].string_row[index];
					if(c == ','){
						comma_number++;
						if((index == p1 || index == p1+1) && (comma_number == comma_position_max)){
							movies[count].data = "0\0";
							break;
						}
						else if(comma_number == comma_position_max){
							strncpy(movies[count].data, movies[count].string_row+p1,index-p1);
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
							movies[count].data[index-p1] = '\0';
							//fprintf(stdout, "%d: %s\n",count, movies[count].data);	
							break;
						}
						p1 = index+1;
					}
				}
			}
			
			temp = j+1;
			count++;
		}
	}
	
	short type = 0;

	for(int j = 1; j < file_count; j++){
		for( int k = 0; movies[j].data[k] != '\0'; k++){
			if(!(isdigit(movies[j].data[k]))){
				if(movies[j].data[k] != '.' || movies[j].data[k] != '-'){
					type = 1;	
				}
			}
		}
	}
	printf("%d \n", type);
	callMe(file_count, movies, type);
	for(int j = 0; j < file_count; j++){
		//fprintf(stdout, "[%s]\n %s", movies[j].data, movies[j].string_row);
	}
	

	
/*	
	for(int j = 0; j < file_count; j++){
		free(movies[j].data);
		movies[j].point = j;
		free(movies[j].string_row);
	}
*/
	free(check_token);
	free(movies);
	
	free(token);
	free(str_file);
	return 0;
}
