#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5;
    int shm_id;
    int *suma;

    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    suma = (int *)shmat(shm_id, NULL, 0);
    *suma = 100;

    // Crear proceso P1
    pid1 = getpid();
    if ((getpid() % 2) == 0) {
        printf("pid1 +10 (suma: %d)\n", *suma);
        *suma = *suma + 10;
    } else {
       
        printf("pid1 -100 (suma: %d)\n", *suma);
        *suma = *suma - 100;
    }

    pid2 = fork();
    if (pid2 == 0) {
        if ((getpid() % 2) == 0) {
            printf("pid2 +10 (suma: %d)\n", *suma);
            *suma = *suma + 10;
        } else {
            *suma = *suma - 100;
            printf("pid2 -100 (suma: %d)\n", *suma);
        }

        pid5 = fork();
        if (pid5 == 0) {
            if ((getpid() % 2) == 0) {
                printf("pid5 +10 (suma: %d)\n", *suma);
                *suma = *suma + 10;
            } else {
                *suma = *suma - 100;
                printf("pid5 -100 (suma: %d)\n", *suma);
            }
        } else if (pid5 < 0) {
            perror("Error al crear proceso P5");
            exit(1);
        } else {
            int status5;
            waitpid(pid5, &status5, 0);
        }
    } else if (pid2 < 0) {
        perror("Error al crear proceso P2");
        exit(1);
    } else {
        // Proceso P1 (padre)
        // Crear proceso P3
        pid3 = fork();
        if (pid3 == 0) {
            if ((getpid() % 2) == 0) {
                printf("pid3 +10 (suma: %d)\n", *suma);
                *suma = *suma + 10;
            } else {
                *suma = *suma - 100;
                printf("pid3 -100 (suma: %d)\n", *suma);
            }

            pid4 = fork();
            if (pid4 == 0) {
                if ((getpid() % 2) == 0) {
                    printf("pid4 +10 (suma: %d)\n", *suma);
                    *suma = *suma + 10;
                } else {
                    *suma = *suma - 100;
                    printf("pid4 -100 (suma: %d)\n", *suma);
                }
            } else if (pid4 < 0) {
                perror("Error al crear proceso P4");
                exit(1);
            } else {
                int status4;
                waitpid(pid4, &status4, 0);
            }
        } else if (pid3 < 0) {
            perror("Error al crear proceso P3");
            exit(1);
        } else {
            // Proceso P1 (padre)
            int status2, status3;
            waitpid(pid2, &status2, 0);
            waitpid(pid3, &status3, 0);
            printf("(suma: %d)\n", *suma);
        }
    }

    exit(0);
