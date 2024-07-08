#include <stdio.h>
#include <unistd.h>

void calculateSum(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum = sum + i;
    }
    printf("Sum is : %d\n", sum);
}

void calculateProduct(int n)
{
    int product = 1;
    for (int i = 1; i <= n; i++)
    {
        product = product * i;
    }
    printf("Product is: %d\n", product);
}

int main()
{
    int n;
    printf("Enter a number : ");
    scanf("%d", &n);

    int pid = fork();

    if (pid == 0)
    {
        calculateProduct(n);
    }
    else
    {
        calculateSum(n);
    }

    return 0;
}
