#include "array_operations.hh"
#include <cstddef>
#include <algorithm>

int greatest_v1(int* itemptr, int size)
{
    int max = itemptr[0];
    for(int i = 0; i < size; ++i){
        max = std::max(max, itemptr[i]);
    }
    return max;
}

int greatest_v2(int* itemptr, int* endptr)
{
    int max = *itemptr;
    for(; itemptr < endptr; ++itemptr){
        max = std::max(max, *itemptr);
    }
    return max;
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    for(; itemptr < endptr; ++itemptr, ++targetptr){
        *targetptr = *itemptr;
    }
}

void reverse(int* leftptr, int* rightptr)
{
    --rightptr;

    for(; leftptr < rightptr; ++leftptr, --rightptr){
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
    }
}
