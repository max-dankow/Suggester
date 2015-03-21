#include <algorithm>
#include <iostream>
#include "rmq.h"
#include "suggester.h"

struct CMP_Lower
{
    bool operator ()(const Word &element, const Word &key) const
    {
        if (element.first.size() < key.first.size())
        {
            return element.first < key.first;
        }

        std::string el_prefix = std::string(element.first, 0, key.first.size());

        return el_prefix < key.first;
    }
};

struct CMP_Upper
{
    bool operator ()(const Word &key, const Word &element) const
    {
        if (element.first.size() < key.first.size())
        {
            return key.first < element.first;
        }

        std::string el_prefix = std::string(element.first, 0, key.first.size());

        return key.first < el_prefix;
    }
};

struct Voc_Max
{
    Word operator()(const Word &a, const Word &b)
    {
        if (a.second > b.second)
            return a;
        else
            return b;
    }
};

void Suggester::print_voc(std::vector<Word>::iterator start, std::vector<Word>::iterator end)const
{
    for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
    {
        if (it >= start && it < end)
        {
            std::cout << "->    ";
        }

        std::cout << (*it).first << ' ' << (*it).second << '\n';
    }

    std::cout << '\n';
}


Suggester::Suggester(const std::vector<Word> &input_vocabulary)
{
    vocabulary = input_vocabulary;
    std::sort(vocabulary.begin(), vocabulary.end());
}

void Suggester::make_suggest(std::string prefix, int suggest_number)
{
    //String_Comparator cmp;

    Word search = {prefix, 0};
    //Word search2 = {"aab", 0};
    //assert(search < search2);
    CMP_Lower cmp_lower;
    //assert(my_cmp(search, search));

    std::vector<Word>::iterator start = std::lower_bound(vocabulary.begin(),
                                                   vocabulary.end(), search, cmp_lower);
    CMP_Upper cmp_upper;
    std::vector<Word>::iterator end = std::upper_bound(vocabulary.begin(),
                                                   vocabulary.end(), search, cmp_upper);
    print_voc(start, end);
    std::cout << start - vocabulary.begin() << '\n';

    Voc_Max voc_max;
    Word neutral = {"", -1};
    std::vector<Word> range(start, end);

    RMQ<Word, Voc_Max> tree(range, voc_max, neutral);
    Word max = tree.count_RMQ(0, range.size() - 1);
    std::cout << max.first << ' ' << max.second << '\n';


}
