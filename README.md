# XEL - A Expression Engine
### Features

> ## Scalability:
>> ### Variables can be customed

>> ### Functions can be customed
>>> Supports variable number of arguments

>> ### Operators can be customed
>>> Supports unary and binary operator

>> ### Value be wrapped by Variant
>>> Supports Double,Int,String,Bool,Null

>> ### Parser,Tokenizer,Preprocessor can be customed

> ## Usability:
For example:
```c++
#include <XELEngine.h>
XELEngine engine;
engine.setExpression("1+0x666*2/4");
OUTPUT(engine.evaluate().toString().toStdString());//OUTPUT need supports UCS2
```
XEL supports Bin and Hex as number

XEL supports English and Chinese identitier

....

> ## Safety
If expression is not right,XEL will throw XELError