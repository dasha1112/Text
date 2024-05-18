#ifndef _LINE_
#define _LINE_
#include "TWord.h"
#include <algorithm>
#include <iostream>
class TLine 
{
protected:
	TLine* next; // указатель на след строку
	TLine* prev; // указатель на пред строку
	int lengthStroka; // количество символов в строке
	std::string data; // строка
	TWord* begin; // указателть на первое слово в строке
	TWord* end; // указатель на последнее слово в строке
public:
	TLine();
	~TLine();
	TLine(const TLine& p);
	TLine(TLine* n, TLine* p, std::string d);
	void Add(TWord* p); // добавляет в конец слово
	void Delete(TWord* p);
	void Insert(std::string word, std::string pos); // вставляет слово перед указанным (pos)

	void Clear();
	void SetNext(TLine* p);
	void SetPrev(TLine* p);
	void PushBegin(TWord* p);
	int GetLengthStroka();
	void SetLength(int a);
	TLine* GetNext();
	TLine* GetPrev();
	TWord* GetBegin();
	TWord* GetEnd();
	std::string GetData();
	void SetData(std::string s);
	void SetNewData(std::string s);

	friend std::ostream& operator<< (std::ostream& out, TLine* line);
};
#endif