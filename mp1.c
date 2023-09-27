#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, pid_hijo;
  pid = fork();
  printf("jorge");
 
  if (pid == -1 ) 
  {
    printf("ERROR !!! No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )   
  {        
    printf("Soy el proceso hijo ... \n");	  
  }
  else    
  { 
   pid_hijo = wait(NULL);
   printf("pid del hijo= %d\n",pid);
  printf("pid del padre= %d\n",getppid());        
  }
   exit(0);
}
