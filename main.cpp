#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <stdio.h>
#include "rmq.h"
#include "suggester.h"

struct Function_Max
{
    int operator ()(int a, int b)
    {
        return std::max(a, b);
    }
};

/*struct String_Comparator
{
    int operator <(std::pair<std::string, long long> a, std::pair<std::string, long long> b)
    {
        return strcmp(a, std::string(b, 0, a.));
    }
};*/

void read_data(std::vector<std::pair<std::string, long long> > &vocabulary,
               size_t &voc_number, std::string &prefix, int &suggest_number)
{
    freopen("input.txt", "r", stdin);
    std::cin >> voc_number;
    vocabulary.clear();
    vocabulary.reserve(voc_number);

    for (size_t i = 0; i < voc_number; ++i)
    {
        std::string in_word;
        long long in_freq;
        std::cin >> in_word >> in_freq;
        vocabulary.push_back(std::make_pair(in_word, in_freq));
    }

    std::cin >> prefix >> suggest_number;
}

int main()
{
    size_t voc_number;
    std::vector<std::pair<std::string, long long> > vocabulary;
    std::string prefix;
    int suggest_number;

    read_data(vocabulary, voc_number,prefix, suggest_number);

    std::sort(vocabulary.begin(), vocabulary.end());
    return 0;
}
