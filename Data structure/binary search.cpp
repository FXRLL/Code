#include <stdio.h>

int search_recursion(int num[], int low, int high, int target)
{
    int mid;
    if (low > high)
    {
        printf("Number not found\n");
        return -1;
    }
    mid = (low + high) / 2;
    if (num[mid] == target)
        return mid;
    else if (num[mid] < target)
        return search_recursion(num, mid + 1, high, target); // Right half
    else
        return search_recursion(num, low, mid - 1, target); // Left half
}

int search_non_recursion(int num[], int low, int high, int target)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (num[mid] == target)
            return mid;
        else if (num[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main()
{
    printf("Enter the size of the array\n");
    int n;
    scanf("%d", &n);
    int num[n];
    printf("Enter the array in ascending order\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    int target;
    printf("Enter the search number\n");
    scanf("%d", &target);
    printf("Recursive search result: %d\n", search_recursion(num, 0, n - 1, target)+1);
    printf("Non-recursive search result: %d\n", search_non_recursion(num, 0, n - 1, target)+1);
    return 0;
}
