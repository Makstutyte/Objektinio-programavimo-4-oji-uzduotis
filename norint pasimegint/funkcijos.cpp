#include "antraste_vector.h"
#include "Timer.h"

void konteineris (char& simbolis, char pirmas, char antras, char trecias)
{
    while (!(simbolis == pirmas || simbolis == antras || simbolis == trecias))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Ivestas netinkamas dydis" <<std::endl;
        std::cout << "Pasirinkite viena is variantu arba " << pirmas << " arba " << antras  << " arba " << trecias << ": ";
        std::cin >> simbolis;
    }
}

/// funkcija patikrinanti ar vartotojo ivesti duomenys (siuo atveju simbolis) yra tinkamo formato
void ar_tas_simboliukas (char& simbolis, char pirmas, char antras)
{
    while (!(simbolis == pirmas || simbolis == antras))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Ivestas netinkamas dydis" <<std::endl;
        std::cout << "Pasirinkite viena is variantu arba " << pirmas << " arba " << antras << ": ";
        std::cin >> simbolis;
    }
}

/// funkcija patikrinanti ar vartotojo ivesti duomenys (siuo atveju skaiciai) yra tinkamo formato
void ar_tinkamas_skaiciukas (int& skaicius, int pradzia, int pabaiga)
{
    while (std::cin.fail() || skaicius < pradzia || skaicius > pabaiga)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Ivestas netinkamas dydis" <<std::endl;
        std::cout << "Pasirinkite skaiciu is intervalo nuo" << pradzia << " iki " << pabaiga << ": ";
        std::cin >> skaicius;
    }
}

