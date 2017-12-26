#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>
#include<math.h>
#include<sys/wait.h>
#include <unistd.h>


long queueCounter;
static pthread_mutex_t mutex_queue=PTHREAD_MUTEX_INITIALIZER;


int  main(int argc,char* argv[]){


	FILE *fp =fopen(argv[1],"r");

	fseek(fp, 0, SEEK_END); // seek to end of file
	double file_size = ftell(fp); // get current file pointer
	printf("File Size is :%lf\n",file_size);
	double no_of_lines = file_size/100;

	double buffer_size = 100000;
	printf("Buffer size is %lf",buffer_size);

	int number_of_files = ceil((no_of_lines*100)/buffer_size);

	char *buffer = malloc(buffer_size * sizeof(char));

	printf("No of files : %d\n",number_of_files);
	printf("No of Lines : %lf\n",no_of_lines);
	fseek(fp, 0, SEEK_SET);
	char line[100];
	
	for(long j=0;j<number_of_files;j++)
	{	
		char str[10];
        sprintf(str, "%ld.txt", j+1);
        
        FILE *fp_t = fopen(str, "w+");
        if(!fp_t)
            continue;
        
        // Reading input file 
        fread(buffer, sizeof(char), buffer_size, fp);
        // Writing chunk file 
        fwrite(buffer, sizeof(char), buffer_size, fp_t);
        
        fclose(fp_t);
    }
    fclose(fp);
	free(buffer);
	char program[15];
	/*for(long i=1;i<=number_of_files;i++){
		sprintf(program, "./sort %ld.txt %ld", i,i);
		system(program,wait=True);
		sleep(10);
	}
	sprintf(program, "./merge %lf",buffer_size);
	system(program);
	*/
	

}

