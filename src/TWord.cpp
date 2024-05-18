#include "TWord.h"

TWord::TWord()
{
	prev = nullptr;
	next = nullptr;
	data = "";
	length = 0;
}

TWord::TWord(std::string s)
{
	prev = nullptr;
	next = nullptr;
	data = s;
	length = s.length();
}

TWord::TWord(TWord* n, TWord* p, std::string s)
{
	prev = p;
	next = n;
	data = s;
	length = s.length();
}

TWord::~TWord()
{
	prev = nullptr;
	next = nullptr;
	data = "";
	length = 0;
}

TWord::TWord(const TWord& p)
{
	prev = p.prev;
	next = p.next;
	data = p.data;
	length = p.length;
}

void TWord::SetNext(TWord* p)
{
	next = p;
}

void TWord::SetPrev(TWord* p)
{
	prev = p;
}

TWord* TWord::GetNext()
{
	return next;
}

TWord* TWord::GetPrev()
{
	return prev;
}

int TWord::GetLength()
{
	return length;
}

void TWord::SetData(std::string s)
{
	data = s;
}

void TWord::SetLength(int a)
{
	length = a;
}

std::string TWord::GetData()
{
	return data;
}

std::ostream& operator<<(std::ostream& out, TWord& word)
{
	out << word.GetData();
	return out;
}
