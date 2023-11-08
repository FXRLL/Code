#include <stdio.h>
#include <stdlib.h>
struct Stack
{
	int data;
	Stack* link;
};
void push(Stack* &top, int number)
{
	struct Stack* temp = (Stack*)malloc(sizeof(struct Stack));
	temp->data = number;
	temp->link = top;
	top = temp;
}
int pop(Stack* &top)
{
	int n = top->data;
	struct Stack* temp = top;
	top = top->link;
	free(temp);
	return n;
}
int main()
{
    struct Stack* top = NULL;
    int decimalNumber, base;
    printf("enter a decimal number: \n");
    scanf("%d", &decimalNumber);
    printf("enter a number(ex: 2 (01011)): \n");
    scanf("%d", &base);
    if (base > 36 || base == 1)
    {
        printf("error ");
        system("pause");
        return 0;
    }
    while (decimalNumber > 0)
    {
        int remainder = decimalNumber % base;
        push(top, remainder);
        decimalNumber /= base;
    }
    printf("the decimal number change to: %d",base);
    while (top != NULL)
    {
        int digit = pop(top);
        if (digit < 10)
        {
            printf("%d", digit);
        }
        else
        {
            printf("%c", 'A' + (digit - 10));
        }
    }
    printf("\n");
    return 0;
}