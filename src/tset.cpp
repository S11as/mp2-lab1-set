// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp) {
    if (mp <= 0) throw out_of_range("Length should be positive");
    this->MaxPower = mp;
}

TSet::TSet(const TSet &s) : BitField(s.BitField) {
    this->MaxPower = s.MaxPower;
}

TSet::TSet(const TBitField &bf) : BitField(bf) {
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField() {
    TBitField tmp(this->BitField);
    return tmp;
}

int TSet::GetMaxPower(void) const
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem)
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
    this->BitField.ClrBit(Elem);
}

TSet &TSet::operator=(const TSet &s)
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const
{
    return (this->BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const
{
    return (this->BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s)
{
    return TSet(this->BitField | s.BitField);
}

TSet TSet::operator+(const int Elem)
{
    TSet tmp(this->BitField);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem)
{
    TSet tmp(this->BitField);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s)
{
    TSet tmp(this->BitField & s.BitField);
    return tmp;
}

TSet TSet::operator~(void)
{
    TSet tmp(~this->BitField);
    return tmp;
}

istream &operator>>(istream &istr, TSet &s)
{
    int elem;
    char ch;
    do { istr >> ch; } while (ch != '{');
    while(true){
        istr>>elem;
        s.InsElem(elem);
        do{ istr >> ch;} while (ch != ' ' && ch != '}');
        if(ch == '}') break;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TSet &s)
{
    ostr << "{ ";
    for (int i = 0; i < s.MaxPower; ++i) {
        if (s.BitField.GetBit(i)) {
            ostr << i << " ";
        }
    }
    ostr << " }\n";
    return ostr;
}
