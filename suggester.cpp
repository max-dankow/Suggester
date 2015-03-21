#include <algorithm>
#include <iostream>
#include "suggester.h"

bool operator <(const Word &a, const Word &b)
{
    return a.text < b.text;
}

void Suggester::print_voc(std::vector<Word>::iterator start, std::vector<Word>::iterator end)const
{
    for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
    {
        if (it >= start && it < end)
        {
            std::cout << "->    ";
        }

        std::cout << (*it).text << ' ' << (*it).freq << '\n';
    }

    std::cout << '\n';
}


Suggester::Suggester(const std::vector<Word> &input_vocabulary)
{
    vocabulary = input_vocabulary;
    std::sort(vocabulary.begin(), vocabulary.end());

    for (size_t i = 0; i < vocabulary.size(); ++i)
    {
        vocabulary[i].index = i;
    }

    Voc_Max voc_max;
    Word neutral = {"", -1, 0};
    segment_tree.init_tree(vocabulary, voc_max, neutral);
}

void Suggester::find_k_maximum(size_t left, size_t right, int k)
{
    //element of heap with comparator
    struct Node
    {
        size_t bound_left, bound_right;
        Word maximum;
        bool operator ()(const Node &a, const Node &b)
        {
            return a.maximum.freq < b.maximum.freq;
        }
    } comparator;

    if (k < 1)
        return;

    std::vector<Node> segment_heap(1);
    //Node init_node = {}
    segment_heap[0] = {left, right, segment_tree.count_RMQ(left, right)};
    //segment_heap[0].bound_right = right;
    //segment_heap[0].maximum = segment_tree.count_RMQ(left, right);
    std::push_heap(segment_heap.begin(), segment_heap.end(), comparator);

    for (int i = 0; i < k; ++i)
    {
        Node current_node = segment_heap.front();
        std::push_heap(segment_heap.begin(), segment_heap.end(), comparator);
        segment_heap.pop_back();
    }
}

void Suggester::make_suggest(std::string prefix, int suggest_number)
{
    Word to_search = {prefix, 0, 0};

    CMP_Lower cmp_lower;
    std::vector<Word>::iterator start = std::lower_bound(vocabulary.begin(),
                                                   vocabulary.end(), to_search, cmp_lower);
    CMP_Upper cmp_upper;
    std::vector<Word>::iterator end = std::upper_bound(vocabulary.begin(),
                                                   vocabulary.end(), to_search, cmp_upper);
    std::vector<Word> range(start, end);

    print_voc(start, end);
    find_k_maximum(start - vocabulary.begin(), end - vocabulary.begin() - 1, suggest_number);

    //Word max = segment_tree.count_RMQ(0, range.size() - 1);
    //std::cout << max.first << ' ' << max.second << '\n';
}
