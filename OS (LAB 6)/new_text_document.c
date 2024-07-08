// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     int pid = fork();
   
//     if (pid == 0)
//     {
//         printf("Child process. PID: %d\n", getpid());
//     }
//     else if (pid > 0)
//     {
//         printf("Parent process. PID: %d, Child PID: %d\n", getpid(), pid);
//     }
//     else
//     {
//         perror("fork");
//         return 1;
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     int pid = fork();
//     if (pid == 0)
//     {
//         // Child process
//         printf("Child process. PID: %d\n", getpid());
//     }
//     else if (pid > 0)
//     {
//         // Parent process
//         printf("Parent process. PID: %d, Child PID: %d\n", getpid(), pid);
//     }
//     else
//     {
//         // Error occurred
//         perror("fork");
//         return 1;
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     while (1)
//     {
//         fork();
//         printf("Forked!\n");
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>

// #define NUM_CHILDREN 3

// int main()
// {
//     for (int i = 0; i < NUM_CHILDREN; ++i)
//     {
//         int pid = fork();
//         if (pid == 0)
//         {
//             // Child process
//             printf("Child %d. PID: %d\n", i + 1, getpid());
//             return 0; // Child process terminates
//         }
//         else if (pid < 0)
//         {
//             // Error occurred
//             perror("fork");
//             return 1;
//         }
//     }
//     // Parent process waits for all children to terminate
//     for (int i = 0; i < NUM_CHILDREN; ++i)
//     {
//         wait(NULL);
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     // Create a child process
//     int pid = fork();
//     if (pid == 0)
//     {
//         // Child process
//         printf("Child process. PID: %d\n", getpid());

//         // Replace the child process with a new program
//         char *args[] = {"ls", "-l", NULL}; // Command and arguments for the new program
//         execvp("ls", args);                // Execute the 'ls' command with arguments

//         // execvp() will only return if an error occurs
//         perror("execvp");
//         return 1;
//     }
//     else if (pid > 0)
//     {
//         // Parent process
//         printf("Parent process. PID: %d, Child PID: %d\n", getpid(), pid);
//     }
//     else
//     {
//         // Error occurred
//         perror("fork");
//         return 1;
//     }
//     return 0;
// }

#include <stdio.h>
#include <unistd.h>

int main()
{
    // Create a child process
    int pid = fork();
    if (pid == 0)
    {
        // Child process
        printf("Child process. PID: %d\n", getpid());

        // Replace the child process with a new program
        char *args[] = {"/bin/ls", "-l", NULL}; // Command and arguments for the new program
        execv("/bin/ls", args);                 // Execute the 'ls' command with arguments

        // execv() will only return if an error occurs
        perror("execv");
        return 1;
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process. PID: %d, Child PID: %d\n", getpid(), pid);
    }
    else
    {
        // Error occurred
        perror("fork");
        return 1;
    }
    return 0;
}
