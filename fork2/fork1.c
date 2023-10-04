    pid1 = getpid();
    if ((getpid() % 2) == 0) {
        printf("el id de p1 es (PID: %d) \n", getpid());
        printf("el id padre de p1 es (PID: %d) \n", getppid());
    } else {
        printf("el id de p1 es (PID: %d) \n", getpid());
    }

    // Crear proceso P2
    pid2 = fork();
    if (pid2 == 0) {
        // Proceso P2
        if ((getpid() % 2) == 0) {
            printf("el id de p2 es (PID: %d) \n", getpid());
            printf("el id padre de p2 es (PID: %d) \n", getppid());
        } else {
            printf("el id de p2 es (PID: %d) \n", getpid());
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
                printf("el id de P3 es (PID: %d) \n", getpid());
                printf("el id padre de p3 es (PID: %d) \n", getppid());
            } else {
                printf("el ide de p3 es (PID: %d) \n", getpid());
            }
            pid4 = fork();
            if (pid4 == 0) {
                if ((getpid() % 2) == 0) {
                    printf("el id de p4 es (PID: %d) \n", getpid());
                    printf("el id padre  de p4 es (PID: %d) \n", getppid());
                } else {
                    printf("el id de p4 es (PID: %d) \n", getpid());
                }
            } else if (pid4 < 0) {
                perror("Error al crear proceso P4");
                exit(1);
            } else {
            int status2;
                  waitpid(pid4, &status2, 0);
            }
        } else if (pid3 < 0) {
            perror("Error al crear proceso P3");
            exit(1);
        } else {
            // Proceso P1 (padre)
            // Esperar a que P2 y P3 terminen
            int status;
            waitpid(pid2, &status, 0);
            waitpid(pid3, &status, 0);     
            printf("esperado a que P2 y P3 terminen\n");
        }
    }

    exit(0);
}
