#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <stdio.h>
#include "suggester.h"

void read_data(std::vector<Word> &vocabulary,
               std::string &prefix, int &suggest_number)
{
    freopen("input.txt", "r", stdin);
    size_t voc_number;
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
    std::vector<Word> vocabulary;
    std::string prefix;
    int suggest_number;

    read_data(vocabulary, prefix, suggest_number);
    prefix = "abc";
    Suggester suggester(vocabulary);
    //suggester.print_voc();
    suggester.make_suggest(prefix, suggest_number);
    return 0;
}
