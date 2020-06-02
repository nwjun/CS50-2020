#include <stdio.h>

int main(void)
{
    int i = 1, j = 1, divider = 3, sum = i+j;
    float ave;
    
    ave = (float)sum / (float)divider;
    
    if(((int)(ave * 10) % 10) >= 5)
        ++ave;
    
    printf("%d", (int) ave);

}
