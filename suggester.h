#include <vector>
#include <string>
#include "rmq.h"

struct Word
{
    std::string text;
    long long freq;
    size_t index;
};

bool operator<(const Word &a, const Word &b);

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
    Suggester(const std::vector<Word> &input_vocabulary):
        segment_tree(input_vocabulary, voc_max, neutral)
    {
        vocabulary = input_vocabulary;
        std::sort(vocabulary.begin(), vocabulary.end());

        for (size_t i = 0; i < vocabulary.size(); ++i)
        {
            vocabulary[i].index = i;
        }

        segment_tree.init_tree(vocabulary, voc_max, neutral);
    }

    std::vector<Word> make_suggest(std::string prefix, int suggest_number);
    void print_voc(std::vector<Word>::iterator start, std::vector<Word>::iterator end)const;

private:
    std::vector<Word> find_k_maximum(size_t left, size_t right, int k);

    Segment_Tree<Word, Voc_Max> segment_tree;
    std::vector<Word> vocabulary;

    Voc_Max voc_max;
    const Word neutral = {"", -1, 0};

};
