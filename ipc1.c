#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <time.h>

void main(){

     int fd[2]; 
     char buffer[50];
    time_t rawtime;
    struct tm *timeinfo;
    char datetime_str[50]; 

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(datetime_str, sizeof(datetime_str), "%d/%m/%Y %H:%M:%S", timeinfo);
    

     pid_t pid;
    
     pipe(fd); 
     
     //Se crea un proceso hijo
     pid = fork();

     if (pid==0)
     
     {
                close(fd[1]); // Cierra el descriptor de escritura
                printf("el id de p2 es (PID: %d) \n", getpid());
                read(fd[0], buffer, 50);
                printf("\t Mensaje leido del pipe: %s \n", buffer);
     
     }
     
     else
     
     {
                close(fd[0]); // Cierra el descriptor de lectura
                printf("El padre escribe en el PIPE...\n");
                write(fd[1], datetime_str , 50);  
                wait(NULL);    
     }
     
        
}
