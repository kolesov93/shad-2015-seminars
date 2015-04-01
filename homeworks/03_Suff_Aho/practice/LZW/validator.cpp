#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main() {
    registerValidation();

    inf.readToken("[a-z]{2,300000}");
    inf.readEoln();
    inf.readEof();

    return 0;
}

