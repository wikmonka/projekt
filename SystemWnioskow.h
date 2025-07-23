#pragma once

#include "Zatrudnieni.h"
#include "Wniosek.h"
#include <iostream>

// Klasa odpowiedzialna za przetwarzanie wniosk�w z wykorzystaniem polimorfizmu
class SystemWnioskow {
public:
    // Metoda przyjmuje wska�nik do obiektu klasy bazowej i wywo�uje odpowiedni� wersj� metody obsluzWniosek
    void przetworz(Wniosek& wniosek, Zatrudnieni* uzytkownik) {
        if (uzytkownik) {
            std::cout << ">> Przetwarzanie wniosku przez u�ytkownika: " << uzytkownik->getLogin() << std::endl;
            uzytkownik->obsluzWniosek(wniosek); // POLIMORFIZM: wywo�ywana metoda konkretnej klasy
        }
        else {
            std::cout << "B��d: nieprawid�owy u�ytkownik (nullptr)" << std::endl;
        }
    }
};
