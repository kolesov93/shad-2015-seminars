#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void bwt_inverse(const std::string& from, std::string& to, size_t index)
{
    std::vector<std::pair<char, size_t>> temp(from.length());
    for (size_t i = 0; i < from.length(); ++i)
    {
        temp[i].first = from[i];
        temp[i].second = i;
    }
    std::sort(temp.begin(), temp.end());
    to.reserve(from.length());
    while (to.length() < from.length())
    {
        to.push_back(temp[index].first);
        index = temp[index].second;
    }
}

void rle_inverse(const std::string& from, std::string& to)
{
    std::istringstream stream(from);
    stream.unsetf(std::ios_base::skipws);
    size_t frequency;
    char character;
    stream >> frequency;
    if (!stream)
    {
        frequency = 1;
        stream.clear();
    }
    while (true)
    {
        stream >> character;
        to.append(frequency, character);
        stream >> frequency;
        if (stream.eof())
            break;
        else
            if (!stream)
            {
                frequency = 1;
                stream.clear();
            }
    }
}

struct node
{
    node(size_t f, size_t l, size_t r, char c): frequency(f), left(l), right(r), character(c), code(0), code_length(0) {}
    size_t frequency;
    size_t left;
    size_t right;
    char character;
    size_t code;
    size_t code_length;
};

void huffman_inverse(const std::string& from, std::string& to, size_t discard)
{
    std::vector<bool> from_bool;
    from_bool.reserve(from.size() << 3);
    for (char character : from)
        for (size_t i = 0; i < 8; ++i)
            from_bool.push_back(character & (1 << i));
    for (size_t i = 0; i < discard; ++i)
        from_bool.pop_back();
    std::vector<node> nodes;
    size_t position = 0;
    std::function<size_t()> read_tree = [&read_tree, &from_bool, &position, &nodes] ()
    {
        if (from_bool[position++])
        {
            char character = 0;
            for (size_t j = 0; j < 8; ++j, ++position)
                character |= (from_bool[position] << j);
            nodes.emplace_back(0, -1, -1, character);
        }
        else
        {
            size_t left = read_tree();
            size_t right = read_tree();
            nodes.emplace_back(0, left, right, 0);
        }
        return nodes.size() - 1;
    };
    read_tree();
    size_t n;
    while (position < from_bool.size())
    {
        for (n = nodes.size() - 1; nodes[n].character == 0; ++position)
            if (from_bool[position])
                n = nodes[n].right;
            else
                n = nodes[n].left;
        to.push_back(nodes[n].character);
    }
}

void decompress(std::string& from, std::string& to)
{
    std::istringstream stream(from);
    std::stringstream temp_stream;
    size_t index;
    stream >> index;
    stream.ignore();
    temp_stream << stream.rdbuf();
    from = temp_stream.str();
    huffman_inverse(from, to, index);
    stream.str(to);
    stream.clear();
    stream >> index;
    stream.ignore();
    temp_stream.str("");
    temp_stream.clear();
    temp_stream << stream.rdbuf();
    to = temp_stream.str();
    from.clear();
    rle_inverse(to, from);
    to.clear();
    bwt_inverse(from, to, index);
}

int main()
{
    std::stringstream stream;
    std::string compressed, decompressed;
    stream << std::cin.rdbuf();
    compressed = stream.str();
    decompress(compressed, decompressed);
    std::cout << decompressed;
    return 0;
}