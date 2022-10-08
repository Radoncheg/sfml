#include <cstdio>
int main()
{
    std::puts("please enter a and b for 'ax + b = 0':");
    int a = 0;
    int b = 0;
    std::scanf("%d %d", &a, &b);
    float x = -b/a;
    std::printf("solution: %d\n", x);
}