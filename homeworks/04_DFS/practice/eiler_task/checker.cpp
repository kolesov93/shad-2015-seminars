#include "testlib.h"
#include <string>
#include <set>

using std::string;
using std::set;

int main(int argc, char * argv[]) {
    setName("Checks if string contains all the k-tuples of n-size alphabet ans have the smallest length");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int k = inf.readInt();

    string answer = ouf.readToken();
    size_t need = 1;
    for (int i = 0; i < k; ++i) need *= n;
    need += k - 1;

    if (answer.size() != need) {
        quitf(_wa, "answer size is %d, but minimal length is %d", int(answer.size()), int(need));
    }
    for (size_t i = 0; i < need; ++i) {
        if (answer[i] < 'a' || answer[i] >= 'a' + n) {
            quitf(_pe, "answer contains character '%c', but must contain only characters between 'a' and '%c'", answer[i], char('a' + n - 1));
        }
    }
    set<int> tokens;
    for (size_t i = 0; i + k <= need; ++i) {
        string token = answer.substr(i, k);
        int tokenValue = 0;
        for (int j = int(k) - 1; j >= 0; --j) {
            tokenValue = tokenValue * n + (token[j] - 'a');
        }
        tokens.insert(tokenValue);
    }

    size_t whole = 1;
    for (int i = 0; i < k; ++i) whole *= n;
    for (size_t i = 0; i < whole; ++i) {
        string cand;
        int tmp = i;
        for (int j = 0; j < k; ++j) {
            cand += char('a' + (tmp % n));
            tmp /= n;
        }
        if (tokens.find(i) == tokens.end()) {
            quitf(_wa, "answer doesn't contain tuple \"%s\"", cand.c_str());
        }
    }

    quitf(_ok, "answer is good");
}
