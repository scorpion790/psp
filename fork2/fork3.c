#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;

    // Crear proceso P1
    pid1 = getpid();
    printf("Proceso P1 (PID: %d)\n", pid1);

    // Crear proceso P2
    pid2 = fork();
    if (pid2 == 0) {
        // Proceso P2
        pid_t my_pid = getpid();
        printf("Proceso P2 (PID: %d, padre PID: %d)\n", my_pid, getppid());

        // Crear proceso P3
        pid3 = fork();
        if (pid3 == 0) {
            // Proceso P3
            pid_t my_pid = getpid();
            printf("Proceso P3 (PID: %d, padre PID: %d)\n", my_pid, getppid());

            // Crear proceso P5
            pid5 = fork();
            if (pid5 == 0) {
                // Proceso P5
                pid_t my_pid = getpid();
                printf("Proceso P5 (PID: %d, padre PID: %d)\n", my_pid, getppid());
            } else if (pid5 < 0) {
                perror("Error al crear proceso P5");
                exit(1);
            } else {
                int status5;
                waitpid(pid5, &status5, 0);
            }
        } else if (pid3 < 0) {
            perror("Error al crear proceso P3");
            exit(1);
        } else {
            // Proceso P2 (padre)
            // Crear proceso P4
            pid4 = fork();
            if (pid4 == 0) {
                // Proceso P4
                pid_t my_pid = getpid();
                printf("Proceso P4 (PID: %d, padre PID: %d)\n", my_pid, getppid());

                // Crear proceso P6
                pid6 = fork();
                if (pid6 == 0) {
                    // Proceso P6
                    pid_t my_pid = getpid();
                    printf("Proceso P6 (PID: %d, padre PID: %d)\n", my_pid, getppid());
                } else if (pid6 < 0) {
                    perror("Error al crear proceso P6");
                    exit(1);
                } else {
                    int status6;
                    waitpid(pid6, &status6, 0);
                }
            } else if (pid4 < 0) {
                perror("Error al crear proceso P4");
                exit(1);
            } else {
                int status4;
                waitpid(pid4, &status4, 0);
            }
        }

        exit(0);
    } else if (pid2 < 0) {
        perror("Error al crear proceso P2");
        exit(1);
    } else {
        // Proceso P1 (padre)
        int status2;
        waitpid(pid2, &status2, 0);
    }

    return 0;
}
