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

void TLine::Add(TWord* p) // �������� ����� � ����� �����������
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
  while (i < d.length()) // ���� �� ������ �� ����� ������
  {
    TWord* word = new TWord();
    std::string wordForData = "";
    // ������� ������ �� ��������� ������
    while (d[i] != ' ' && d[i] != '\0' && d[i] != '\n') // ���� �� �������� ������ ��� �� ������ �� ����� ������
    {
      wordForData += d[i];
      i++;
    }
    word->SetData(wordForData); // ������ ������ � �����
    word->SetLength(wordForData.length()); // ���� ���������� ������� � ����� � ����������� ��� ��������� ����� ������
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
  TWord* curr = begin; // ��������� ��� ���������� �� ������
  std::string lineData = ""; // ����� ������ ������ TLine
  while (curr!=nullptr) // ���� �� ������ �� �����
  {
    if (curr->GetData() == pos) // ����� ����� �����, ����� �������� ����� �������� ��������
    {
      TWord* insertWord = new TWord(curr, curr->GetPrev(), word); // ������� �����
      lengthStroka = word.length();
      curr->GetPrev()->SetNext(insertWord); // ������������� ����� ����� ����������� 
      curr->SetPrev(insertWord);
      lineData += insertWord->GetData() + " ";
    }
    lineData += curr->GetData();
    curr = curr->GetNext();
    if (curr != nullptr) { lineData += " "; } // ���� �� ����� �� ����� ������, �� ���������� ������
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

void TLine::Clear() // ������� ������ (� ������ ����� ���� ��������� � ���������� ������)
{
  TLine* nextLine = next; // ������������� ����� ����� �����������
  TLine* prevLine = prev;
  next->SetPrev(prevLine);
  prev->SetNext(nextLine);

  lengthStroka = 0;
  data = "";

  TWord* temp = begin;
  TWord* next = nullptr;
  while (temp != nullptr)  // ���������� � ������� ���
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
