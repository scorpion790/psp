#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    int fd[2];
    int fd2[2];
    pid_t pid;
    pipe(fd);
    pipe(fd2);
    
    pid = fork();

    if (pid == 0) {
        
        close(fd[1]);  
 	int a,fact = 1;

  	read(fd[0], &a, sizeof(int));
	
  	for (int b = a; b > 1; b--){
    	fact = fact * b;
	}
	
        close(fd[0]);
        close(fd2[0]);  
       write(fd2[1], &fact, sizeof(int));
        close(fd2[1]);
    } else {
        
        close(fd[0]);  
        srand(time(NULL));
        int num1,fact;
	num1 = (rand() % 9) + 1;
        
        write(fd[1], &num1, sizeof(int));
        
     
        close(fd[1]);
         close(fd2[1]);  
        
        read(fd2[0], &fact, sizeof(int));
        
     	printf("El factorial de %d = %d\n",num1, fact);
        close(fd2[0]);
        wait(NULL);
    }

    return 0;
}


