#include "Preprocessor.h"

Preprocessor::Preprocessor()
{

}

XString Preprocessor::process(XString expression)
{
	bool isInQuotes=false;
	XString result;
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
	return result;
}

XELContext* Preprocessor::context() const
{
	return mContext;
}

void Preprocessor::setContext(XELContext* context)
{
	mContext = context;
}
