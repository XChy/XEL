#include <XEL/XELNumber.h>

XELNumber::XELNumber()
{}

XELNumber::XELNumber(const XELNumber& other)
	:mHolder(other.mHolder),
	  mType(other.mType)
{}

XELNumber::XELNumber(int value)
{
	mHolder.intergerValue=value;
	mType=Interger;
}

XELNumber::XELNumber(long long value)
{
	mHolder.intergerValue=value;
	mType=Interger;
}

XELNumber::XELNumber(float value)
{
	mHolder.decimalValue=value;
	mType=Decimal;
}

XELNumber::XELNumber(double value)
{
	mHolder.decimalValue=value;
	mType=Decimal;
}

XELNumber XELNumber::operator+(const XELNumber& other)
{
	if(mType==Decimal){
		if(other.mType==Decimal){
			return mHolder.decimalValue+other.mHolder.decimalValue;
		}else if(other.mType==Interger){
			return mHolder.decimalValue+double(other.mHolder.intergerValue);
		}
	}else if(mType==Interger){
		if(other.mType==Interger){
			return mHolder.intergerValue+other.mHolder.intergerValue;
		}else if(other.mType==Decimal){
			return double(mHolder.intergerValue)+other.mHolder.decimalValue;
		}
	}
}

XELNumber XELNumber::operator-(const XELNumber& other)
{
	if(mType==Decimal){
		if(other.mType==Decimal){
			return mHolder.decimalValue-other.mHolder.decimalValue;
		}else if(other.mType==Interger){
			return mHolder.decimalValue-double(other.mHolder.intergerValue);
		}
	}else if(mType==Interger){
		if(other.mType==Interger){
			return mHolder.intergerValue-other.mHolder.intergerValue;
		}else if(other.mType==Decimal){
			return double(mHolder.intergerValue)-other.mHolder.decimalValue;
		}
	}
}

XELNumber XELNumber::operator*(const XELNumber& other)
{
	if(mType==Decimal){
		if(other.mType==Decimal){
			return mHolder.decimalValue*other.mHolder.decimalValue;
		}else if(other.mType==Interger){
			return mHolder.decimalValue*double(other.mHolder.intergerValue);
		}
	}else if(mType==Interger){
		if(other.mType==Interger){
			return mHolder.intergerValue*other.mHolder.intergerValue;
		}else if(other.mType==Decimal){
			return double(mHolder.intergerValue)*other.mHolder.decimalValue;
		}
	}
}

XELNumber XELNumber::operator/(const XELNumber& other)
{
	if(mType==Decimal){
		if(other.mType==Decimal){
			return mHolder.decimalValue/other.mHolder.decimalValue;
		}else if(other.mType==Interger){
			return mHolder.decimalValue/double(other.mHolder.intergerValue);
		}
	}else if(mType==Interger){
		if(other.mType==Interger){
			return mHolder.intergerValue/other.mHolder.intergerValue;
		}else if(other.mType==Decimal){
			return double(mHolder.intergerValue)/other.mHolder.decimalValue;
		}
	}
}
