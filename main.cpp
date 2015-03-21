#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <stdio.h>
#include <cstdlib>
#include "suggester.h"

void read_vocabulary(char *file_name, std::vector<Word> &vocabulary)
{
    //FILE *voc_file = freopen(file_name, "r", stdin);
    std::ifstream voc_file(file_name);

    if (!voc_file)
    {
        std::cerr << "Can't open vocabulary.\n";
        exit(1);
    }

    vocabulary.clear();

    while (1)
    {
        std::string in_word;
        long long in_freq;

        voc_file >> in_word >> in_freq;

        if (voc_file.eof())
        {
            std::cout << "Vocabulary loaded.\n";
            return;
        }

        if (!voc_file.good())
        {
            fprintf(stderr, "Wrong input.\n");
            exit(1);
        }
        Word input = {in_word, in_freq, 0};
        vocabulary.push_back(input);
    }

    //std::cin >> prefix >> suggest_number;
}

int main()
{
    std::vector<Word> vocabulary;
    read_vocabulary("vocabulary.txt", vocabulary);
    Suggester suggester(vocabulary);

    while (1)
    {
        std::string prefix;
        int suggest_number;
        std::cout << "Please, enter a word and number of suggestions:\n";

        std::cin >> prefix >> suggest_number;

        if (std::cin.eof())
        {
            return 1;
        }

        if (!std::cin.good())
        {
            fprintf(stderr, "Wrong input.\n");
            return 1;
        }

        suggester.make_suggest(prefix, suggest_number);

        //vocabulary.push_back(std::make_pair(in_word, in_freq));
    }
    //suggester.print_voc();
    return 0;
}
