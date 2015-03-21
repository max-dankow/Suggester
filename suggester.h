#include <vector>
#include <string>

typedef std::pair<std::string, long long> Word;

class Suggester
{
public:
    Suggester(const std::vector<Word> &input_vocabulary);
    void make_suggest(std::string prefix, int suggest_number);
    void print_voc(std::vector<Word>::iterator start, std::vector<Word>::iterator end)const;
private:
    std::vector<Word> vocabulary;
};
