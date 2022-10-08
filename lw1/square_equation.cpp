#include <cstdio>
#include <cmath>
int main()
{
    std::puts("please enter a,b and c for 'ax^2 + bx + c= 0':");
    int a = 0;
    int b = 0;
    int c = 0;
    std::scanf("%d %d %d", &a, &b, &c);
    float d = b * b - 4 * a * c;
    if (d > 0)
    {
        float x1 = ((-b) + sqrt(d)) / (2 * a);
        float x2 = ((-b) - sqrt(d)) / (2 * a);
        std::printf("solution: %f %f\n", x1, x2);
    }
    if (d == 0)
    {
        float x = -(b / (2 * a));
        std::printf("solution: %f\n", x);
    }
    if (d < 0)
    {
        std::printf("There are not real roots");
    }
}