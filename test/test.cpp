#include <XEL/XELEngine.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
	XELEngine engine;
	cin >> std::noskipws;
	string str;
	while (true) {
			try
			{
				getline(cin, str);
				engine.setExpression(XString::fromStdString(str));
				cout << engine.evaluate().toString().toStdString() << endl;
			}
			catch (const XELError& error) {
				cout << error.errorString().toStdString() << endl;
			}
	}
	return 0;
}