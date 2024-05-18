#ifndef _TEXT_
#define _TEXT_
#include <algorithm>
#include <iostream>
#include "TPage.h"

class TText 
{
protected:
	TPage* begin;
	TPage* end;
	int countPage;
public:
	TText();
	~TText();
	TText(TText& p);

	void Add(TPage* p);
	TText CreateText(std::string s); // сооздать текст из строки

	TLine FindLine(std::string s); // найти строку, в которой содержится данное слово
	TPage FindPage(std::string s); // найти страницу, в которой содержится данная строка

	void InsertWord(std::string stringLine, std::string pos, std::string word); // вставить слово в строку
	void InsertLine(int numPage, int numLine, std::string strline); // вставить строку в страницу

	void Delete(std::string strLine, std::string strWord); // удалить слово из строки
	void DeleteLine(int numPage, int numLine); // удалить строку

	void AddLine(std::string s);// Добавить новую строчку в самый конец

	friend std::ostream& operator<< (std::ostream& out, TText& text);

	TPage* GetBegin();
	TPage* GetEnd();
	int GetCount();
	void SetCount(int a);
	TPage* GetCountPage(int num);
};
#endif