
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid1, pid2, pid3, pid4;
    int shm_id;
    int *suma;
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    suma = (int *)shmat(shm_id, NULL, 0);
        printf("el id de p1 es (PID: %d) \n", getpid());
        printf("el id padre de p1 es (PID: %d) \n", getppid());
    *suma = *suma + getpid() + getppid();
    // Crear proceso P2
    pid2 = fork();
    if (pid2 == 0) {
        *suma = *suma + getpid() + getppid();
            printf("el id de p2 es (PID: %d) \n", getpid());
            printf("el id padre de p2 es (PID: %d) \n", getppid());
    } else if (pid2 < 0) {
        perror("Error al crear proceso P2");
        exit(1);
    } else {     
        pid3 = fork();
        if (pid3 == 0) {
         *suma = *suma + getpid() + getppid();
                printf("el id de P3 es (PID: %d) \n", getpid());
                printf("el id padre de p3 es (PID: %d) \n", getppid());
        } else if (pid3 < 0) {
            perror("Error al crear proceso P3");
            exit(1);
        } else {
        pid4 = fork();
        if (pid4 == 0) {
            	 *suma = *suma + getpid() + getppid();
                printf("el id de P4 es (PID: %d) \n", getpid());
                printf("el id padre de p4 es (PID: %d) \n", getppid());
        } else if (pid4 < 0) {
            perror("Error al crear proceso P3");
            exit(1);
        }else{
            int status;
            waitpid(pid2, &status, 0);
            waitpid(pid3, &status, 0);
            waitpid(pid4, &status, 0);
             printf("la suma  (suma: %d) \n", *suma);
            }
        }
    }

   exit(0);
}
