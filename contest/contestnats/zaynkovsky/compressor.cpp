#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void bwt(const std::string& from, std::string& to, size_t& index)
{
    std::vector<size_t> count(256);
    std::vector<size_t> suffix_array(from.length());
    std::vector<size_t> shifted(from.length());
    std::vector<size_t> old_classes(from.length());
    std::vector<size_t> new_classes(from.length());
    for (size_t i = 0; i < from.length(); ++i)
        ++count[from[i]];
    for (size_t i = 1; i < count.size(); ++i)
        count[i] += count[i - 1];
    for (size_t i = from.length(); i --> 0;)
        suffix_array[--count[from[i]]] = i;
    size_t c = 0;
    for (size_t i = 1; i < suffix_array.size(); ++i)
    {
        if (from[suffix_array[i]] != from[suffix_array[i - 1]])
            ++c;
        new_classes[suffix_array[i]] = c;
    }
    for (size_t block = 1; block < from.length(); block <<= 1)
    {
        count.assign(c + 1, 0);
        old_classes.swap(new_classes);
        for (size_t i = 0; i < from.length(); ++i)
            shifted[i] = (suffix_array[i] - block + from.length()) % from.length();
        for (size_t i = 0; i < shifted.size(); ++i)
            ++count[old_classes[shifted[i]]];
        for (size_t i = 1; i < count.size(); ++i)
            count[i] += count[i - 1];
        for (size_t i = shifted.size(); i --> 0;)
            suffix_array[--count[old_classes[shifted[i]]]] = shifted[i];
        c = 0;
        for (size_t i = 1; i < suffix_array.size(); ++i)
        {
            if (old_classes[suffix_array[i]] != old_classes[suffix_array[i - 1]] ||
                old_classes[(suffix_array[i] + block) % from.length()] != old_classes[(suffix_array[i - 1] + block) % from.length()])
                ++c;
            new_classes[suffix_array[i]] = c;
        }
    }
    to.resize(from.length());
    for (size_t i = 0; i < suffix_array.size(); ++i)
    {
        if (suffix_array[i] == 0)
            index = i;
        to[i] = from[(suffix_array[i] + from.length() - 1) % from.length()];
    }
}

std::string rle(const std::string& from)
{
    std::ostringstream stream;
    size_t start = 0, end;
    while (start < from.length())
    {
        end = from.find_first_not_of(from[start], start);
        if (end > from.length())
            end = from.length();
        if (end - start > 1)
        {
            stream << end - start;
        }
        stream << from[start];
        start = end;
    }
    return stream.str();
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

void huffman(const std::string& from, std::string& to, size_t& discard)
{
    std::vector<size_t> temp(256);
    for (char character : from)
        ++temp[character];
    std::vector<node> nodes;
    std::vector<size_t> heap;
    size_t unique_characters = 0;
    for (size_t c = 0; c < temp.size(); ++c)
        if (temp[c] > 0)
        {
            ++unique_characters;
            heap.push_back(nodes.size());
            nodes.emplace_back(temp[c], -1, -1, c);
        }
    auto comp = [&nodes] (size_t i, size_t j)
    {
        return nodes[i].frequency > nodes[j].frequency;
    };
    std::make_heap(heap.begin(), heap.end(), comp);
    while (heap.size() > 1)
    {
        std::pop_heap(heap.begin(), heap.end(), comp);
        size_t i = heap.back();
        heap.pop_back();
        std::pop_heap(heap.begin(), heap.end(), comp);
        size_t j = heap.back();
        heap.pop_back();
        heap.push_back(nodes.size());
        nodes.emplace_back(nodes[i].frequency + nodes[j].frequency, i, j, 0);
        std::push_heap(heap.begin(), heap.end(), comp);
    }
    for (size_t i = nodes.size(); i --> 0; )
        if (nodes[i].character == 0)
        {
            nodes[nodes[i].left].code = nodes[i].code << 1;
            nodes[nodes[i].left].code_length = nodes[i].code_length + 1;
            nodes[nodes[i].right].code = (nodes[i].code << 1) + 1;
            nodes[nodes[i].right].code_length = nodes[i].code_length + 1;
        }
    std::vector<bool> to_bool;
    std::function<void(size_t)> write_tree = [&write_tree, &nodes, &temp, &to_bool] (size_t i)
    {
        if (nodes[i].character == 0)
        {
            to_bool.push_back(false);
            write_tree(nodes[i].left);
            write_tree(nodes[i].right);
        }
        else
        {
            temp[nodes[i].character] = i;
            to_bool.push_back(true);
            for (size_t j = 0; j < 8; ++j)
                to_bool.push_back((1 << j) & nodes[i].character);
        }
    };
    write_tree(nodes.size() - 1);
    for (char character : from)
        for (size_t i = nodes[temp[character]].code_length; i --> 0; )
            to_bool.push_back((1 << i) & nodes[temp[character]].code);
    to.resize((to_bool.size() >> 3) + ((to_bool.size() & 7) > 0));
    for (size_t i = 0; i < (to_bool.size() >> 3); ++i)
        for (size_t j = 0; j < 8; ++j)
            to[i] |= (to_bool[(i << 3) + j] << j);
    for (size_t j = 0; j < (to_bool.size() & 7); ++j)
        to.back() |= (to_bool[((to_bool.size() >> 3) << 3) + j] << j);
    discard = 8 - (to_bool.size() & 7);
    if (discard == 8)
        discard = 0;
}

std::string compress(const std::string& from)
{
    std::string temp;
    size_t index;
    bwt(from, temp, index);
    temp = rle(temp);
    std::ostringstream stream;
    stream << index << ' ' << temp;
    temp.clear();
    huffman(stream.str(), temp, index);
    stream.str("");
    stream.clear();
    stream << index << ' ' << temp;
    return stream.str();
}

int main()
{
    std::stringstream stream;
    std::string original;
    stream << std::cin.rdbuf();
    std::cout << compress(stream.str());
    return 0;
}