#include "TLine.h"

TLine::TLine()
{
  next = nullptr;
  prev = nullptr;
  begin = nullptr;
  end = nullptr;
  lengthStroka = 0;
  data = "";
}

TLine::~TLine()
{
  next = nullptr;
  prev = nullptr;
  lengthStroka = 0;
  data = "";
}

TLine::TLine(const TLine& p)
{
  next = p.next;
  prev = p.prev;
  lengthStroka = p.lengthStroka;
  data = p.data;
}

void TLine::Add(TWord* p) // добавить слово в конец предложения
{
  if (end == nullptr) 
  {
    begin = end = p;

  }
  else 
  {
    end->SetNext(p);
    p->SetPrev(end);
    end = p;
  }
}

TLine::TLine(TLine* n, TLine* p, std::string d)
{
  begin = nullptr;
  end = nullptr;
  next = n;
  prev = p;
  data = d;
  lengthStroka = d.length();
  
  int i = 0;
  while (i < d.length()) // пока не дойдем до конца строки
  {
    TWord* word = new TWord();
    std::string wordForData = "";
    // Создаем строку из элементов строки
    while (d[i] != ' ' && d[i] != '\0' && d[i] != '\n') // пока не встретим пробел или не дойдем до конца строки
    {
      wordForData += d[i];
      i++;
    }
    word->SetData(wordForData); // кладем строку в слово
    word->SetLength(wordForData.length()); // ищем количество симвлов в слове и присваиваем его параметру длины словаи
    Add(word);
    if (d[i] == ' ')
    {
      i++;
    }
  }
}

void TLine::Delete(TWord* p)
{
  TWord* prevWord = p->GetPrev();
  TWord* nextWord = p->GetNext();
  nextWord->SetPrev(prevWord);
  prevWord->SetNext(nextWord);
  delete p;
}

void TLine::Insert(std::string pos, std::string word)
{
  TWord* curr = begin; // указатель для перемщения по строке
  std::string lineData = ""; // новая строка данных TLine
  while (curr!=nullptr) // пока не дойдем до конца
  {
    if (curr->GetData() == pos) // когда нашли слово, после которого хотим вставить исходное
    {
      TWord* insertWord = new TWord(curr, curr->GetPrev(), word); // создаем слово
      lengthStroka = word.length();
      curr->GetPrev()->SetNext(insertWord); // устанавливаем связи между указателями 
      curr->SetPrev(insertWord);
      lineData += insertWord->GetData() + " ";
    }
    lineData += curr->GetData();
    curr = curr->GetNext();
    if (curr != nullptr) { lineData += " "; } // если не дошли до конца строки, то прибавляем пробел
  }
  data = lineData;
  lengthStroka = data.length();
}

void TLine::SetNext(TLine* p)
{
  next = p;
}

void TLine::SetPrev(TLine* p)
{
  prev = p;
}

int TLine::GetLengthStroka()
{
  return lengthStroka;
}

void TLine::Clear() // удаляет строку (в случае когда есть следующая и предыдущая строки)
{
  TLine* nextLine = next; // устанавливаем связи между указателями
  TLine* prevLine = prev;
  next->SetPrev(prevLine);
  prev->SetNext(nextLine);

  lengthStroka = 0;
  data = "";

  TWord* temp = begin;
  TWord* next = nullptr;
  while (temp != nullptr)  // проходимся и удаляем все
  {
    next = temp->GetNext();
    delete temp;
    temp = next;
  }
  begin = nullptr;
  end = nullptr;
}

TLine* TLine::GetNext()
{
  return next;
}

void TLine::PushBegin(TWord* p)
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

void TLine::SetLength(int a)
{
  lengthStroka = a;
}

TLine* TLine::GetPrev()
{
  return prev;
}

TWord* TLine::GetBegin()
{
  return begin;
}

TWord* TLine::GetEnd()
{
  return end;
}

std::string TLine::GetData()
{
  return data;
}

void TLine::SetData(std::string s)
{
  data += s;
}

void TLine::SetNewData(std::string s)
{
  data = s;
}

std::ostream& operator<<(std::ostream& out, TLine* line)
{
  out << line->GetData();
  return out;
}
