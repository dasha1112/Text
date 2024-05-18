#ifndef _WORD_
#define _WORD_
#include <algorithm>
#include <iostream>

class TWord
{
protected:
	TWord* next; // указатель на следующее слово
	TWord* prev; // указатель на предыдущее слов
	std::string data; // строка слова
	int length; // длина слова
public:
	TWord();
	TWord(std::string s);
	TWord(TWord* n, TWord* p, std::string s);
	~TWord();
	TWord(const TWord& p);

	void SetNext(TWord* p);
	void SetPrev(TWord* p);
	TWord* GetNext();
	TWord* GetPrev();
	int GetLength();
	void SetData(std::string s);
	void SetLength(int a);
	std::string GetData();

	friend std::ostream& operator<< (std::ostream& out, TWord& word);
};
#endif