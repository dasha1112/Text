#include "TPage.h"

TPage::TPage()
{
	next = nullptr;
	prev = nullptr;
	begin = nullptr;
	end = nullptr;
	count = 0;
}

TPage::~TPage()
{
	next = nullptr;
	prev = nullptr;
	count = 0;
}

TPage::TPage(const TPage& p)
{
	next = p.next;
	prev = p.prev;
	end = p.end;
	begin = p.begin;
	count = p.count;
}

void TPage::Add(TLine* p)
{
	if (end != nullptr)
	{
		end->SetNext(p);
		p->SetPrev(end);
		end = p;
	}
	else
	{
		begin = end = p;
	}
}


void TPage::Insert(int pos, std::string line)
{
	TLine* curr = GetCountLine(pos); // Получаем строку в данной позиции
	TLine* insertLine = new TLine(curr, curr->GetPrev(), line); // создаем новую строку
	curr->GetPrev()->SetNext(insertLine); // устанавливаем связи между указателями 
	curr->SetPrev(insertLine);
	count++;
}

void TPage::Delete(TLine* p)
{
	p->Clear(); // удаляет строку
	count--;
}

void TPage::PushBegin(TLine* p)
{
	if (begin != nullptr)
	{
		begin->SetPrev(p);
		p->SetNext(begin);
		begin = p;
	}
	else
	{
		begin = end = p;
	}
}

void TPage::SetNext(TPage* p)
{
	next = p;
}

void TPage::SetPrev(TPage* p)
{
	prev = p;
}

int TPage::GetCount()
{
	return count;
}

void TPage::SetCount(int a)
{
	count = a;
}

TPage* TPage::GetNext()
{
	return next;
}

TPage* TPage::GetPrev()
{
	return prev;
}

TLine* TPage::GetBegin()
{
	return begin;
}

TLine* TPage::GetEnd()
{
	return end;
}

TLine* TPage::GetCountLine(int numLine)
{
	TLine* curr = begin;
	for (int i = 1; i < numLine; i++) 
	{
		curr = curr->GetNext();
	}
	return curr;
}


std::ostream& operator<<(std::ostream& out, TPage* page)
{
	TLine* l = page->GetBegin();
	while (l != nullptr)
	{
		out << l << "\n";
		l = l->GetNext();
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const TPage& page)
{
	TLine* l = page.begin;
	while (l != nullptr)
	{
		out << l << "\n";
		l = l->GetNext();
	}
	return out;
}
