// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include "conio.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len < 0)
throw "negative length";
	BitLen=len;
	MemLen=(len-1)/(sizeof(TELEM) * 8) +1;
	pMem=new TELEM[MemLen];
	memset(pMem,0, MemLen * sizeof(TELEM));
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM[MemLen];
	for(int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n>BitLen))
		throw "wrong n";
  return (n / BITS_IN_ONE_MEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n>BitLen))
		throw "wrong n";
  return 1 << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n>BitLen))
		throw "wrong n";
	int k=n/BITS_IN_ONE_MEM;//k-номер блока
	int offset=n % BITS_IN_ONE_MEM;
	TELEM mask=GetMemMask(n);
	pMem[k]=pMem[k]|mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n>BitLen))
		throw "wrong n";
	int k=n/BITS_IN_ONE_MEM;//k-номер блока
	int offset=n % BITS_IN_ONE_MEM;
	TELEM mask=GetMemMask(n);
	pMem[k]=pMem[k]& (~mask);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n>BitLen))
		throw "wrong n";
	int res = pMem[GetMemIndex(n)]&GetMemMask(n);
	if(res>0)
	return 1;
	else
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)  return *this; 
	if (bf.pMem== NULL) //присваиваем пустое поле
		{ 
			delete []pMem; 
			BitLen=bf.BitLen; 
			MemLen=bf.MemLen; 
			return *this; 
	}
		if (MemLen != bf.MemLen) // разное кол-во эл-ов в массивах - пересоздаём
		{ 
			if (pMem != NULL) delete []pMem;
			MemLen=bf.MemLen;
			pMem=new TELEM[MemLen];
		}
	BitLen=bf.BitLen;
	for (int i=0; i<bf.MemLen; i++) 
		pMem[i] = bf.pMem[i];
	return *this;
	
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen==bf.BitLen)
	{
		for (int i=0;i<MemLen;i++)
			if (pMem[i]!=bf.pMem[i])
				return 0;
		return 1;
	}
	else
		return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{ 
	int len=bf.BitLen;
	if (BitLen>bf.BitLen)
	{
		len=BitLen;
	}
	
	TBitField temp(len);
	for (int i=0;i<MemLen;i++)
		temp.pMem[i]=pMem[i];

	for (int i=0;i<bf.MemLen;i++)
	temp.pMem[i]|=bf.pMem[i];
	
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	
	int len = BitLen;

	if ( bf.BitLen < len ) 
	{ 
		len = bf.BitLen; 
	}	
	TBitField temp(len);  
	memcpy(temp.pMem, pMem, sizeof(temp.pMem) ); 
		for (int i=0; i < temp.MemLen; i++ )  
		temp.pMem[i] &= bf.pMem[i];

	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len=BitLen;
	TBitField temp(len);
	for (int i=0;i<(temp.MemLen-1);i++)
	temp.pMem[i]=~pMem[i];
	for (int j=(temp.MemLen-1)*BITS_IN_ONE_MEM; j<temp.BitLen;j++)
	{
		int a=GetBit(j);
		if(a==0)
			temp.SetBit(j);
		else temp.ClrBit(j);
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0;
	char ch;
	{
		do
		{
			istr>>ch;
		}
		while (ch!=' ');
		while (1)
		{
			istr>>ch;
			if(ch=='0') bf.ClrBit(i++);
			else if (ch=='1') bf.SetBit(i++); 
			else break;
		}
	return istr;
 
}
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
int len=bf.GetLength();
	for (int i=0; i<len; i++)
		if(bf.GetBit(i))
			ostr<<'1';
		else ostr<<'1';
  return ostr;
}