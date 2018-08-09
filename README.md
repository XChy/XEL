# X Expression Language - A language for calculating
For example:
```C++
try{
		XELEngine engine;
		engine.setVariable("a",3.0);
		engine.setExpression("1*2-a");
		Variant value=engine.evaluate();//equals 0
		switch (value.type()) {
			case VariantType::Double:
				qDebug()<<value.toDouble();
				break;
			case VariantType::String:
				qDebug()<<value.toString();
				break;
			case VariantType::Bool:
				qDebug()<<value.toBool();
				break;
		}
	}catch(XELError& error){
		qDebug()<<error.errorString();
	}
```
* Features:

  * Supports setting the variable
  * Supports setting the custom functions
  * Supports setting the custom operators
  * Supports customing the preprocessor/tokenizer/parser
  * Value wrap by Variant (Supports String,Double and Boolean)
* Implementations:
  * Expression->preprocess->Preprocessed Expression->Token Analysis->Token List->Parse->Evaluation Tree->Value
