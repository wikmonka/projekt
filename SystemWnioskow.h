#pragma once

#include "Zatrudnieni.h"
#include "Wniosek.h"
#include <iostream>

// Klasa odpowiedzialna za przetwarzanie wniosków z wykorzystaniem polimorfizmu
class SystemWnioskow {
public:
    // Metoda przyjmuje wskaŸnik do obiektu klasy bazowej i wywo³uje odpowiedni¹ wersjê metody obsluzWniosek
    void przetworz(Wniosek& wniosek, Zatrudnieni* uzytkownik) {
        if (uzytkownik) {
            std::cout << ">> Przetwarzanie wniosku przez u¿ytkownika: " << uzytkownik->getLogin() << std::endl;
            uzytkownik->obsluzWniosek(wniosek); // POLIMORFIZM: wywo³ywana metoda konkretnej klasy
        }
        else {
            std::cout << "B³¹d: nieprawid³owy u¿ytkownik (nullptr)" << std::endl;
        }
    }
};
