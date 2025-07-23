#pragma once

#include "Zatrudnieni.h"
#include "Pracownik.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Klasa reprezentuj¹ca administratora systemu
class Administrator : public Zatrudnieni {
public:
    Administrator() = default;

    Administrator(const std::string& imie, const std::string& nazwisko,
        const std::string& stanowisko, const std::string& login,
        const std::string& haslo, const Pensja& pensja)
        : Zatrudnieni(imie, nazwisko, stanowisko, login, haslo, pensja) {}

    void obsluzWniosek(Wniosek& wniosek) override {
        if (wniosek.getTyp() == "uprawnienia") {
            wniosek.ustawStatus("zatwierdzony");
            std::cout << "[ADMIN] Wniosek o uprawnienia zosta³ zatwierdzony.\n";
        }
        else {
            wniosek.ustawStatus("przekazano do kadr");
            std::cout << "[ADMIN] Wniosek przekazano do dzia³u kadr.\n";
        }
    }

    void dodajPracownika(std::vector<Pracownik>& pracownicy, const Pracownik& nowy) {
        pracownicy.push_back(nowy);
        std::cout << "[ADMIN] Dodano nowego pracownika: " << nowy.getLogin() << "\n";
    }

    void usunPracownika(std::vector<Pracownik>& pracownicy, const std::string& login) {
        auto it = std::remove_if(pracownicy.begin(), pracownicy.end(),
            [&](const Pracownik& p) { return p.getLogin() == login; });

        if (it != pracownicy.end()) {
            pracownicy.erase(it, pracownicy.end());
            std::cout << "[ADMIN] Usuniêto pracownika: " << login << "\n";
        }
        else {
            std::cout << "[ADMIN] Nie znaleziono pracownika o loginie: " << login << "\n";
        }
    }

    void pokazAktywnosc() override {
        std::cout << "[AKTYWNOŒÆ] " << login << ": Zalogowano jako ADMINISTRATOR.\n";
    }
};
