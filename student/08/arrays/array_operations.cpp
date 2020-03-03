#include "array_operations.hh"
#include <algorithm>
#include <bits/stdc++.h>
int greatest_v1(int* itemptr, int size)
{
    auto max = *itemptr;
    for (auto iter = itemptr+1;iter - itemptr < size; iter++)
    {
        if (max < *iter)
            max = *iter;
    }
    return max;
}
int greatest_v2(int* itemptr, int* endptr)
{
    auto max = *itemptr;
    for (auto iter = itemptr+1; iter != endptr; iter++)
    {
        if (max < *iter)
            max = *iter;
    }
    return max;
}
void copy(int* itemptr, int* endptr, int* targetptr)
{
    for ( auto iter = itemptr; itemptr != endptr; iter++)
{
    *targetptr = *itemptr;
    targetptr++;

}
}
void reverse(int* leftptr, int* rightptr)
{
    int d = rightptr - leftptr;
    for (auto i = 0; i <= int(d/2) ; i++ )
    {
        auto temp = *(leftptr+i);
        *(leftptr+i)= *(rightptr-i);
        *(rightptr-i) = temp;
    }
}
