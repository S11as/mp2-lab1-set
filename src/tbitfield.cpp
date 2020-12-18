// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) {
    if (len < 0) throw out_of_range("Length should be positive");
    this->BitLen = len;
    this->MemLen = (len + 31) >> 5;
    this->pMem = new TELEM[this->MemLen];

    if (this->pMem != NULL) {
        for (int i = 0; i < this->MemLen; ++i) {
            this->pMem[i] = 0;
        }
    }
}

TBitField::TBitField(const TBitField &bf)
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[bf.MemLen];
    for (int i = 0; i < this->MemLen; ++i) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    if (this->pMem != NULL) {
        delete[] this->pMem;
        this->pMem = NULL;
    }
}

int TBitField::GetMemIndex(const int n) const
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    return (1 << (n % (sizeof(TELEM) * 8)));
}


int TBitField::GetLength(void) const
{
    return this->BitLen;
}

void TBitField::SetBit(const int n)
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    this->pMem[this->GetMemIndex(n)] = (this->pMem[this->GetMemIndex(n)] | this->GetMemMask(n));
}

void TBitField::ClrBit(const int n)
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    this->pMem[this->GetMemIndex(n)] = (this->pMem[this->GetMemIndex(n)] & ~this->GetMemMask(n));
}

int TBitField::GetBit(const int n) const
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    return (this->pMem[this->GetMemIndex(n)] & this->GetMemMask(n)) != 0;
}


TBitField &TBitField::operator=(const TBitField &bf)
{
    if (&bf != this) {
        if (this->MemLen != bf.MemLen) {
            if (this->pMem != NULL) {
                delete[] this->pMem;
                this->pMem = NULL;
            }
            this->pMem = new TELEM[bf.MemLen];
        }
        this->BitLen = bf.BitLen;
        this->MemLen = bf.MemLen;
        for (int i = 0; i < this->MemLen; ++i) {
            this->pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const
{
    if (&bf == this) return 1;
    if (this->BitLen == bf.BitLen) {
        for (int i = 0; i < this->MemLen; ++i) {
            if (this->pMem[i] != bf.pMem[i]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int TBitField::operator!=(const TBitField &bf) const
{
    if (&bf == this) return 0;
    if (this->BitLen == bf.BitLen) {
        for (int i = 0; i < this->MemLen; ++i) {
            if (this->pMem[i] != bf.pMem[i]) {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf)
{
    int max_length = this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen;
    TBitField tmp(max_length);
    for (int i = 0; i < this->MemLen; ++i) {
        tmp.pMem[i] = this->pMem[i];
    }
    for (int i = 0; i < bf.MemLen; ++i) {
        tmp.pMem[i] |= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf)
{
    int max_length = this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen;
    TBitField tmp(max_length);
    for (int i = 0; i < this->MemLen; ++i) {
        tmp.pMem[i] = this->pMem[i];
    }
    for (int i = 0; i < bf.MemLen; ++i) {
        tmp.pMem[i] &= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void)
{
    int fullMems = (this->BitLen) / (sizeof(TELEM) * 8);
    int exceedBits = (this->BitLen) % (sizeof(TELEM) * 8);

    TBitField tmp(this->BitLen);

    for (int i = 0; i < fullMems; ++i) {
        tmp.pMem[i] = ~this->pMem[i];
    }

    for (int i = 0; i < exceedBits; ++i) {
        int index = sizeof(TELEM) * 8 * fullMems;
        if (!this->GetBit(index + i)) {
            tmp.SetBit(index + i);
        }
    }

    return tmp;
}

istream &operator>>(istream &istr, TBitField &bf)
{
    int index = 0;
    char ch;
    do { istr >> ch; } while (ch != ' ');
    while (true) {
        istr >> ch;
        if (ch == '0') {
            bf.ClrBit(index);
            index++;
        } else if (ch == '1') {
            bf.SetBit(index);
            index++;
        } else {
            break;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf)
{
    int len = bf.GetLength();
    for (int i = 0; i < len; ++i) {
        ostr << bf.GetBit(i);
    }
    ostr << "\n";
    return ostr;
}
