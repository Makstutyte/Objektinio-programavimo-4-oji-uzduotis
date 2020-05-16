# Objektinio-programavimo-4-oji-uzduotis


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
| std::vector  |7.8209| 
| Vector | 7.65252 |
