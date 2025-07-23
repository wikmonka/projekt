#pragma once

#include <string>
#include "Pensja.h"
#include "Wniosek.h"
#include "KomunikatManager.h"
#include <iostream>

// Klasa bazowa dla wszystkich u¿ytkowników systemu
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

    // Czysto wirtualna metoda – musi zostaæ zaimplementowana przez klasy pochodne
    virtual void obsluzWniosek(Wniosek& wniosek) = 0;

    // Gettery
    std::string getLogin() const { return login; }
    std::string getHaslo() const { return haslo; }
    std::string getImie() const { return imie; }
    std::string getNazwisko() const { return nazwisko; }
    std::string getStanowisko() const { return stanowisko; }

    // POPRAWIONY GETTER
    Pensja& getPensja() { return *pensja; }

    // Wirtualna metoda – mo¿e byæ przes³oniêta, ale ma domyœln¹ implementacjê
    virtual void pokazAktywnosc() {
        std::cout << "[AKTYWNOŒÆ] " << login << ": Zalogowano jako U¯YTKOWNIK BAZOWY.\n";
    }

    // Wyœwietlanie komunikatów dla danego loginu (domyœlna implementacja)
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