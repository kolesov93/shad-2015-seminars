#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <queue>
#include <memory>
#include <bitset>


using namespace std;

namespace compression {
    const char eof = '\0';
    string alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ()':,.!?'\"";
    list<char> mtfList(alphabet.begin(), alphabet.end());

    vector<int> encodeMtF(const string &str, list<char> mtfList) {
        vector<int> mtf;

        for (int i = 0; i < str.length(); i++) {
            long position = 0;
            for (auto it = mtfList.begin(); it != mtfList.end(); it++, position++) {
                if (*it == str[i]) {
                    mtf.push_back(position);
                    mtfList.push_front(*it);
                    mtfList.erase(it);
                    break;
                }
            }
        }

        return mtf;
    }

    vector<size_t> buildSuffixArray(const string &str) {
        vector<size_t> suffix_array(str.length());

        for (size_t i = 0; i < suffix_array.size(); i++) {
            suffix_array[i] = i;
        }

        sort(suffix_array.begin(), suffix_array.end(), [&](size_t position1, size_t position2) {
            return str.compare(position1, str.length() - position1, str, position2, str.length() - position2) < 0;
        });

        return suffix_array;
    }

    string BWT(string &str, char eof = '\0') {
        str.append(1, eof);

        vector<size_t> suffix_array = buildSuffixArray(str);
        string bwt = "";

        for (int i = 0; i < suffix_array.size(); i++) {
            if (suffix_array[i] == 0) {
                bwt += string(1, str[str.length() - 1]);
            } else {
                bwt += string(1, str[suffix_array[i] - 1]);
            }
        }

        str.erase(str.length() - 1);
        return bwt;
    }

    class HuffmanCoding {
    public:
        struct Node {
            shared_ptr<Node> zero;
            shared_ptr<Node> one;
            char symbol;
            size_t count;

            Node(char s, size_t c = 0, shared_ptr<Node> zero = nullptr, shared_ptr<Node> one = nullptr) :
                    symbol(s), count(c), zero(zero), one(one) { };
        };

        class CompareNode {
        public:
            bool operator()(const shared_ptr<Node> n1, const shared_ptr<Node> n2) const {
                return n1->count > n2->count;
            }
        };

        vector<uint8_t> &encode() {
            int i = 0;
            uint8_t byte = 0;
            string cur = "";

            for (int v: seq) {
                cur += encoding_map[v];
                enc_s += encoding_map[v];
                if (cur.length() >= 8) {
                    encoded.push_back((uint8_t) (bitset<8>(cur.substr(0, 8)).to_ulong()));
                    cur.erase(0, 8);
                }
            }
            if (cur.length() > 0) {
                cur += "0000000";
                encoded.push_back((uint8_t) (bitset<8>(cur.substr(0, 8)).to_ulong()));
            }
            return encoded;
        }

        HuffmanCoding(vector<int> input, size_t max_value) : seq(input), eof(max_value + 1), size(max_value + 2) {
            seq.push_back(eof);
            make_tree();

            encoding_map.resize(size);
            buildEncodingMap(root, "");


        }

        template<class T>
        void decode(const T &in, vector<int> &result) {
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

        void to_array(vector<uint8_t> &repr) {
            visit(root);

            if (str.length() % 8) {
                str += "0000000";
            }
            for (size_t i = 0; i < str.length() / 8; ++i) {
                repr.push_back((uint8_t) bitset<8>(str.substr(i * 8, i * 8 + 8)).to_ulong());
            }
        }

        HuffmanCoding(string &suffix) : eof(0) {
            root = from_str(suffix);
        }

    private:
        shared_ptr<Node> root;
        vector<string> encoding_map;
        vector<uint8_t> encoded;
        vector<int> seq;
        string enc_s;
        size_t size;
        size_t eof;
        string str;
        const static size_t bit_length = 7;

        void make_tree() {
            vector<size_t> freq(size, 0);
            for (auto s: seq) {
                ++freq[s];
            }

            priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, CompareNode> hqueue;
            for (char i = 0; i < freq.size(); ++i) {
                if (freq[i] != 0) {
                    hqueue.push(shared_ptr<Node>(new Node(i, freq[i])));
                }
            }

            while (hqueue.size() > 1) {
                shared_ptr<Node> n1 = hqueue.top();
                hqueue.pop();
                shared_ptr<Node> n2 = hqueue.top();
                hqueue.pop();
                hqueue.push(shared_ptr<Node>(new Node(-1, n1->count + n2->count, n1, n2)));
            }

            root = hqueue.top();
        }

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

    void encode_file(const string &input_file, const string &output_file) {
        mtfList.push_back(eof);

        ofstream outs(output_file);
        ifstream in(input_file);
        string str;

        getline(in, str);
        string eb = BWT(str, eof);
        vector<int> emb = encodeMtF(eb, mtfList);
        HuffmanCoding hc(emb, alphabet.size());
        vector<uint8_t> ehmb = hc.encode();

        vector<uint8_t> repr;
        hc.to_array(repr);

        outs << (uint8_t) repr.size();

        for (auto i: repr) {
            outs << i;
        }

        for (auto v: ehmb) {
            outs << v;
        }
    }

}


int main(int argc, char *argv[]) {
    string in_file;
    string out_file;
    if (argc == 2) {
        in_file = "input.txt";
        out_file = argv[1];
    } else if (argc == 3) {
        in_file = argv[1];
        out_file = argv[2];
    } else {
        in_file = "input.txt";
        out_file = "compressed.txt";
    }

    compression::encode_file(in_file, out_file);
    return 0;
}