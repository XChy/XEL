#ifndef XELFUNCTIONS_H
#define XELFUNCTIONS_H

#include <XEL/xel_global.h>
#include <XEL/NodeCreator.h>

class SinFunction:public XELFunction{
	class SinNode:public FunctionNode{
	public:
		virtual Variant evaluate() const;
	};
public:
	virtual FunctionNode* create() const{return new SinNode;}
	virtual FunctionNode* create(int paramSize) const;
	virtual bool isVariableParam() const{return false;}
	virtual bool isSupportParamSize(int paramSize) const{return paramSize==1;}
};

class CosFunction:public XELFunction{
	class CosNode:public FunctionNode{
	public:
		virtual Variant evaluate() const;
	};
public:
	virtual FunctionNode* create() const{return new CosNode;}
	virtual FunctionNode* create(int paramSize) const;
	virtual bool isVariableParam() const{return false;}
	virtual bool isSupportParamSize(int paramSize) const{return paramSize==1;}
};

class TanFunction:public XELFunction{
	class TanNode:public FunctionNode{
	public:
		virtual Variant evaluate() const;
	};
public:
	virtual FunctionNode* create() const{return new TanNode;}
	virtual FunctionNode* create(int paramSize) const;
	virtual bool isVariableParam() const{return false;}
	virtual bool isSupportParamSize(int paramSize) const{return paramSize==1;}
};

class CotFunction:public XELFunction{
	class CotNode:public FunctionNode{
	public:
		virtual Variant evaluate() const;
	};
public:
	virtual FunctionNode* create() const{return new CotNode;}
	virtual FunctionNode* create(int paramSize) const;
	virtual bool isVariableParam() const{return false;}
	virtual bool isSupportParamSize(int paramSize) const{return paramSize==1;}
};
#endif
