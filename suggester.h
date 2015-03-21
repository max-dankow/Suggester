#include <vector>
#include <string>
#include "rmq.h"

struct Word
{
    std::string text;
    long long freq;
    size_t index;
};

//lower_bound comparator
struct CMP_Lower
{
    bool operator ()(const Word &element, const Word &key) const
    {
        if (element.text.size() < key.text.size())
        {
            return element.text < key.text;
        }

        std::string el_prefix = std::string(element.text, 0, key.text.size());

        return el_prefix < key.text;
    }
};

//upper_bound comparator
struct CMP_Upper
{
    bool operator ()(const Word &key, const Word &element) const
    {
        if (element.text.size() < key.text.size())
        {
            return key.text < element.text;
        }

        std::string el_prefix = std::string(element.text, 0, key.text.size());

        return key.text < el_prefix;
    }
};

//functor for segment tree
struct Voc_Max
{
    Word operator()(const Word &a, const Word &b)
    {
        if (a.freq > b.freq)
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
