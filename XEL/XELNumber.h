#ifndef XELNUMBER_H
#define XELNUMBER_H

enum NumberType{
    Interger,
    Decimal,
};

union XELNumberHolder{
    long long intergerValue;
    double decimalValue;
};

class XELNumber{
public:
    XELNumber();
    XELNumber(const XELNumber& other);
    XELNumber(int value);
    XELNumber(long long value);
    XELNumber(float value);
    XELNumber(double value);

    XELNumber operator+(const XELNumber& other);
    XELNumber operator-(const XELNumber& other);
    XELNumber operator*(const XELNumber& other);
    XELNumber operator/(const XELNumber& other);

private:
    XELNumberHolder mHolder;
    NumberType mType;
};

#endif
