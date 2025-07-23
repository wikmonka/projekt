#pragma once

#include "Zatrudnieni.h"
#include "ZadanieManager.h"
#include <string>
#include <iostream>

class Pracownik : public Zatrudnieni {
private:
    std::string umowa;

public:
    Pracownik() = default;

    Pracownik(const std::string& imie, const std::string& nazwisko,
        const std::string& stanowisko, const std::string& login,
        const std::string& haslo, Pensja* pensja,
        const std::string& umowa)
        : Zatrudnieni(imie, nazwisko, stanowisko, login, haslo, pensja), umowa(umowa) {}

    void obsluzWniosek(Wniosek& wniosek) override {
        wniosek.ustawStatus("oczekuj¹cy");
        std::cout << "[PRACOWNIK] Wniosek zosta³ wys³any i oczekuje na zatwierdzenie.\n";
    }

    void dodajDzienPracy() {
        pensja->dodajDzienPracy();
        std::cout << "[INFO] Dodano jeden dzieñ pracy.\n";
    }

    void wyswietlZadania() const {
        auto lista = ZadanieManager::wczytajDla(login);
        std::cout << "\n== TWOJE ZADANIA ==\n";
        if (lista.empty()) {
            std::cout << "Brak przypisanych zadañ.\n";
        }
        else {
            for (const auto& z : lista) {
                std::cout << "[" << z.data << "] " << z.tresc << "\n";
            }
        }
    }

    // --- POPRAWKA ---
    // Wersja pozwalaj¹ca na modyfikacjê pensji
    Pensja& getPensja() { return *pensja; }
    // Wersja tylko do odczytu (dla sta³ych obiektów)
    const Pensja& getPensja() const { return *pensja; }
    // --- KONIEC POPRAWKI ---

    void pokazAktywnosc() override {
        std::cout << "[AKTYWNOŒÆ] " << login << ": Zalogowano jako PRACOWNIK.\n";
    }
};