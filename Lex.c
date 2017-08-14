//-----------------------------------------------------------------------------
// Lex.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
	
	int count=0;
	FILE *in, *in2, *out;
	char line[MAX_LEN];
	char* token;
	
	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing 
	in = fopen(argv[1], "r");
	in2 = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( in2==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
   /* read each line of input file to get size needed for initialization of array */
   while( fgets(line, MAX_LEN, in2) != NULL)  {
   		token = line;
   		count++;
   	}

   char** tokenlist = calloc(count, sizeof(char*));
   int n=0;

   /* read each line of input file to put into array */
	while( fgets(line, MAX_LEN, in) != NULL)  {
		if(strcmp(line,"\n")==0) {
			token=line;
		}
		else {
			token = strtok(line, "\n");
		}
   		char* temp = calloc(count, sizeof(char*)+1);
   		strcpy(temp,token);
   		tokenlist[n] = temp;
   		n++;
   	}

   	List L = newList();
   	
   	for(int j=1; j<count; j++) {
   		char* temp = tokenlist[j];
   		int i = j-1;
   		if( length(L)==0) {
   			prepend(L,0);
   		}
   		if( length(L)>0 ) {
   			moveFront(L);
   			while( index(L) != i ) {
   				moveNext(L);
   			}
   		}
   		while( i>=0 && strcmp(temp, tokenlist[get(L)] ) < 0 ) {
   			//array[i+1] = array[i];
   			movePrev(L);
   			i--;
   		}
   		//array[i+1] = temp;
   		if(index(L) == -1 ) {
   			prepend(L,j);
   		}
   		else {
   			insertAfter(L,j);
   		}
   	}

   	moveFront(L);
   	for(int i=0; i<count; i++) {
   		fprintf(out, "%s\n", tokenlist[get(L)] );
   		moveNext(L);
   	}
   	
   	
   	freeList(&L);
    for(int i=0; i<count; i++) {
    	free(tokenlist[i]);
    }
    free(tokenlist);
    
   	fclose(in);
   	fclose(in2);
   	fclose(out);
   
   return(0);
}





