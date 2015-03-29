#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
#include "suggester.h"

struct Heap_Element
{
    size_t bound_left, bound_right;
    Word maximum;

    bool operator ()(const Heap_Element &a, const Heap_Element &b)
    {
        return a.maximum.freq < b.maximum.freq;
    }
};

bool operator<(const Word &a, const Word &b)
{
    return a.text < b.text;
}

bool cmp_bin_lower(const Word &element, const Word &key)
{
    if (element.text.size() < key.text.size())
    {
        return element.text < key.text;
    }

    return strncmp(element.text.c_str(), key.text.c_str(), key.text.size()) < 0;
}

bool cmp_bin_upper(const Word &key, const Word &element)
{
    if (element.text.size() < key.text.size())
    {
        return key.text < element.text;
    }

    return strncmp(element.text.c_str(), key.text.c_str(), key.text.size()) > 0;
}

void Suggester::print_voc(std::vector<Word>::iterator start,
                          std::vector<Word>::iterator end)const
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

std::vector<Word> Suggester::find_k_maximum(size_t left, size_t right, int k)
{
    std::vector<Word> answer;
    k = std::min(k, (int) (right - left + 1));

    if (k < 1)
        return answer;

    answer.reserve(k);
    std::priority_queue<Heap_Element, std::vector<Heap_Element>, Heap_Element> segment_heap;
    segment_heap.push({left, right, segment_tree.count_RMQ(left, right)});

    for (int i = 0; i < k; ++i)
    {
        Heap_Element current_node = segment_heap.top();
        segment_heap.pop();

        answer.push_back(current_node.maximum);

        Word sub_left = segment_tree.count_RMQ(current_node.bound_left,
                                               current_node.maximum.index - 1);

        Word sub_right = segment_tree.count_RMQ(current_node.maximum.index + 1,
                                                current_node.bound_right);

        Heap_Element push_node;

        if (sub_left.freq != -1)
        {
            push_node = {current_node.bound_left,
                         current_node.maximum.index - 1,
                         sub_left};

            segment_heap.push(push_node);
        }

        if (sub_right.freq != -1)
        {
            push_node = {current_node.maximum.index + 1,
                         current_node.bound_right,
                         sub_right};

            segment_heap.push(push_node);
        }
    }

    return answer;
}

std::vector<Word> Suggester::make_suggest(std::string prefix, int suggest_number)
{
    Word to_search = {prefix, 0, 0};

    auto start = std::lower_bound(vocabulary.begin(),vocabulary.end(),
                                  to_search, cmp_bin_lower);

    auto end = std::upper_bound(vocabulary.begin(), vocabulary.end(),
                                to_search, cmp_bin_upper);

    print_voc(start, end);

    return find_k_maximum(start - vocabulary.begin(),
                          end - vocabulary.begin() - 1,
                          suggest_number);
}
