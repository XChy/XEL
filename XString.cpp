#include <XString.h>

StringData::StringData(const StringData& other){
	allocate(other.allocSize);
	size=other.size;
	data[size]='\0';
	memcpy(data,other.data,other.size*sizeof(char16_t));
}

StringData::StringData(uint allocSize)
{
	allocate(allocSize);
	size=0;
	data[0]='\0';
}

void StringData::allocate(uint allocSize){
	data=new char16_t[allocSize];
	this->allocSize=allocSize;
}

void StringData::reallocate(uint allocSize){
	char16_t* newData=new char16_t[allocSize];
	this->allocSize=allocSize;
	memcpy(newData,data,size*sizeof(char16_t));
	delete data;
	data=newData;
}

StringData::~StringData(){
	delete data;
}

bool XChar::isDigit() const
{
	return ucs>='0'&&ucs<='9';
}

bool XChar::isSpace() const
{
	return ucs==' '||ucs=='\t';
}

bool XChar::isLetter() const
{
	return (ucs>='a'&&ucs<='z')||(ucs>='A'&&ucs<='Z');
}

bool XChar::isLetterOrDigit() const{
	return isLetter()||isDigit();
}

int XChar::digitValue() const
{
	return ucs-'0';
}

XChar XChar::operator-(const XChar& other) const
{
	return XChar(ucs-other.ucs);
}

bool XChar::operator==(XChar other) const
{
	return ucs==other.ucs;
}

bool XChar::operator!=(XChar other) const
{
	return ucs!=other.ucs;
}

bool XChar::operator>(XChar other) const
{
	return ucs>other.ucs;
}

bool XChar::operator<(XChar other) const
{
	return ucs<other.ucs;
}

bool XChar::operator>=(XChar other)const
{
	return ucs>=other.ucs;
}

bool XChar::operator<=(XChar other)const
{
	return ucs<=other.ucs;
}


int ucs2len(const char16_t* str){
	const char16_t* it=str;
	while(*(++it)){}
	return it-str;
}

void xstrcpy(char16_t* dst,const char* src,int size)
{
	while (size--)
		*dst++ = *src++;
}

void xstrcpy(char16_t* dst,const wchar_t* src,int size)
{
	memcpy(dst,src,size*sizeof(char16_t));
}

void xstrcpy(char16_t* dst,const char16_t* src,int size)
{
	memcpy(dst,src,size*sizeof(char16_t));
}

XString::XString()
	:d(new StringData)
{}

XString::XString(const XString& other)
	:d(other.d)
{}

XString::XString(const char* cstr)
{
	int len=strlen(cstr);
	d.ref=new Ref<StringData>(new StringData(len+1));
	d.data()->size=len;
	xstrcpy(d.data()->data,cstr,len+1);
}

XString::XString(const wchar_t* wstr)
{
	int len=wcslen(wstr);
	d.ref=new Ref<StringData>(new StringData(len+1));
	d.data()->size=len;
	xstrcpy(d.data()->data,wstr,len+1);
}

XString::XString(const char16_t* ustr)
{
	int len=ucs2len(ustr);
	d.ref=new Ref<StringData>(new StringData(len+1));
	d.data()->size=len;
	xstrcpy(d.data()->data,ustr,len+1);
}

char16_t*XString::data() const
{
	return d.data()->data;
}

int XString::size() const
{
	return d.data()->size;
}

XString&XString::operator=(const char16_t* ustr){
	int len=ucs2len(ustr);
	if(d.data()->allocSize<len+1){
		delete[] d.data()->data;
		d.data()->allocate(len+1);
	}
	d.data()->size=len;
	xstrcpy(d.data()->data,ustr,len+1);
	return *this;
}

XString& XString::operator=(const char* cstr){
	int len=strlen(cstr);
	if(d.data()->allocSize<len+1){
		delete d.data()->data;
		d.data()->allocate(len+1);
	}
	xstrcpy(d.data()->data,cstr,len+1);
	return *this;
}

XString& XString::operator=(const wchar_t* wstr){
	int len=wcslen(wstr);
	if(d.data()->allocSize<len+1){
		delete d.data()->data;
		d.data()->allocate(len+1);
	}
	d.data()->size=len;
	xstrcpy(d.data()->data,wstr,len+1);
	return *this;
}

XString& XString::append(const char* cstr){
	if(!isDetach()){
		detach();
	}
	int otherSize=strlen(cstr);
	int totalSize=d.data()->size+otherSize;
	if(d.data()->allocSize<totalSize+1){
		d.data()->reallocate((totalSize+1)*2);
	}
	xstrcpy(d.data()->data+d.data()->size,cstr,otherSize+1);
	d.data()->size=totalSize;
	return *this;
}

XString& XString::append(const wchar_t* wstr){
	if(!isDetach()){
		detach();
	}
	int otherSize=wcslen(wstr);
	int totalSize=d.data()->size+otherSize;
	if(d.data()->allocSize<totalSize+1){
		d.data()->reallocate((totalSize+1)*2);
	}
	xstrcpy(d.data()->data+d.data()->size,wstr,otherSize+1);
	d.data()->size=totalSize;
	return *this;
}

XString& XString::append(const XString& other){
	if(!isDetach()){
		detach();
	}
	int otherSize=other.d.data()->size;
	int totalSize=d.data()->size+otherSize;
	if(d.data()->allocSize<totalSize+1){
		d.data()->reallocate((totalSize+1)*2);
	}
	xstrcpy(d.data()->data+d.data()->size,other.data(),otherSize+1);
	d.data()->size=totalSize;
	return *this;
}

