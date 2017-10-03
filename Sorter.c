#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Sorter.h"

void transfer(CSVRow *a, CSVRow *b, int k, int c){
		b[k].data = strdup(a[c].data);
		b[k].data[strlen(a[c].data)]= '\0';
		b[k].data = a[c].data;
		b[k].string_row = strdup(a[c].string_row);
		b[k].string_row[strlen(a[c].string_row)]= '\0';
		return;
}

void merge(CSVRow * a, CSVRow * temp, int i1,int j1,int i2,int j2)
{
	//array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
 	//printf("hi\n");   
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(strcmp(a[i].data,a[j].data))
            transfer(temp,a,k++,i++);
        else
            transfer(temp,a,k++,j++);
    }
 	//printf("hi2\n");   
    while(i<=j1){    //copy remaining elements of the first list
        //printf("11%d\n", i);
		k++;
		i++;
		transfer(temp,a,k,i);
	}    
    while(j<=j2) {   //copy remaining elements of the second list
        //printf("22%d\n", j);
		k++;
		j++;
		transfer(temp,a,k,j);
    }
   	//printf("hi3\n"); 
	//Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        transfer(a,temp,i,j);

	return;
}

void mergesort(CSVRow * a, CSVRow * temp, int i,int j)
{
    //printf("hia\n");   
	int mid;        
    if(i<j)
    {
        mid=(i+j)/2;
        mergesort(a,temp,i,mid);        //left recursion
        mergesort(a,temp,mid+1,j);    //right recursion
        merge(a,temp, i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
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

	
	CSVRow *tempy = malloc(file_count * sizeof(CSVRow));
	//token = strtok(str_file, "\n");
	
	for(int j = 0; j < file_count; j++){
		tempy[j].data = malloc(1000);
		tempy[j].point = j;
		tempy[j].string_row = malloc(1000);
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
					if(c == ',' && index+1 != strlen(movies[count].string_row) && movies[count].string_row[index+1] == '"'){
							
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
						
						index = index+2;
						for(int x = 0; c != '"'; index++){
							c = movies[count].string_row[index];
						}	
						
						c = movies[count].string_row[index];
						//fprintf(stdout,"%c\n" , c);
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
						index++;
						c = movies[count].string_row[index];
	
					}
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
	
	mergesort(movies, tempy,0, file_count-2);
	printf("heyo\n");
	for(int j = 0; j < file_count; j++){
		fprintf(stdout, "[%s]", movies[j].data);
		//printf("[%s]\n", movies[j].data);
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
