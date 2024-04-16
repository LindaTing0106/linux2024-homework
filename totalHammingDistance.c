#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

// int totalHammingDistance(int* nums, int numsSize)
// {
//     int total = 0;;
//     for (int i = 0;i < numsSize;i++)
//         for (int j = 0; j < numsSize;j++)
//             total += __builtin_popcount(nums[i] ^ nums[j]); 
//     return total >> 1;
// }

int totalHammingDistance(int* nums, int numsSize) {
    int total = 0;
    int one;
    for (int i = 0;i < 32;i++){
        one = 0;
        for (int j = 0; j < numsSize;j++){
            if(nums[j] & ((uint32_t)1 << i)){
                one++;
            }
        }
        total += one * (numsSize - one);

    }         
    return total;
}

int main()
{
    int nums[4] = {2, 3, 5, 7};

    int total = totalHammingDistance(nums, 4);

    printf("%d\n", total);
}