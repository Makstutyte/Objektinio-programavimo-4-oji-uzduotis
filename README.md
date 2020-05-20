# Objektinio-programavimo-4-oji-uzduotis

 ## 5 skirtingų funkcijų pavyzdžiai:

* resize → funkcija, keičianti vektoriaus konteinerio dydi iki nurodyto elemento n. 
   * jei n yra mažiau už esamą vektoriaus dydį - šis yra sumažinamas iki pirmųjų n elementų, o elementai esantys už n yra pašalinami juos sunaikinant.
   * jei n yra daugiau už esamą vektoriaus dydį - būsimi elementai pridedami vektoriaus pabaigoje.
``` ruby
template <typename T>
void Vector<T>::resize(int n, T val)
{
    if (n > size()) 
    {
        int o = size();
        int z = n - size();
        avail += z;

        for (int i = o; i < n; i++) 
        {
            data1[i] = val;
        }
    }

    else resize(n);
}

```
Funkcijai paduodamos dvi reikšmės: n nurodo skaičių, iki kurio bus padidintas vektoriaus dydis, val nurodo, kokiomis reikšmėmis bus užpildomi naujai sukurti elementai.


* reserve → funkcija, padidinanti naudojamo vektoriaus talpą (capacity) skaičiumi n. Jeigu paduodamas n skaičius yra didesnis negu esama vekroiaus talpa (capacity), funkcijos metu vyksta naujos vietos alokavimas (allocation) bei elementų perkopijavimas taip padidinant vektoriaus talpą (capacity) iki nurodyto n dydžio. Funkcijai paduodamas norimo dydčio rodiklis. 
``` ruby
template<typename T>
void Vector<T>::reserve(int n) 
{
    int b = capacity();

    if (n > b)
    {
        size_type new_size = n;
       
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data1, avail, new_data);

        uncreate();
        data1 = new_data;
        avail = new_avail;
        limit = data1 + new_size;
    }
 }
 ```
 
 * clear → funkcija, pašalinanti visus vektoriaus konteineryje esančius elementus (juos sunaikinant) bei taip performuojant vektoriaus dydi lygu nuliui. Funkcijai parametrai nėra paduodami.
 ``` ruby
template <typename T>
void Vector<T>::clear() 
{
    resize(0);
}
```

* emplace → funkcija, išplėčianti vektoiaus konteinerį, įterpdama naują nurodytą elementą į nurodytą vietą. Įterpiant elementą į vektorių, šio dydyis yra padidinamas vienetu. Funkcijai yra paduodami du parametrai: 
    * vieta - nurodomas iteratorius, į kurią vietą reikia įterpti naują elementą;
    * reikšmė - nurodomas elementas, kuris bus įteroiamas į nurodytą vietą vektoriaus konteineryje.
``` ruby
template<typename T>
void Vector<T>::emplace(Vector<T>::const_iterator it, T args) 
{
        if ((it < data1) || (it > avail)) 
        {
          std::cout << "Throw exception" << std::endl;
        }
            int v = 0;

            for (auto a = begin(); a < it; a++) 
            {
                v++;
            }

    size_type new_size = (size() + 1);
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data1, avail+1, new_data);

    for(int i = 0; i< v; i++)
    {
        new_data[i] = data1[i];
    }

    new_data[v] = args;
    int z = v + 1;
    int g = size() + 1;

    for(int i = z; i< g; i++)
    {
        new_data[i] = data1[i-1];
    }
    
    uncreate();
    data1 = new_data;
    avail = new_avail;
    limit = data1 + new_size;
}
```
* shrink_to_fit → funkcija, sumažinanti vektoriaus konteineriui skirtą talpą (capacity), tai yra, sumažina vektoriui rezervuotą, tačiau nereikalingą, atmintį. Funkcijai parametrai nėra paduodami.
``` ruby
template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (avail < limit) 
    {
        limit = avail;
    }
}
```
## Spartos analizė
Efektyvumo/spartos analizė naudojant originalų std::vector ir sukurtą Vector konteinerius. Lyginama, kiek vidutiniškai laiko užtrunka  std::vector tipo ir Vector tipo tuščių vektorių užpildymas, naudojant push_back() funkciją:


|  Konteineris       | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
| ------------- | ------------- | ------------- | ------------- | ------------- | ------------- 
| std::vector  | 0s | 0.001995 |  0.01895 | 0.199508 | 2.11385 | 
| Vector | 0s | 0.002992 | 0.02294 | 0.238394 | 2.24057 |



Konteinerių (Vector ir std::vector) atminties perskirstymai užpildant 100000000 elementų. Perskirstymas įvyksta tada, kai yra patenkinama sąlyga: capacity() == size():


| Konteineris | Perskirstymai |
| ------------- | ------------- |  
| std::vector  | 27| 
| Vector | 27 |


Spartos analizė naudojant duomenų failą su 100000 studentų įrašų, lyginant kiek laiko užtrunka programos veikimas naudojant std::vector ir Vector realizacijas:

| Konteineris | 100000 | 
| ------------- | ------------- | 
| std::vector  |5.6258| 
| Vector | 5.4933 |


Matavimo įrangos parametrai:
| CPU | RAM | SSD |
| ------------- | ------------- | ------------- |
| Intel CORE i5 7th Gen 2.70 GHz | 8 GB  | 256 GB |

## Išvados

Dėl šventos ramybės - geriau naudoti std::vector. Sukurta Vector klasė funkcionalumo prasme nėra ganėtinai išdirbta, jog būtų patogi kasdienio naudojimo atžvilgiu. 
