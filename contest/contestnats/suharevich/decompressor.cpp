#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <queue>
#include <memory>
#include <bitset>
#include <iterator>


using namespace std;

namespace decompression {
    string decodeMtF(const vector<int> &MtFCode, list<char> mtfList) {
        string str = "";

        for (int i = 0; i < MtFCode.size(); i++) {
            int position = 0;
            for (auto it = mtfList.begin(); it != mtfList.end(); it++, position++) {
                if (position == MtFCode[i]) {
                    str += *it;
                    mtfList.push_front(*it);
                    mtfList.erase(it);
                    break;
                }
            }
        }

        return str;
    }

    vector<char> inverseBWT(string& str, int row_num=0) {
        vector< pair<char, int> > permutation(str.length());
        for (int i = 0; i < str.length(); ++i) {
            permutation[i] = pair<char, int>(str[i], i);
        }
        sort(permutation.begin(), permutation.end());
        vector<char> result(str.length());
        for (size_t i = 0; i < str.length(); ++i) {
            result[i] = permutation[row_num].first;
            row_num = permutation[row_num].second;
        }
        return result;

    }

    string to_string(vector<char>& container, size_t start, size_t end) {
        string result;
        for (size_t i = start; i < end; ++i) {
            result.push_back(container[i]);
        }
        return result;
    }

    char eof = '\0';
    string alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ()':,.!?'\"";
    list<char> mtfList(alphabet.begin(), alphabet.end());


    class Huffman {
    public:
        struct Node {
            shared_ptr<Node> zero;
            shared_ptr<Node> one;
            char symbol;
            size_t count;

            Node(char s, size_t c=0, shared_ptr<Node> zero = nullptr, shared_ptr<Node> one = nullptr) :
                    symbol(s), count(c), zero(zero), one(one) { };
        };
        class CompareNode {
        public:
            bool operator() (const shared_ptr<Node> n1, const shared_ptr<Node> n2) const {
                return n1->count > n2->count;
            }
        };

        template<class T>
        void decode(const T& in, vector<int>& result) {
            shared_ptr<Node> cur = root;

            for (uint8_t byte: in) {
                string bits = bitset<8>(byte).to_string();
                for (char c: bits) {
                    if (c == '1') {
                        cur = cur->one;
                    } else {
                        cur = cur->zero;
                    }
                    if (cur->symbol != -1) {
                        result.push_back(cur->symbol);
                        if (cur->symbol == eof) {
                            return;
                        }
                        cur = root;
                    }

                }
            }
        }

        Huffman(string& suffix): eof(0) {
            root = from_str(suffix);
        }

    private:
        shared_ptr<Node> root;
        vector<string> encoding_map;
        size_t eof;
        string str;

        const static size_t bit_length = 7;

        void buildEncodingMap(const shared_ptr<Node> n, string prefix) {
            if (n->symbol != -1) {
                encoding_map[n->symbol] = prefix;
            } else {
                buildEncodingMap(n->one, prefix + '1');
                buildEncodingMap(n->zero, prefix + '0');
            }
        }

        void visit(shared_ptr<Node> node) {
            if (node->symbol == -1) {
                str += '0';
                visit(node->zero);
                visit(node->one);
            } else {
                str += '1';
                str += bitset<bit_length>(node->symbol).to_string();
            }
        }

        shared_ptr<Node> from_str(string &suffix) {

            char s = suffix[0];
            suffix = suffix.substr(1, suffix.length());
            if (s == '1') {
                int value = bitset<bit_length>(suffix.substr(0, bit_length)).to_ulong();
                if (value > eof) {
                    eof = value;
                }
                suffix = suffix.substr(bit_length, suffix.length());
                return shared_ptr<Node>(new Node(value));
            } else {
                shared_ptr<Node> node(new Node(-1));
                node->zero = from_str(suffix);
                node->one = from_str(suffix);

                return node;
            }
        }
    };

    void bytesToStr(vector<uint8_t>& in, string& repr) {
        repr = "";
        for (auto v: in) {
            repr += bitset<8>(v).to_string();
        }
    }

    void decompress(const string& in_file, const string& out_file) {
        mtfList.push_back(eof);

        ofstream output(out_file);

        ifstream input(in_file, ios::binary);
        vector<uint8_t> content((istreambuf_iterator<char>(input)),
                                istreambuf_iterator<char>());

        vector<uint8_t> tree(content[0]);
        for (size_t i = 0; i < content[0]; ++i)  {
            tree[i] = content[i+1];
        }

        string repr;
        bytesToStr(tree, repr);
        Huffman hc(repr);

        content.erase(content.begin(), content.begin() + content[0] + 1);
        vector<int> dh;
        hc.decode(content, dh);

        string dmh = decodeMtF(dh, mtfList);
        vector<char> dbmh = inverseBWT(dmh, eof);

        string decoded = to_string(dbmh, 1, dbmh.size());
        output << decoded << endl;

    }
}

int main(int argc, char *argv[]) {


    string in_file;
    string out_file;

    if (argc == 2) {
        in_file = "decompressed.txt";
        out_file = argv[1];
    } else if (argc == 3) {
        in_file = argv[1];
        out_file = argv[2];
    } else {
        in_file = "decompressed.txt";
        out_file = "output.txt";
    }

    decompression::decompress(in_file, out_file);

    return 0;
}