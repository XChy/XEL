#ifndef XELERROR_H
#define XELERROR_H

#include <XEL/xel_global.h>
#include <XEL/XString.h>

class XEL_EXPORT XELError
{
   public:
    XELError(XString errorString);
    XString errorString() const;

    void setErrorString(const XString& errorString);

   private:
    XString _errorString;
};

#endif  // FORMULAERROR_H