XString& XString::append(const char16_t* ustr){
	if(!isDetach()){
		detach();
	}
	int otherSize=ucs2len(ustr);
	int totalSize=d.data()->size+otherSize;
	if(d.data()->allocSize<totalSize+1){
		d.data()->reallocate((totalSize+1)*2);
	}
	xstrcpy(d.data()->data+d.data()->size,ustr,otherSize+1);
	d.data()->size=totalSize;
	return *this;
}

XString& XString::append(XChar xc)
{
	if(!isDetach()){
		detach();
	}
	int totalSize=d.data()->size+1;
	if(d.data()->allocSize<totalSize+1){
		d.data()->reallocate((totalSize+1)*2);
	}
	d.data()->data[totalSize-1]=xc.ucs;
	d.data()->data[totalSize]='\0';
	d.data()->size=totalSize;
	return *this;
}

XString& XString::reverse()
{
	std::reverse(begin(),end());
	return *this;
}

XString XString::operator+(const char* cstr) const
{
	return XString(*this).append(cstr);
}

XString XString::operator+(const wchar_t* wstr) const
{
	return XString(*this).append(wstr);
}

XString XString::operator+(const XString& other) const
{
	return XString(*this).append(other);
}

XString XString::operator+(const char16_t* ustr) const
{
	return XString(*this).append(ustr);
}

XString XString::operator+(XChar xc) const
{
	return XString(*this).append(xc);
}

bool XString::operator==(const XString& other) const
{
	if(d.ref==other.d.ref){
		return true;
	}else if(size()==other.size()){
		return memcmp(data(),other.data(),size())==0;
	}else{
		return false;
	}
}

bool XString::contains(XChar xc) const
{
	for(auto it=begin();it!=end();++it){
		if(*it==xc){
			return true;
		}
	}
	return false;
}

void XString::removeAt(int pos){
	if(!isDetach()){
		detach();
	}
	xstrcpy(d.data()->data+pos,d.data()->data+pos+1,d.data()->size-pos-1);
	d.data()->data[--d.data()->size]='\0';
}

void XString::remove(int pos, int len){
	if(!isDetach()){
		detach();
	}
	xstrcpy(d.data()->data+pos,d.data()->data+pos+len,d.data()->size-pos-len);
	d.data()->data[d.data()->size-=len]='\0';
}

void XString::removeLast(){
	if(!isDetach()){
		detach();
	}
	d.data()->data[--d.data()->size]='\0';
}

std::string XString::toStdString() const
{
	std::string result;
	for(char16_t* p=data();p!=data()+size();++p){
		result.push_back(*p);
	}
}

int XString::toInt(int base) const
{
	int result=0;
	switch (base) {
		case 2:
			for(auto it=begin();it!=end();++it){
				result<<=1;
				if(*it=='1'){
					result+=1;
				}
			}
			break;
		case 10:
			for(auto it=begin();it!=end();++it){
				result*=10;
				result+=it->digitValue();
			}
			break;
		case 16:
			for(auto it=begin();end();++it){
				result<<=4;
				if(it->isDigit()){
					result+=it->digitValue();
				}else if(*it>='a'||*it<='f'){
					result+=10+it->digitValue();
				}
			}
			break;
	}
	return result;
}

double XString::toDouble() const
{
	double result=0;
	for(auto it=begin();it!=end();++it){
		if(*it=='.'){
			++it;
			double decMul=1;
			while(it!=end()){
				if(*it=='e'){
					goto E;
				}
				decMul*=10;
				result+=(double(it->digitValue())/decMul);
				++it;
			}
			break;
		}else if(*it=='e'){
			++it;
E:
			bool isMinus=false;
			if(*it=='+'){
				++it;
			}else if(*it=='-')
			{
				++it;
				isMinus=true;
			}
			double ePart=0;
			while(it!=end()){
				ePart*=10;
				ePart+=it->digitValue();
				++it;
			}
			if(isMinus){
				while(ePart--){
					result/=10;
				}
			}else{
				while(ePart--){
					result*=10;
				}
			}
			break;
		}else{
			result*=10;
			result+=it->digitValue();
		}

	}

	return result;
}

XString XString::number(int v)
{
	XString result;
	if(v<0){
		result.append('-');
	}
	while(v){
		result.append(XChar(char(v%10+'0')));
		v/=10;
	}
	return result.reverse();
}

XString XString::number(double v,int prec)
{
	XString result;
	int intPart=v;
	double decPart=v-intPart;
	if(!intPart){
		result.append('0');
	}else{
		while(intPart){
			result.append(XChar(char(intPart%10+'0')));
			intPart/=10;
		}
		result.reverse();
	}

	if(decPart){
		result.append('.');
		while(prec--){
			int currentDigit=int(decPart*=10);
			if(!currentDigit){
				break;
			}
			result.append(XChar(char(currentDigit+'0')));
			decPart-=currentDigit;
		}
	}
	return result;
}

XString::iterator XString::begin(){
	return (iterator)d.data()->data;
}

XString::iterator XString::end(){
	return (iterator)(d.data()->data+d.data()->size);
}

XString::const_iterator XString::begin() const
{
	return (iterator)d.data()->data;
}

XString::const_iterator XString::end() const
{
	return (iterator)(d.data()->data+d.data()->size);
}

bool XString::isDetach(){
	return d.ref->refCount()==1;
}

void XString::detach(){
	d.ref->unref();
	d.ref=new Ref<StringData>(new StringData(*d.data()));
}

XString operator+(const char* cstr,const XString& xstr)
{
	return XString(cstr).append(xstr);
}
