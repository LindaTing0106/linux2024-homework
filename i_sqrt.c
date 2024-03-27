#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
int i_sqrt(int x)
{
    if (x <= 1) /* Assume x is always positive */
        return x;

    int msb = 0;
    for (int temp = x; temp; ){
        int var = ffs(temp);
        msb += var;
        temp >>= var;
    }

    int z = 0;
    for (int m = 1UL << ((msb - 1) & ~1UL); m; m >>= 2) {
        int b = z + m;
        z >>= 1;
        int mask = -(x >= b);
        x -= mask & b;
        z += mask & m;
    }
    return z;
}

int main()
{
    int N = 49;
    printf("%d\n", i_sqrt(N));
    return 0;
}
