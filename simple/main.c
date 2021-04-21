#include <stdio.h>

#include "array.h"


int main(void)
{
    int vec[5] = {5,2,7,4,8};
    quick_sort(vec, 0, 4);
    
    for(int i = 0; i < 5; ++i) {
		printf("%d\n", vec[i]);
	}
	
    return 0;
}
