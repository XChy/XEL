#include "Preprocessor.h"

Preprocessor::Preprocessor()
{

}

QString Preprocessor::process(QString expression)
{
	bool isInQuotes=false;
	QString result;
	for(auto it=expression.begin();it!=expression.end();++it){

		if((*it)=='\"'){
			if(isInQuotes){
				isInQuotes=false;
			}else{
				isInQuotes=true;
			}
		}

		if(it->isSpace()){
			if(!isInQuotes){
				continue;
			}
		}

		result.append(*it);
	}
	return result;
}
