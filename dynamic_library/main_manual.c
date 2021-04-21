#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "array.h"

int (*func_ptr) (int* s_arr, int first, int last);

int main(void)
{
    // src to lib
    void* handle = dlopen ("/home/null/Desktop/c/dynamic_library/lib/libsort.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    
    // find the function
    func_ptr = dlsym(handle, "quick_sort");
    if (!func_ptr) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }    
    
    int vec[5] = { 5,2,7,4,8 };
    func_ptr(vec, 0, 4);
    
    for(int i = 0; i < 5; ++i) {
		printf("%d\n", vec[i]);
	}
	
    return 0;
}
