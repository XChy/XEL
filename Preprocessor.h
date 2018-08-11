#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <xel_global.h>
#include <XELContext.h>

class XEL_EXPORT Preprocessor
{
public:
	Preprocessor();
	virtual QString process(QString expression);

	XELContext* context() const;
	void setContext(XELContext* context);
private:
	XELContext* mContext;
};

#endif // PREPROCESSOR_H
