#include "TText.h"

TText::TText()
{
  begin = nullptr;
  end = nullptr;
  countPage = 0;
}

TText::~TText()
{
  begin = nullptr;
  end = nullptr;
  countPage = 0;
}

TText::TText(TText& p)
{
  begin = p.begin;
  end = p.end;
  countPage = p.countPage;
}

void TText::Add(TPage* p)
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

TLine TText::FindLine(std::string s)
{
  TWord* stroka = new TWord(s); // ������� ����� �� ������
  TLine res; 
  TPage* page = begin;

  while (page != nullptr) // ���������� �� ���� ���������
  {
    TLine* line = page->GetBegin();
    while (line != nullptr) // ���������� �� ���� �������
    {
      TWord* word = line->GetBegin();
      while (word != nullptr) // ���������� �� ���� ������ 
      {
        if (word->GetData() == stroka->GetData()) // ���� ����� �������� �����, �� ���������� ������
        {
          //TLine* l = new TLine(*line);
          res = *line;
          return res;
        }
        word = word->GetNext();
      }
      line = line->GetNext();
    }
    page = page->GetNext();
  }
  throw "Line not found"; 
}

TPage TText::FindPage(std::string s)
{
  TPage res;
  TLine* stroka = new TLine();
  int lenLine = 0; // ����� ������
  int i = 0;
  // ������� ������ TLine �� ��������� ������� ������
  while(i < s.length()) 
  {
    TWord* word = new TWord();
    std::string wordForData = "";
    while (s[i] != ' ' && s[i] != '\0') // ���� �� �������� ������
    {
      wordForData += s[i];
      i++;
    }
    word->SetData(wordForData); // ������ ������ � �����
    word->SetLength(wordForData.length()); // ���� ���������� ������� � ����� � ����������� ��� ��������� ����� �����
    lenLine += word->GetLength(); // ����������� ����� ������ �� ���-�� ��������� � �����
    stroka->Add(word); // ��������� ����� � ����� ������
    stroka->SetData(word->GetData()); // ��������� ����� � ������ Tline

    if (s[i] == ' ')
    {
      stroka->SetData(" ");
      i++;
      lenLine++;
    }
  }

  TPage* page = begin;
  while (page != nullptr)
  {
    TLine* line = page->GetBegin();
    while (line != nullptr) 
    {
      if (line->GetData() == stroka->GetData())
      {
        //TPage* p = new TPage(*page);
        res = *page;
        return res;
      }
      line = line->GetNext();
    }
    page = page->GetNext();
  }
  //return res;
}

TText TText::CreateText(std::string s)
{
  int i = 0;
  int lengthStr = s.length();
  int numOfPage = 0;
  TText* text = new TText();
  TText res;
  while (i < lengthStr) 
  {
    int countLine = 0; // ���������� ����� � ��������
    TPage* page = new TPage();
    while (countLine < 30 && i < lengthStr) 
    {
      TLine* line = new TLine();
      int lenLine = 0; // ����� ������
      while (lenLine < 50 && i < lengthStr && s[i]!='\n') // � ������ �������� 50 ��������
      {
        TWord* word = new TWord();
        std::string wordForData = "";
        // ������� ������ �� ��������� ������
        while (s[i] != ' ' && s[i] != '\0' && s[i] != '\n') // ���� �� �������� ������ ��� �� ������ �� ����� ������
        {
          wordForData += s[i];
          i++;
        }
        word->SetData(wordForData); // ������ ������ � �����
        word->SetLength(wordForData.length()); // ���� ���������� ������� � ����� � ����������� ��� ��������� ����� �����
        lenLine += word->GetLength(); // ����������� ����� ������ �� ���-�� ��������� � �����
        line->Add(word); // ��������� ����� � ����� ������
        line->SetData(word->GetData()); // ��������� ����� � ������ Tline

        if (s[i] == ' ') 
        {
          line->SetData(" ");
          i++;
          lenLine++;
        }
      } 
      if (s[i] == '\n')
      {
        i++; // ���� ����� �� ����� ������, �� ����������� �������
      }
      line->SetLength(lenLine); // ������������� ����� ������
      page->Add(line); // ��������� ������ � ��������
      countLine++; 
    }
    page->SetCount(countLine); // ������������� ���-�� ����� � ��������
    text->Add(page); // ��������� �������� � �����
    numOfPage++;
  }
  res = *text;
  res.SetCount(numOfPage);
  return res;
}

