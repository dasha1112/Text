#ifndef _BASE_
#define _BASE_

class IBase 
{
public:
	IBase* Find(IBase* p);
	IBase* Find(const char* s);
	IBase* Add(IBase* p);
	IBase* Add(const char* s);
	IBase* Delete(IBase* p);
	IBase* Insert(IBase* p);
};
#endif