#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>
#include<math.h>
#define total_records 10000

struct hash {
    char key[11];
    char value[100];
};

int count1=0,count2=0;
double number_of_records;
double records_to_read=1000;

int pass=1;

void quickSort(struct hash records[], long int low, long int high);
void swap(struct hash *a, struct hash *b);
int partition (struct hash records[],long int low1, long int high1);
int compare_string(char a[11],char b[11]);


int  main(int argc,char* argv[]){

	FILE *fp1 =fopen("1.txt","r");

	fseek(fp1, 0, SEEK_END); // seek to end of file
	double file_size = ftell(fp1); // get current file pointer
	printf("File Size is :%lf\n",file_size);
	double no_of_lines = file_size/100;
	number_of_records =no_of_lines;

	double buffer_size = atof(argv[1]);
	printf("Buffer size is %lf",buffer_size);

	int number_of_files = 10;//ceil((no_of_lines*100)/buffer_size);

	//char *buffer = malloc(buffer_size * sizeof(char));

	printf("No of files : %d\n",number_of_files);
	printf("No of Lines : %lf\n",no_of_lines);
	fclose(fp1);

	struct hash *records = malloc((records_to_read*10)* sizeof(struct hash));

	char *str1 = malloc(100 * sizeof(char));

	FILE *fp[number_of_files];

	for(long int i=0;i<number_of_files;i++){
		char str[10];
        sprintf(str, "%ld.txt", i+1);
		fp[i] = fopen(str,"r");
		if(!fp[i])
            continue;
	}

//printf("Abhinav");

	int counter=1;
	long int loc=0;
	while(!feof(fp[number_of_files-1]))
	{//printf("Abhinav");
		//printf("\npointer loc %d",*records);
		if(counter==1){
			for(int j=0;j<number_of_files;j++){	
				
				for(long int i=0;i<records_to_read;i++){


  					fgets(str1, 100, fp[j]);
  					if(strcmp(str1, "\n")==0)
    					fgets(str1, 100, fp[j]);
    				
					strncpy(records[loc].key, str1,10); // Extracting key
					strncpy(records[loc].value,str1,100);
					
					loc++;
                    //free(str1);
					//printf("%li\n",loc);
					
				}
				//memcpy(records1,records,(records_to_read*10)* sizeof(struct hash));
				
			}//printf("Abhinav");
			quickSort(records, 0, (records_to_read*10)-1);
			pass=pass+9;
			//printf("Pass %d\n",pass);
			counter++;
			//free(records);
			//exit(0);
			//printf("\npointer loc %d",*recor ds);
		}
		
		else if((counter>1) && (pass>0)){

			for(int j=0;j<number_of_files;j++){	
				loc=0;
				for(long int i=0;i<records_to_read;i++){


  					fgets(str1, 100, fp[j]);
  					if(strcmp(str1, "\n")==0)
    					fgets(str1, 100, fp[j]);
    				
					strncpy(records[loc].key, str1,11); // Extracting key
					strncpy(records[loc].value,str1,100);
					
					loc++;
					//printf("%li\n",loc);
					
				}
				//memcpy(records1,records,(records_to_read*10)* sizeof(struct hash));
				counter++;
				
    			
    			
    			pass++;
				quickSort(records, 0, (records_to_read*10)-1);
				//printf("Pass %d\n",pass);

			}//printf("Abhinav");
			
			//free(records);

			//printf("\npointer loc %d",*records);
		}
				//memcpy(records1,records,(records_to_read*10)* sizeof(struct hash));
		else
		break;		
				
			
		
	}
}


void swap(struct hash *a, struct hash *b)
{
   
    
    struct hash t = *a;
    *a = *b;
    *b = t;
    //records1[pos1]=a;
    //records1[pos2]=b;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (struct hash records1[], long int low1, long int high1)
{
    //printf("%s\n",records[high1].key);
    //printf("%li\n",high1);
    char *pivot = malloc(11 * sizeof(char));
    
    long int mid =(low1+high1)/2;
    //printf("%s\n",records[high1].key);
    strncpy(pivot,records1[mid].key,11);
    //printf("%s\n",records1[high1].key);
    //printf("%s\n",records1[low1].key);
    //printf("%s\n",pivot);
    //char pivot[] = records2[high1].key;    // pivot
    
    long int m = (low1-1);  // Index of smaller element
 
    for (long int j = low1; j <= high1- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot

    	int a =compare_string(records1[j].key,pivot);
       if(a<=0)
        {
            m++;    // increment index of smaller element
            //printf("Inside partition %s\n",records1[j].key);
            //exit(0);
            //printf("%.10s\n", records1[i].value);
            //printf("%.10s\n", records1[j].value);
            swap(&records1[m], &records1[j]);
            //printf("%.10s\n", records1[i].value);
            //printf("%s\n", records1[j].value)    
            
        }
    }
    swap(&records1[m + 1], &records1[high1]);
    free(pivot);
    //printf("Outside Partition\n%s\n", records1[0].value);

    return (m + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(struct hash records1[], long int low, long int high)

{   
    count1++;
    
  	//printf("Abhinav");
    if (low < high)
    {  count2++; 

        /* pi is partitioning index, arr[p] is now
           at right place */
        //for (int j=0; j<100; j++)
        //printf("%s\n",records1[high].key);
        long int pi = partition(records1, low, high);
        //printf("%s\n", records1[1].value);
        
        // Separately sort elements before
        // partition and after partition
        //printf("Abhinav\n");
        
        quickSort(records1, low, pi - 1);
        
        //printf("Phase 1 completed");

        //printf("\n%dcount\n",count);
        //exit(0);
        //printf("%s\n",records1[0].value);
        
        quickSort(records1, pi + 1, high);
        
        //printf("Phase1 completed");
        count2--;
        count1--;
        //printf("%s\n",records1[0].value);
    }
    
    
      //printf("Count is %d\n",count);
    else if (count1>0)
      count1--;


    if(count1==0 && count2==0)
    {
      printf("Count is %d %d\n",count1,count2);
      FILE *fp_t = fopen("sorted.txt", "a");
      //FILE *fp_t1 = fopen("dat_sort.txt", "w");
      if(!fp_t) {
        printf("Error file reading file");
        
    }
    
    // Write sorted record to file
    if((total_records-records_to_read*pass)>=records_to_read){
    		for (long int j=0; j<records_to_read; j++){
        		fprintf(fp_t,"%s\n", records1[j].value);}
        		
    	}
    	else{
    		for (long int j=0; j<records_to_read*10; j++){
        	fprintf(fp_t,"%s\n", records1[j].value);}
        	pass=0;
        }
    //for(long int j=records_to_read;j<(records_to_read*10);j++)  
    //	fprintf(fp_t1,"%s\n", records1[j].value);

    fclose(fp_t);

    //pass++;
    //fclose(fp_t1);
    //printf("Abhinav");
    //(&records1);
    }        
    
}

int compare_string(char x[11],char y[11]){

    for(int i=0;i<11;i++){
        
        if(x[i]==' ' && y[i]==' ')
            continue;
        else if(x[i]==' ' && y[i]!=' ')
            return -1;
        else if(x[i]!=' ' && y[i]==' ')
            return 1;

        else if(x[i]>y[i]){
            
            return 1;}
        
        else if (x[i]<y[i]){
            return -1;
            
        }
        if((i+1)==11)
            return 0;
    }
}