void TText::InsertWord(std::string stringLine, std::string pos, std::string word)
{
  TPage* page = begin;
  while (page != nullptr) 
  {
    TLine* line = page->GetBegin();
    while (line != nullptr)
    {
      if (line->GetData() == stringLine) 
      {
        line->Insert(pos, word);
        while (line->GetLengthStroka()>50) // ���� � ������ ������ 50 ��������, �� ��������� �������� ����� �� ����� �������
        {
          TWord* w = line->GetEnd(); // �������� ��������� �����
          line = line->GetNext(); // ��������� � ��������� �������
          line->PushBegin(w); // ������ ����� � ������ �������
        }
      }
      line = line->GetNext();
    }
    page = page->GetNext();
  }
}

void TText::InsertLine(int numPage, int numLine, std::string strline)
{
  TPage* page = GetCountPage(numPage); // ������� ������ ��������
  page->Insert(numLine, strline);
  while (page->GetCount() > 30) // ���� � �������� ��� 30 �����, �� ������ ��������� ������ � ��������� ��������
  {
    TLine* l = page->GetEnd(); // �������� ��������� ������
    page = page->GetNext(); // ��������� � ��������� ��������
    page->PushBegin(l); // ������ ������ � ������ ��������
  }
}

void TText::Delete(std::string strLine, std::string strWord)
{
  TWord* stroka = new TWord(strWord); // ������� ����� �� ������
  TPage* page = begin;
  std::string wordDataLine = ""; // ������ ������ ��� ������ TLine

  while (page != nullptr) // ���������� �� ���� ���������
  {
    TLine* line = page->GetBegin();
    while (line != nullptr) // ���������� �� ������ ������
    {
      if (line->GetData() == strLine) 
      {
        if (line->GetLengthStroka() == strWord.length()) { line->Clear(); } // ���� � ������ ���������� ������ ���� �����, �� ������� ������
        TWord* word = line->GetBegin();
        while (word != nullptr) // ���������� �� ������� �����
        {
          if (word->GetData() == strWord) // ��� ������ ����� ����� - ������� ���
          {
            TWord* w = word->GetNext(); // �������� �� ����. ����� ����� ���������� (����� �� �������� ����)
            line->Delete(word);
            word = w;
          }
          wordDataLine += word->GetData(); // ���� �� �������, �� ������. ��� � ������ ��� ������ TLine
          word = word->GetNext();
          if (word != nullptr) { wordDataLine += " "; } // ���� �� ����� ������, �� ����� ����� ������. ������
        }
        line->SetNewData(wordDataLine); // ��������� ������ ������ TLine
        line->SetLength(wordDataLine.length()); 
      }
      line = line->GetNext();
    }
    page = page->GetNext();
  }
}

void TText::DeleteLine(int numPage, int numLine)
{
  TPage* page = GetCountPage(numPage);
  TLine* line = page->GetCountLine(numLine);
  page->Delete(line);
}

void TText::AddLine(std::string s)
{
  TPage* page = end;
  TLine* line = new TLine(nullptr, nullptr, s);
  page->Add(line);
}

TPage* TText::GetBegin()
{
  return begin;
}

TPage* TText::GetEnd()
{
  return end;
}

int TText::GetCount()
{
  return countPage;
}

void TText::SetCount(int a)
{
  countPage = a;
}

TPage* TText::GetCountPage(int num)
{
  TPage* p = begin;
  for (int i = 1; i < num; i++)
  {
    p = p->GetNext();
  }
  return p;
}

std::ostream& operator<<(std::ostream& out, TText& text)
{
  TPage* p = text.GetBegin();
  while (p != nullptr)
  {
    out << p;
    p = p->GetNext();
  }
  return out;
}
