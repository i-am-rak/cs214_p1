#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char ** argv){
	fprintf(stdout,"testing for something\n");
	FILE* fp;
	int bufferSize = 100000;
	char * buff = calloc(1,100000+1);

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		fprintf(stderr, "ERROR: <File not found>\n");
		free(buff);
		return 0;
	}

	while(fgets(buff, bufferSize, (FILE*)fp) != NULL){
			fprintf(stdout,"%s \n", buff);
	}

	free(buff);
	fclose(fp);
	return 0;
}
