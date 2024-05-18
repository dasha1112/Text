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
  TWord* stroka = new TWord(s); // создаем слово из строки
  TLine res; 
  TPage* page = begin;

  while (page != nullptr) // проходимся по всем страницам
  {
    TLine* line = page->GetBegin();
    while (line != nullptr) // проходимся по всем строкам
    {
      TWord* word = line->GetBegin();
      while (word != nullptr) // проходимся по всем словам 
      {
        if (word->GetData() == stroka->GetData()) // если нашли исходное слово, то возвращаем строку
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
  int lenLine = 0; // длина строки
  int i = 0;
  // Создаем строку TLine из элементов входной строки
  while(i < s.length()) 
  {
    TWord* word = new TWord();
    std::string wordForData = "";
    while (s[i] != ' ' && s[i] != '\0') // пока не встретим пробел
    {
      wordForData += s[i];
      i++;
    }
    word->SetData(wordForData); // кладем строку в слово
    word->SetLength(wordForData.length()); // ищем количество симвлов в слове и присваиваем его параметру длины слова
    lenLine += word->GetLength(); // увеличиваем длину строки на кол-во элементов в слове
    stroka->Add(word); // добавляем слово в конец строки
    stroka->SetData(word->GetData()); // добавляем слово в строку Tline

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
    int countLine = 0; // количество строк в странице
    TPage* page = new TPage();
    while (countLine < 30 && i < lengthStr) 
    {
      TLine* line = new TLine();
      int lenLine = 0; // длина строки
      while (lenLine < 50 && i < lengthStr && s[i]!='\n') // в строке максимум 50 символов
      {
        TWord* word = new TWord();
        std::string wordForData = "";
        // Создаем строку из элементов строки
        while (s[i] != ' ' && s[i] != '\0' && s[i] != '\n') // пока не встретим пробел или не дойдем до конца строки
        {
          wordForData += s[i];
          i++;
        }
        word->SetData(wordForData); // кладем строку в слово
        word->SetLength(wordForData.length()); // ищем количество симвлов в слове и присваиваем его параметру длины слова
        lenLine += word->GetLength(); // увеличиваем длину строки на кол-во элементов в слове
        line->Add(word); // добавляем слово в конец строки
        line->SetData(word->GetData()); // добавляем слово в строку Tline

        if (s[i] == ' ') 
        {
          line->SetData(" ");
          i++;
          lenLine++;
        }
      } 
      if (s[i] == '\n')
      {
        i++; // если дошли до конца строки, то увеличиваем счетчик
      }
      line->SetLength(lenLine); // устанавливаем длину строки
      page->Add(line); // добавляем строку в страницу
      countLine++; 
    }
    page->SetCount(countLine); // устанавливаем кол-во строк в странице
    text->Add(page); // добавляем страницу в текст
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
        while (line->GetLengthStroka()>50) // если в строке больше 50 символов, то переносим последне слово на новую строчку
        {
          TWord* w = line->GetEnd(); // получаем последнее слово
          line = line->GetNext(); // переходим к следующей строчке
          line->PushBegin(w); // кладем слово в начало строчки
        }
      }
      line = line->GetNext();
    }
    page = page->GetNext();
  }
}

void TText::InsertLine(int numPage, int numLine, std::string strline)
{
  TPage* page = GetCountPage(numPage); // находим нужную страницу
  page->Insert(numLine, strline);
  while (page->GetCount() > 30) // если в странице уже 30 строк, то кладем последнюю строку в следующую страницу
  {
    TLine* l = page->GetEnd(); // получаем последнюю строку
    page = page->GetNext(); // переходим к следующей странице
    page->PushBegin(l); // кладем строку в начало страницы
  }
}

void TText::Delete(std::string strLine, std::string strWord)
{
  TWord* stroka = new TWord(strWord); // создаем слово из строки
  TPage* page = begin;
  std::string wordDataLine = ""; // строка данных для нового TLine

  while (page != nullptr) // проходимся по всем страницам
  {
    TLine* line = page->GetBegin();
    while (line != nullptr) // проходимся до нужной строки
    {
      if (line->GetData() == strLine) 
      {
        if (line->GetLengthStroka() == strWord.length()) { line->Clear(); } // если в строке содержится только одно слово, то удаляем строку
        TWord* word = line->GetBegin();
        while (word != nullptr) // проходимся до нужного слова
        {
          if (word->GetData() == strWord) // как тольео нашли слово - удаляем его
          {
            TWord* w = word->GetNext(); // указател на след. слово после введенного (чтобы не нарушать цикл)
            line->Delete(word);
            word = w;
          }
          wordDataLine += word->GetData(); // Если не удалено, то добавл. его в строку для данных TLine
          word = word->GetNext();
          if (word != nullptr) { wordDataLine += " "; } // если не конец строки, то полсе слова добавл. пробел
        }
        line->SetNewData(wordDataLine); // обновляем данные строки TLine
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
