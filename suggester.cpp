#include <algorithm>
#include <iostream>
#include "rmq.h"
#include "suggester.h"

/*bool operator <(Word &element, Word &key)
{
    if (element.first.size() < key.first.size())
    {
        return true;
    }

    std::string el_prefix = std::string(element.first, 0, key.first.size());

    return el_prefix < key.first;
    return element.second > key.second;
}*/

struct CMP
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

struct CMP2
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
    CMP my_cmp;
    //assert(my_cmp(search, search));

    std::vector<Word>::iterator start = std::lower_bound(vocabulary.begin(),
                                                   vocabulary.end(), search, my_cmp);
    CMP2 my_cmp2;
    std::vector<Word>::iterator end = std::upper_bound(vocabulary.begin(),
                                                   vocabulary.end(), search, my_cmp2);
    print_voc(start, end);
    std::cout << start - vocabulary.begin() << '\n';


}
