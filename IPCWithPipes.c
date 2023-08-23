#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sortArray(int *arr, int size) {
     for (int i = 0; i < size - 1; i++) {
        for (int j = i+1; j < size ; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int pipeChildToParent[2];
    int pipeParentToChild[2];
    if (pipe(pipeChildToParent) == -1) {
        perror("Pipe creation failed");
        return 1;
    }
    if (pipe(pipeParentToChild) == -1) {
        perror("Pipe creation failed");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        close(pipeChildToParent[0]);
        close(pipeParentToChild[1]);
        
       int arr2[100], size2;
      
        if(read(pipeParentToChild[0], &size2, sizeof(size2))==-1){return 1;}
        if(read(pipeParentToChild[0], arr2, size2 * sizeof(int))==-1){return 2;}
        
        sortArray(arr2, size2);
         
         if(write(pipeChildToParent[1], &size2, sizeof(size2))==-1){return 3;}
         if(write(pipeChildToParent[1], arr2, size2 * sizeof(int))==-1){return 4;}
         
       
         close(pipeChildToParent[1]);
         close(pipeParentToChild[0]); 
    }  
    else { // Parent process
        
       
        close(pipeParentToChild[0]);
        close(pipeChildToParent[1]);
        int arr[100], size;
        printf("Enter the size of the array: ");
        scanf("%d", &size);

        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }

        
        if(write(pipeParentToChild[1], &size, sizeof(size))==-1){return 5;}
        if(write(pipeParentToChild[1], arr, size * sizeof(int))==-1){return 6;}
        
        wait(NULL);
        if(read(pipeChildToParent[0], &size, sizeof(size))==-1){return 7;}
        if(read(pipeChildToParent[0], arr, size * sizeof(int))==-1){return 8;}
        
        printf("Sorted array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        close(pipeParentToChild[1]);
        close(pipeChildToParent[0]); 
        
    }

    return 0;
}