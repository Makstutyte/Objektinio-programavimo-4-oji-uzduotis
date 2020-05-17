#ifndef ANTRASTE_VECTOR_H_INCLUDED
#define ANTRASTE_VECTOR_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <numeric>
#include <limits>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>
#include "vektoriukas.h"
const int daugiausia = 50;

class Base
{
  protected:
      std::string vardas;
      std::string pavarde;

      inline Base() : vardas("vardas"), pavarde("pavarde"){ }
};

class Studentas1 : protected Base
{

  public:

   inline Studentas1() : Base{}, egz(0) { }
   inline ~Studentas1(){ }

    inline std::string getName() const {return vardas; };
    inline std::string getSurname() const { return pavarde; };
    virtual void setName(std::string);
    virtual void setSurname(std::string);

    void setExam(int);
    inline int getExam() const { return egz;};
    
      int n = 0;
      double galutinis;
      Vector<int> vektoriukas;
   
     Studentas1(const Studentas1& a)
      {
        vardas = a.vardas;
        pavarde = a.pavarde;
        egz = a.egz;
        vektoriukas.reserve(a.vektoriukas.size());
        std::copy(a.vektoriukas.begin(), a.vektoriukas.end(), std::back_inserter(vektoriukas));
        n = a.n;
        galutinis=a.galutinis;
      }

      Studentas1& operator = (const Studentas1& a)
      {    
	      	 if(&a==this) return *this;

           vardas = a.vardas;
           pavarde = a.pavarde;
           galutinis = a.galutinis;
           return *this;
      }

    inline friend bool operator >(const Studentas1& a, const Studentas1& b) { return a.galutinis > b.galutinis; }
    inline friend bool operator <(const Studentas1& a, const Studentas1& b) { return a.galutinis < b.galutinis; }
    inline friend bool operator >=(const Studentas1& a, const Studentas1& b) { return a.galutinis >= b.galutinis; }
    inline friend bool operator <=(const Studentas1& a, const Studentas1& b) { return a.galutinis <= b.galutinis; }
    inline friend bool operator ==(const Studentas1& a, const Studentas1& b) { return a.vardas == b.vardas && a.pavarde == b.pavarde && a.egz == b.egz &&
        a.n == b.n && a.galutinis == b.galutinis && a.vektoriukas == b.vektoriukas; }
    inline friend bool operator !=(const Studentas1& a, const Studentas1& b) { return !(a == b); }

    
    inline friend int operator + (const Studentas1& a, const Studentas1& b) { return a.egz + b.egz;} 
    inline friend int operator - (const Studentas1& a, const Studentas1& b) { return a.egz - b.egz;} 
    inline friend int operator * (const Studentas1& a, const Studentas1& b) { return a.egz * b.egz;}
    inline friend int operator / (const Studentas1& a, const Studentas1& b) { return a.egz / b.egz;}

  private:
      int egz; 

};


void konteineris (char& simbolis, char pirmas, char antras, char trecias);
void ar_tas_simboliukas (char& simbolis, char pirmas, char antras);
void ar_tinkamas_skaiciukas (int& skaicius, int pradzia, int pabaiga);
double rastimediana (Vector<int> vekt);
double vidurkis (int const* nd, int n);
double galutinis (char kas_cia1,  Studentas1& Studentas);
double galutinis_skaitant (char kas_cia1, Studentas1& Studentas,Vector<int> vektoriukas);
void pazymiu_generavimas ( Studentas1& Studentas);
bool rikiuojam( Studentas1& a, Studentas1& b);
void I_FAILA_pazymiu_generavimas ( Studentas1& Studentas, std::string pavadinimas, int kiek);
bool rikiuojam_pagal_bala( Studentas1& a,  Studentas1& b);
void vektorius();

#endif // ANTRASTE_VECTOR_H_INCLUDED
