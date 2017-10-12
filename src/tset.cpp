// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
}

TSet::operator TBitField()
{
	 TBitField temp(this->BitField); 
	 return temp; 
 }

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	//BitField.GetBit(Elem);
	for(int i=0;i<MaxPower;i++)
	if (BitField.GetBit(i)==BitField.GetBit(Elem))
    return 1;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField=s.BitField; 
	MaxPower=s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if(BitField==s.BitField)
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if(BitField!=s.BitField)
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	BitField=BitField | s.BitField; 
	return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	res.InsElem(Elem);
	return res;

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	BitField=BitField & s.BitField; 
	return *this;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res( (~BitField) ); 
	return res;

}

// перегрузка ввода/вывода


istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp;
	char ch;
	{
		do
		{
			istr>>ch;
		}
		while (ch!='{');
		do
		{
			istr>>temp;
			s.InsElem(temp);
			do
			{
				istr>>ch;
			}
			while((ch!=',')&&(ch!='}') );
		}
			while (ch!='}');
}
	return istr; 
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i,n;
	char ch=' ';
	ostr<<"{";
	n=s.GetMaxPower();
	for (i=0;i<n;i++)
	{
		if (s.IsMember(i) )
		{
			ostr<<ch<<' '<<i;
			ch=',';
		}
	}
	ostr<<"}";
  return ostr;
}