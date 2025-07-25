#pragma once

#include <string>
#include "Pensja.h"
#include "Wniosek.h"
#include "KomunikatManager.h"
#include <iostream>

// Klasa bazowa dla wszystkich użytkowników systemu
class Zatrudnieni {
protected:
    std::string imie;
    std::string nazwisko;
    std::string stanowisko;
    std::string login;
    std::string haslo;
    Pensja* pensja;

public:
    Zatrudnieni() = default;

    // POPRAWIONY KONSTRUKTOR
    Zatrudnieni(const std::string& imie, const std::string& nazwisko,
        const std::string& stanowisko, const std::string& login,
        const std::string& haslo, Pensja* pensja)
        : imie(imie), nazwisko(nazwisko), stanowisko(stanowisko),
        login(login), haslo(haslo), pensja(pensja) {}

    virtual ~Zatrudnieni() = default;

    // Czysto wirtualna metoda – musi zostać zaimplementowana przez klasy pochodne
    virtual void obsluzWniosek(Wniosek& wniosek) = 0;

    // Gettery
    std::string getLogin() const { return login; }
    std::string getHaslo() const { return haslo; }
    std::string getImie() const { return imie; }
    std::string getNazwisko() const { return nazwisko; }
    std::string getStanowisko() const { return stanowisko; }

    // POPRAWIONY GETTER
    Pensja& getPensja() { return *pensja; }

    // Wirtualna metoda – może być przesłonięta, ale ma domyślną implementację
    virtual void pokazAktywnosc() {
        std::cout << "[AKTYWNOŚĆ] " << login << ": Zalogowano jako UŻYTKOWNIK BAZOWY.\n";
    }

    // Wyświetlanie komunikatów dla danego loginu (domyślna implementacja)
    virtual void wyswietlKomunikaty() {
        auto lista = KomunikatManager::wczytajWszystkie();
        std::cout << "\n== KOMUNIKATY SYSTEMOWE (GLOBALNE) ==\n";
        if (lista.empty()) {
            std::cout << "Brak nowych komunikatów.\n";
        }
        else {
            for (const auto& k : lista) {
                std::cout << "[" << k.data << "] " << k.tresc << "\n";
            }
        }
    }
};