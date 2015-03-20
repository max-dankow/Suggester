#include <vector>
#include <algorithm>
#include <assert.h>

template <typename Value, typename Functor>
class RMQ
{
public:
    RMQ(std::vector<Value> input_data, const Functor &new_function, Value new_default_value);
    Value count_RMQ(size_t seek_left, size_t seek_right);
private:
    size_t get_parent(const size_t index) const;
    size_t get_son_left(const size_t index) const;
    size_t get_son_right(const size_t index) const;
    void build(const std::vector<Value> &input_data);
    Value count_RMQ(size_t index, size_t seek_left, size_t seek_right,
                       size_t bound_left, size_t bound_right);

    std::vector<Value> data;
    Functor function;
    Value default_value;
    size_t list_number;
    size_t real_number;
};

template <typename Value, typename Functor>
size_t RMQ<Value, Functor>::get_parent(const size_t index) const
{
    return index / 2;
}

template <typename Value, typename Functor>
size_t RMQ<Value, Functor>::get_son_left(const size_t index) const
{
    return index * 2;
}

template <typename Value, typename Functor>
size_t RMQ<Value, Functor>::get_son_right(const size_t index) const
{
    return (index * 2) + 1;
}

template <typename Value, typename Functor>
void RMQ<Value, Functor>::build(const std::vector<Value> &input_data)
{
    list_number = 1 << ((int) (log2(input_data.size() - 1)) + 1);
    data.resize(list_number * 2);

    for (int i = list_number; i < list_number + input_data.size(); ++i)
    {
        data[i] = input_data[i - list_number];
    }

    for (int i = list_number - 1; i > 0; --i)
    {
        data[i] = function(data[get_son_left(i)], data[get_son_right(i)]);
    }

}

template <typename Value, typename Functor>
RMQ<Value, Functor>::RMQ(std::vector<Value> input_data, const Functor &new_function,
                                   Value new_default_value)
{
    function = new_function;
    default_value = new_default_value;
    real_number = input_data.size();
    build(input_data);
}

template <typename Value, typename Functor>
Value RMQ<Value, Functor>::count_RMQ(size_t index, size_t seek_left, size_t seek_right,
                                     size_t bound_left, size_t bound_right)
{
    if (seek_left > seek_right)
    {
        return default_value;
    }

    if (bound_left == seek_left && bound_right == seek_right)
    {
        return data[index];
    }

    size_t middle = (bound_left + bound_right) / 2;

    return function(count_RMQ(get_son_left(index), seek_left, std::min(middle, seek_right),
                              bound_left, middle),

                    count_RMQ(get_son_right(index), std::max(seek_left, middle + 1), seek_right,
                              middle + 1, bound_right));
}

template <typename Value, typename Functor>
Value RMQ<Value, Functor>::count_RMQ(size_t seek_left, size_t seek_right)
{
    if (seek_right >= real_number)
    {
        return default_value;
    }

    return count_RMQ(1, seek_left, seek_right, 0, list_number - 1);
}
