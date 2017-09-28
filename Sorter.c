#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Sorter.h"

int main(int argc, char ** argv){
	//fprintf(stdout,"testing for something\n");
	FILE* fp;
	int bufferSize = 100000;
	char * buff = calloc(1,100000+1);

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		fprintf(stderr, "ERROR: <File not found>\n");
		free(buff);
		return 0;
	}
	char * token;
	int count = 0;
	int file_count = 0;
	char c = 0;

	for (c = getc(fp); c != EOF; c = getc(fp)){
		if(c == '\n')
			file_count++;
	}
	fclose(fp);
	fp = fopen(argv[1], "r");
	
	CSVRow movies[file_count];
	
	while(fgets(buff, bufferSize, (FILE*)fp) != NULL){

			if(buff[strlen(buff)-1] == '\n'){
				buff[strlen(buff)-1] = '\0';
			}
			
			movies[count].string_row = strdup(buff);
			*/
			count++;
	}
	
	for(int i = 0; i < file_count; i++){
		fprintf(stdout, "%s \n", movies[i].string_row);
	}

	free(buff);
	fclose(fp);
	return 0;
}
