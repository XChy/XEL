#include <XEL/XELEngine.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
	XELEngine engine;
	while (true) {
		string str;
		cin >> str;
		engine.setExpression(XString::fromStdString(str));
		cout << engine.evaluate().toString().toStdString() << endl;
	}
	return 0;
}