#include "testlib.h"
#include <algorithm>
#include <string>
#include <set>
#include <vector>

using std::max;
using std::string;
using std::set;
using std::vector;

int main(int argc, char * argv[]) {
    setName("Checks xo-task solution");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> inputField(n);
    inf.readLine();
    for (int i = 0; i < n; ++i) {
        inputField[i] = inf.readString();
    }

    const string POOR_TAK = "Poor Tak";
    const string HAPPY_TAK = "Happy Tak";
    string userVerdict = ouf.readLine();
    string juryVerdict = ans.readLine();
    quitif(userVerdict != POOR_TAK && userVerdict != HAPPY_TAK, _pe, "Expected verdict '%s' or '%s', but got '%s'", POOR_TAK.c_str(), HAPPY_TAK.c_str(), userVerdict.c_str());
    //quitif(userVerdict != juryVerdict, _wa, "Expected verdict '%s', but got '%s'", juryVerdict.c_str(), userVerdict.c_str());
    if (userVerdict == POOR_TAK) {
        quitif(juryVerdict == POOR_TAK, _ok, "Ok, no solution exists");
        quitif(juryVerdict != POOR_TAK, _wa, "Solution exists, but user says it's not");
    }


    vector<string> userField(n);
    for (int i = 0; i < n; ++i) {
        userField[i] = ouf.readString();
    }

    for (int i = 0; i < n; ++i) {
        const auto& userRow = userField[i];
        const auto& juryRow = inputField[i];

        quitif(int(userRow.size()) != m, _pe, "%dth line size is %d, but must be %d", i + 1, int(userRow.size()), m);
        for (int j = 0; j < m; ++j) {
            if (userRow[j] == '*') {
                quitif(juryRow[j] != '*', _pe, "Cat is found at (%d,%d), but it wasn't here at start", i + 1, j + 1);
            } else if (userRow[j] == 'x' || userRow[j] == 'o') {
                quitif(juryRow[j] != '?' && juryRow[j] != userRow[j], _pe, "Found '%c' in (%d,%d), but it must be '%c'", userRow[j], i + 1, j + 1, juryRow[j]);
            } else {
                quitf(_pe, "Found '%c' in (%d,%d) and it's not allowed character", userRow[j], i + 1, j + 1);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int cntx = 0, cnto = 0;
        for (int j = 0; j < m; ++j)
            if (userField[i][j] == 'x') ++cntx;
            else if (userField[i][j] == 'o') ++cnto;
        quitif(cntx != cnto, _wa, "In %dth row number of 'x' is %d, number of 'o' is %d", i + 1, cntx, cnto);
    }
    for (int j = 0; j < m; ++j) {
        int cntx = 0, cnto = 0;
        for (int i = 0; i < n; ++i)
            if (userField[i][j] == 'x') ++cntx;
            else if (userField[i][j] == 'o') ++cnto;
        quitif(cntx != cnto, _wa, "In %dth columnt number of 'x' is %d, number of 'o' is %d", j + 1, cntx, cnto);
    }

    quitif(juryVerdict == POOR_TAK, _fail, "User found solution, but the jury thinks that is no solution");
    quitf(_ok, "User found the solution");
}

