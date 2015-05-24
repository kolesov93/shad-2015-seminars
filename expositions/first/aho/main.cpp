#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

class IAhoKorasikSolver {
public:
    virtual int solve(const string& text, const vector<string>& patterns) = 0;
};

class NaiveSolver : public IAhoKorasikSolver {
public:
    virtual int solve(const string& s, const vector<string>& patterns) override {
        int result = 0;
        for (auto&& pattern : patterns) {
            for (int i = 0; i + pattern.size() <= s.size(); ++i) {
                if (s.substr(i, pattern.size()) == pattern) {
                    result += 1;
                }
            }
        }
        return result;
    }
};

class StupidSolver : public IAhoKorasikSolver {
public:
    virtual int solve(const string& s, const vector<string>& patterns) override {
        int result = 1;
        for (auto&& pattern : patterns) {
            for (int i = 0; i + pattern.size() <= s.size(); ++i) {
                if (s.substr(i, pattern.size()) == pattern) {
                    result += 1;
                }
            }
        }
        return result;
    }
};

bool check(IAhoKorasikSolver* solver, const string& s, const vector<string>& patterns) {
    NaiveSolver naiveSolver;
    int got = solver->solve(s, patterns);
    int expected = naiveSolver.solve(s, patterns);
    if (got != expected) {
        cerr << "Got error!" << endl;
        cerr << "Text: '" << s << "'" << endl;
        for (auto&& pattern : patterns) {
            cerr << "\tPattern: " << pattern << endl;
        }
        cerr << "Got result " << got << ", but real result = " << expected << endl;
    } else {
        cerr << "Test passed: result " << got << endl;
    }
    return solver->solve(s, patterns) == naiveSolver.solve(s, patterns);
}

int main() {
    srand(time(0));

    StupidSolver solver;
    check(&solver, "abacaba", vector<string>{"aba", "c", "d"});

    return 0;
}

