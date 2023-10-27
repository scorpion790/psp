#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    int fd[2];
    pid_t pid;
    
   

    pid = fork();

   

    if (pid == 0) {
       
        close(fd[0]);  

        
        srand(time(NULL));
        int num1 = (rand() % 50) + 1;
        int num2 = (rand() % 50) + 1;

        printf("Proceso hijo generó %d y %d\n", num1, num2);


        write(fd[1], &num1, sizeof(int));
        write(fd[1], &num2, sizeof(int));

        close(fd[1]);
    } else {
        
        close(fd[1]);  
        int num1, num2,num3;

        
        read(fd[0], &num1, sizeof(int));
        read(fd[0], &num2, sizeof(int));
       

        
        printf("Proceso padre recibió %d y %d\n", num1, num2);
        printf("Suma: %d\n", num1 + num2);
        printf("Diferencia: %d\n", num1 - num2);
        printf("Producto: %d\n", num1 * num2);
        
        printf("Proceso padre recibió %d y %d\n", num2, num1);
        printf("Suma: %d\n", num2 + num1);
        printf("Diferencia: %d\n", num2 - num1);
        printf("Producto: %d\n", num2 * num1);

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}
