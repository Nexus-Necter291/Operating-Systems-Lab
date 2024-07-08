#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int data, pipe1[2], pipe2[2];

    // Create pipes for communication
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    // Create first child process (C1)
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) { // Child C1
        // Close unused ends of pipes
        close(pipe1[1]);
        close(pipe2[0]);

        int num1, num2, result;

        // Receive data for addition and subtraction from parent
        if (read(pipe1[0], &data, sizeof(int)) == -1) {
            perror("read");
            exit(1);
        }
        printf("Child C1 (PID: %d) received data: %d\n", getpid(), data);

        // Get input for second operation (subtraction) from user
        printf("Enter second number for subtraction: ");
        if (scanf("%d", &num2) != 1) {
            perror("scanf");
            exit(1);
        }

        // Perform addition and subtraction
        num1 = data;
        result = num1 + num2;
        printf("Child C1 (PID: %d): Addition result: %d\n", getpid(), result);
        result = num1 - num2;
        printf("Child C1 (PID: %d): Subtraction result: %d\n", getpid(), result);

        // Send addition result to C3 through pipe2
        if (write(pipe2[1], &result, sizeof(int)) == -1) {
            perror("write");
            exit(1);
        }

        // Exit C1 process
        exit(0);
    }

    // Create second child process (C2)
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) { // Child C2
        // Close unused ends of pipes
        close(pipe1[0]);
        close(pipe2[1]);

        int num1, num2, result;

        // Receive data for multiplication and division from parent
        if (read(pipe2[0], &data, sizeof(int)) == -1) {
            perror("read");
            exit(1);
        }
        printf("Child C2 (PID: %d) received data: %d\n", getpid(), data);

        // Get input for second operation (division) from user
        printf("Enter second number for division: ");
        if (scanf("%d", &num2) != 1) {
            perror("scanf");
            exit(1);
        }

        // Perform multiplication and division (handle division by zero)
        num1 = data;
        if (num2 == 0) {
            printf("Child C2 (PID: %d): Error: Division by zero\n", getpid());
        } else {
            result = num1 * num2;
            printf("Child C2 (PID: %d): Multiplication result: %d\n", getpid(), result);
            result = num1 / num2;
            printf("Child C2 (PID: %d): Division result: %d\n", getpid(), result);
        }

        // Send multiplication result to C3 through pipe2
        if (write(pipe2[1], &result, sizeof(int)) == -1) {
            perror("write");
            exit(1);
        }

        // Exit C2 process
        exit(0);
    }

    // Parent process
    close(pipe1[0]);
    close(pipe2[1]);

    // Get data from user for child C1
    printf("Enter a number for Child C1 (addition and subtraction): ");
    if (scanf("%d", &data) != 1) {
        perror("scanf");
        exit(1);
    }

    // Send data
    // Send data to child C1 through pipe1
    if (write(pipe1[1], &data, sizeof(int)) == -1) {
        perror("write");
        exit(1);
    }

    // Wait for child C1 to finish (before sending data to C2)
    wait(NULL);

    // Get data from user for child C2
    printf("\nEnter a number for Child C2 (multiplication and division): ");
    if (scanf("%d", &data) != 1) {
        perror("scanf");
        exit(1);
    }

    // Send data to child C2 through pipe2
    if (write(pipe2[0], &data, sizeof(int)) == -1) {
        perror("write");
        exit(1);
    }

    // Wait for child C2 to finish
    wait(NULL);

    // Close unused pipes (already closed in children)

    printf("Parent (PID: %d): All child processes completed.\n", getpid());

    return 0;
}
