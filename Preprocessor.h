#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <formulaengine_global.h>

class FORMULAENGINESHARED_EXPORT Preprocessor
{
public:
	Preprocessor();
	QString process(QString expression);
};

#endif // PREPROCESSOR_H
