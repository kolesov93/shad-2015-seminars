#include "testlib.h"
#include <sstream>
#include <vector>

using namespace std;

vector<int> kmp(const vector<int>& a) {
    int n = a.size();
    vector<int> result(n);
    for (int i = 1; i < n; ++i) {
        int& k = result[i] = result[i - 1];
        while (k && a[k] != a[i]) {
            k = result[k - 1];
        }
        if (a[k] == a[i]) ++k;
    }
    return result;
}

int main(int argc, char * argv[])
{
    setName("Checking inverse-kmp problem");

    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> pi(n);
    for (int i = 0; i < n; ++i) {
        pi[i] = inf.readInt();
    }

    vector<int> judgeAnswer;
    vector<int> participantAnswer;
    while (!ans.seekEof()) {
        judgeAnswer.push_back(ans.readInt());
    }
    while (!ouf.seekEof()) {
        participantAnswer.push_back(ouf.readInt());
        if (participantAnswer.back() > n) {
            quitf(_pe, "Participant array contains element greater than %d", n);
        }
    }

    if (judgeAnswer.size() != 1 && int(judgeAnswer.size()) != n) {
        quitf(_fail, "Judge answer doesn't contain \"-1\" or %d elements as expected", n);
    }
    if (participantAnswer.size() != 1 && int(participantAnswer.size()) != n) {
        quitf(_wa, "Participant answer doesn't contain \"-1\" or %d elements as expected", n);
    }

    bool judgeNoAnswer = (judgeAnswer.size() == 1 && judgeAnswer[0] == -1);
    bool participantNoAnswer = (participantAnswer.size() == 1 && participantAnswer[0] == -1);

    if (judgeNoAnswer && participantNoAnswer) {
        quitf(_ok, "Ok. Such string doesn't exist");
    }
    if (judgeNoAnswer) {
        if (kmp(participantAnswer) == pi) {
            quitf(_fail, "Participant has found solution, while jury thinks there is no one");
        }
        quitf(_wa, "Participant thinks that she found solution, but there is no one");
    }
    if (kmp(judgeAnswer) != pi) {
        quitf(_fail, "Jury thinks that it found solution, but it's wrong");
    }

    if (participantNoAnswer) {
        quitf(_wa, "Participant thinks there is no such string, but there is");
    }
    if (kmp(participantAnswer) != pi) {
        quitf(_wa, "Participant found solution that doesn't match given failure table");
    }
    quitf(_ok, "Ok. Solution found");
}
