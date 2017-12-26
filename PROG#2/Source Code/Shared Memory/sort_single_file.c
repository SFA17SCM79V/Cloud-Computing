#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>
#include<math.h>

int file_j = 0;

struct hash {
    char key[11];
    char value[100];
};

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
//#define number_of_records 100

double number_of_records;
void quickSort(struct hash records[], int low, int high);
void swap(struct hash *a, struct hash *b,struct hash records1[],int pos1,int pos2);
int partition (struct hash records[], int low1, int high1);
int count1=0,count2=0;

int  main(int argc,char* argv[]){
    
file_j = (int)argv[2];
FILE *fp =fopen(argv[1],"r");
fseek(fp, 0, SEEK_END); // seek to end of file
double file_size = ftell(fp); // get current file pointer
//printf("File Size is :%lf\n",file_size);
number_of_records = file_size/100;
printf("Number of records :%lf\n",number_of_records);
fseek(fp, 0, SEEK_SET);

//char *buffer = malloc(number_of_records*100 * sizeof(char));
struct hash *records = malloc(number_of_records* sizeof(struct hash));

char *str1 = malloc(100 * sizeof(char));

//printf("Abhinav");
for(int i=0;i<number_of_records;i++){


  fgets(str1, 100, fp);
  if(strcmp(str1, "\n")==0)
    fgets(str1, 100, fp);

strncpy(records[i].key, str1,10); // Extracting key
strncpy(records[i].value,str1,100);


//printf("%s\n",records[i].key);
//printf("%s\n",records[i].value);



}
fclose(fp);
printf("Reading from disk completed");
quickSort(records, 0, number_of_records-1);
free(records);


}


void swap(struct hash *a, struct hash *b,struct hash records1[],int pos1,int pos2)
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
int partition (struct hash records1[], int low1, int high1)
{
    //printf("%s\n",records[high1].key);
    char *pivot = malloc(10 * sizeof(char));
    
    //printf("%s\n",records[high1].key);
    strncpy(pivot,records1[high1].key,10);
    //printf("%s\n",records1[high1].key);
    //printf("%s\n",records1[low1].key);
    //printf("%s\n",pivot);
    //char pivot[] = records2[high1].key;    // pivot
    
    int i = (low1 - 1);  // Index of smaller element
 
    for (int j = low1; j <= high1- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
       if(strcmp(records1[j].key,pivot)<=0)
        {
            i++;    // increment index of smaller element
            //printf("Inside partition %s\n",records1[j].key);
            //exit(0);
            //printf("%.10s\n", records1[i].value);
            //printf("%.10s\n", records1[j].value);
            swap(&records1[i], &records1[j],records1,i,j);
            //printf("%.10s\n", records1[i].value);
            //printf("%s\n", records1[j].value);
            
           
            
            
        }
    }
    swap(&records1[i + 1], &records1[high1],records1,i+1,high1);
    free(pivot);
    //printf("Outside Partition\n%s\n", records1[0].value);

    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(struct hash records1[], int low, int high)

{   
    count1++;
  
  
    if (low < high)
    {  count2++; 

        /* pi is partitioning index, arr[p] is now
           at right place */
        //for (int j=0; j<100; j++)
        //printf("%s\n",records1[j].key);
        int pi = partition(records1, low, high);
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
        char str[10];
        sprintf(str, "%d.txt", file_j+11);
        
        FILE *fp_t = fopen(str, "w");
        if(!fp_t)
            printf("Error file reading file");
         
      printf("Count is %d %d\n",count1,count2);
      
    
    
    // Write sorted record to file
    for (int j=0; j<number_of_records; j++){
        fprintf(fp_t,"%s\n", records1[j].value);}
    
        
    
    fclose(fp_t);

        


    }


     
        
    
}