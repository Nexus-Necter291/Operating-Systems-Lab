#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void add_sub_result(int num1, int num2, int *result1, int *result2, int pipefd1[])
{
    close(pipefd1[1]);

    read(pipefd1[0], &num1, sizeof(int));
    read(pipefd1[0], &num2, sizeof(int));

    *result1 = num1 + num2;
    printf("Child 1: Addition Result: %d\n", *result1);
    *result2 = num1 - num2;
    printf("Child 1: Subtraction Result: %d\n", *result2);

    close(pipefd1[0]);
    exit(EXIT_SUCCESS);
}

void mul_div_result(int num1, int num2, int *result1, int *result2, int pipefd2[])
{
    close(pipefd2[1]);

    read(pipefd2[0], &num1, sizeof(int));
    read(pipefd2[0], &num2, sizeof(int));

    *result1 = num1 * num2;
    printf("Child 2: Multiplication Result: %d\n", *result1);
    if (num2 != 0)
    {
        *result2 = num1 / num2;
        printf("Child 2: Division Result: %d\n", *result2);
    }
    else
        printf("Child 2: Division by zero!\n");

    close(pipefd2[0]);
    exit(EXIT_SUCCESS);
}

void input1(int num1, int num2, int pipefd1[])
{
    close(pipefd1[0]);
    printf("Enter two numbers for addition and subtraction: ");
    scanf("%d %d", &num1, &num2);

    write(pipefd1[1], &num1, sizeof(int));
    write(pipefd1[1], &num2, sizeof(int));
    close(pipefd1[1]);
}

void input2(int num1, int num2, int pipefd2[])
{
    close(pipefd2[0]);

    printf("Enter two numbers for multiplication and division: ");
    scanf("%d %d", &num1, &num2);

    write(pipefd2[1], &num1, sizeof(int));
    write(pipefd2[1], &num2, sizeof(int));

    close(pipefd2[1]);
}

int main()
{
    int pipefd1[2], pipefd2[2], pid1, pid2, pid3, num1, num2, result1, result2;

    if (pipe(pipefd1) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();

    if (pid1 == 0)
    {
        add_sub_result(num1, num2, &result1, &result2, pipefd1);
    }
    else
    {
        input1(num1, num2, pipefd1);
        wait(NULL);
        puts("");
        pid2 = fork();
        if (pid2 == 0)
            mul_div_result(num1, num2, &result1, &result2, pipefd2);
        else
        {
            input2(num1, num2, pipefd2);
            wait(NULL);
            puts("");
            pid3 = fork();
            if (pid3 == 0)
            {
                read(pipefd1[0], &result1, sizeof(int));
                read(pipefd1[0], &result2, sizeof(int));
                printf("Child 3: Received Addition Result: %d, Subtraction Result: %d\n", result1, result2);

                read(pipefd2[0], &num1, sizeof(int));
                read(pipefd2[0], &num2, sizeof(int));
                printf("Child 3: Received Multiplication Result: %d, Division Result: %d\n", num1, num2);

                exit(EXIT_SUCCESS);
            }
            else
                wait(NULL);
        }
    }
    return 0;
}
