#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <XEL/xel_global.h>
#include <XEL/XELContext.h>

class XEL_EXPORT Preprocessor
{
public:
	Preprocessor();
	virtual XString process(XString expression);

	XELContext* context() const;
	void setContext(XELContext* context);
private:
	XELContext* mContext;
};

#endif // PREPROCESSOR_H
