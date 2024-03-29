#include <XEL/XELEngine.h>
#include <functional>
#include <iostream>
#include "XEL/Expression.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    XEL::XELEngine engine;
    string str;
    if (argc < 2) {
        cout << "No argument\n";
        return 0;
    }
    try {
        str = string(argv[1]);
        auto expr = engine.compile(XString::fromStdString(str));
        XEL::Expression expr1 = expr;
        cout << expr.evaluate().toString().toStdString() << endl;
    } catch (const XELError &error) {
        cout << error.errorString().toStdString() << endl;
    }
}
