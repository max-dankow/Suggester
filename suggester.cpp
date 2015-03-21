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

std::vector<Word> Suggester::find_k_maximum(size_t left, size_t right, int k)
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

    std::vector<Word> answer;
    k = std::min(k, (int) (right - left + 1));

    if (k < 1)
        return answer;

    answer.reserve(k);
    std::vector<Node> segment_heap(1);
    segment_heap[0] = {left, right, segment_tree.count_RMQ(left, right)};
    std::push_heap(segment_heap.begin(), segment_heap.end(), comparator);

    for (int i = 0; i < k; ++i)
    {
        Node current_node = segment_heap.front();

        std::pop_heap(segment_heap.begin(), segment_heap.end(), comparator);
        segment_heap.pop_back();

        answer.push_back(current_node.maximum);

        Word sub_left = segment_tree.count_RMQ(current_node.bound_left, current_node.maximum.index - 1);
        Word sub_right = segment_tree.count_RMQ(current_node.maximum.index + 1, current_node.bound_right);

        Node push_node;
        if (sub_left.freq != -1)
        {
            push_node = {current_node.bound_left, current_node.maximum.index - 1, sub_left};
            segment_heap.push_back(push_node);
            std::push_heap(segment_heap.begin(), segment_heap.end(), comparator);
        }

        if (sub_right.freq != -1)
        {
            push_node = {current_node.maximum.index + 1, current_node.bound_right, sub_right};
            segment_heap.push_back(push_node);
            std::push_heap(segment_heap.begin(), segment_heap.end(), comparator);
        }
    }

    return answer;
}

std::vector<Word> Suggester::make_suggest(std::string prefix, int suggest_number)
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

    return find_k_maximum(start - vocabulary.begin(), end - vocabulary.begin() - 1, suggest_number);
}
