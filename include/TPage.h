#ifndef _PAGE_
#define _PAGE_
#include <algorithm>
#include <iostream>
#include "TLine.h"

class TPage 
{
protected:
	TPage* next; // указатель на следующую страницу
	TPage* prev; // указатель на предыдущую страницу
	TLine* begin; // указатель на начальную строку
	TLine* end; // указатель на конечную строку
	int count; // количетсво строк
public:
	TPage();
	~TPage();
	TPage(const TPage& p);
	void Add(TLine* p); // добавляет строку в конец страницы
	void Insert(int pos, std::string line); // вставляет новую строку перед указанной строкой (pos)
	void Delete(TLine* p);
	
	void PushBegin(TLine* p);
	void SetNext(TPage* p);
	void SetPrev(TPage* p);
	int GetCount();
	void SetCount(int a);
	TPage* GetNext();
	TPage* GetPrev();
	TLine* GetBegin();
	TLine* GetEnd();
	TLine* GetCountLine(int numLine);
	friend std::ostream& operator<< (std::ostream& out, TPage* page);
	friend std::ostream& operator<< (std::ostream& out, const TPage& page);
};
#endif