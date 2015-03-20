#include <iostream>
#include "rmq.h"
#include <vector>
#include <limits.h>

int main()
{
    std::vector<int> data = {1, 2, 10, 505, 18, 10};

    struct f
    {
        int operator ()(int a, int b)
        {
            return std::max(a, b);
        }
    } my_max;

    RMQ<int, f> tree(data, my_max, INT_MIN);

    for (int i = 1; i < 6; ++i)
       std::cout << tree.count_RMQ(i, 5) << '\n';

    return 0;
}
