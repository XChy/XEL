# XEL - 一个表达式引擎((A Expression Engine))

## 可伸缩性(Scalability)
  #### 允许自定义变量(Variables can be customed)
  #### 允许自定义函数(Functions can be customed)
    支持可变参函数(Supports variable number of arguments)
  #### 允许自定义运算符(Operators can be customed)
    支持单元与双元运算符(Supports unary and binary operator)
  #### 值使用Variant包装(Value be wrapped by Variant)
    支持Double,Int,String,Bool,Null(Supports Double,Int,String,Bool,Null)
  #### 允许自定义语法,词法分析器(Parser,Tokenizer can be customed)

## 易用性(Usability):
  例子(For example):
  ```c++
  #include <XELEngine.h>
  XELEngine engine;
  engine.setExpression("1+0x666*2/4");
  OUTPUT(engine.evaluate().toString().toStdString());
  ```
  XEL支持二进制数和十六进制数(XEL supports Bin and Hex as number)
  
  XEL支持英文和中文的标识符(XEL supports English and Chinese identitier_

  ....

## 安全性(Safety)
如果表达式非法,XEL将会抛出XELError(If expression is not right,XEL will throw XELError)
