
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
void sortNumbersOfFile(FILE* fileToBeSorted, int count){
    int size=count;
    int buffArray[count];
    count = 0;
    fileToBeSorted = fopen("file.txt", "r+");
    while(fscanf(fileToBeSorted, "%d", &buffArray[count])!=EOF){
          count++;
    }
    int temp;
    int i, j; 
    for(i=0; i<size; i++)
    {
        for(j=i+1; j<size; j++) { 
         if(buffArray[i]>buffArray[j])
            {
                temp = buffArray[i];
                buffArray[i] = buffArray[j];
                buffArray[j] = temp;
            }
        }
    }
    rewind(fileToBeSorted);
    for(i=0; i<size; i++)
    {
        fprintf(fileToBeSorted,"%d ",buffArray[i]);
    }
    fclose(fileToBeSorted);
}

int main()
{
    FILE* testFile;
    testFile = fopen("file.txt", "w");
    int count=0;
    printf("Enter Number Of Digits:\n");
    scanf("%d",&count);
    int NoToSort[count];
    printf("Enter Numbers :\n");
    for (int i = 0; i < count; i++) {
        scanf("%d",&NoToSort[i]);
        fprintf(testFile,"%d\n",NoToSort[i]);
    }
    fclose(testFile);
    
     pid_t pid;
     pid = fork();
     
     if(pid<0){
         printf("Process not created");
     }
     else if(pid==0){
        sortNumbersOfFile(testFile,count);
     }
     else {
       wait(NULL);
       testFile=fopen("file.txt", "r");
       if(testFile==NULL){
           perror("file cannot be open");
       }
       int sortedNumber[count];
       int sortedNumbers;
       printf("After Sorting\n");
       while(fscanf(testFile, "%d", &sortedNumbers)!=EOF){
          printf("%d ", sortedNumbers);
       }
       fclose(testFile);
     }
     
    return 0;
    
}