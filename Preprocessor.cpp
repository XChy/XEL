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
			isInQuotes=!isInQuotes;
		}else if(it->isSpace()){
			if(!isInQuotes){
				continue;
			}
		}

		result.append(*it);
	}
	qDebug()<<result;
	return result;
}
