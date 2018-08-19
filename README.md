# XEL - 一个表达式引擎(A Expression Engine)

## 基本特性
  使用Variant包装值,可支持double,int,bool,Object,null<br/>
  允许用户自定义变量,操作符,函数<br/>
  内置(+ - \* / ^ =)等操作符,(sin,cos,tan)等函数<br/>
  发现表达式非法时,抛出XELError<br/>

## Basic Features
  Value be wrapped with Variant,supports double,int,bool,Object,null<br/>
  Allows users to customize variables, operators, functions<br/>
  Built-in operator(+ - \* / ^ =) functoin(sin cos tan) .etc<br/>
  When it find the expression is NOT right,it will throw XELError<br/>

## 高级特性
  允许自定义XELObject嵌入其中,并通过重写虚函数member,invoke等返回对象成员和调用成员函数<br/>
  比如内置的XVectorObject,XMapObject等
  <br/><br/>
  允许自定义一元和二元操作符,并通过Variant::type()判断类型<br/>
  若是Object则convertObject并通过dynamic_cast判断和转换类型
  允许字符式的二元操作符,比如(and or xor),不过需要与操作数之间有空格
  <br/><br/>
  支持二进制和十六进制数<br/>
  允许自定义Parser和Tokenizer<br/>

## Advanced Features
Allows custom XELObjects to be embedded in them, and returns object members and calls member functions by overwriting virtual functions such as member, invoke, and so on<br/>
Such as built-in XVectorObject, XMapObject, etc.
<br/><br/>
Allows to customize unary and binary operators and determine types by Variant::type ()<br/>
If it's Object ,convertObject and dynamic_cast can be used to determine and transform types<br/>
Allows characters as binary operator, such as (AND OR XOR), but needs to have spaces between operands
<br/><br/>
Supports bin and hex numbers<br/>
Allows custom Parser and Tokenizer<br/>
