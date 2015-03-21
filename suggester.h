#include <vector>
#include <string>
#include "rmq.h"

typedef std::pair<std::string, long long> Word;

//lower_bound comparator
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

//upper_bound comparator
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

//functor for segment tree
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

class Suggester
{
public:
    Suggester(const std::vector<Word> &input_vocabulary);
    void make_suggest(std::string prefix, int suggest_number);
    void print_voc(std::vector<Word>::iterator start, std::vector<Word>::iterator end)const;
private:
    void find_k_maximum(size_t left, size_t right, int k);

    Segment_Tree<Word, Voc_Max> segment_tree;
    std::vector<Word> vocabulary;
};
