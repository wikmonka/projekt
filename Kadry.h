#pragma once

#include "Zatrudnieni.h"
#include "Pracownik.h"
#include <iostream>

class Kadry : public Zatrudnieni {
public:
    Kadry() = default;

    Kadry(const std::string& imie, const std::string& nazwisko,
        const std::string& stanowisko, const std::string& login,
        const std::string& haslo, const Pensja& pensja)
        : Zatrudnieni(imie, nazwisko, stanowisko, login, haslo, pensja) {}

    void obsluzWniosek(Wniosek& wniosek) override {
        wniosek.ustawStatus("zatwierdzony");
        std::cout << "[KADRY] Wniosek zosta³ zatwierdzony automatycznie.\n";
    }

    void zmienPodstawePensji(Pracownik& pracownik, double nowaPodstawa) {
        pracownik.getPensja().ustawDniówke(nowaPodstawa);
        std::cout << "[KADRY] Zmieniono stawkê dniówki na " << nowaPodstawa << " PLN\n";
    }

    void dodajPremie(Pracownik& pracownik, double kwota) {
        pracownik.getPensja().ustawPremie(kwota);
        std::cout << "[KADRY] Dodano premiê: " << kwota << " PLN\n";
    }

    void ustawLimity(Pracownik& pracownik, double min, double max) {
        pracownik.getPensja().ustawLimity(min, max);
        std::cout << "[KADRY] Ustawiono zakres wynagrodzenia: " << min << " - " << max << " PLN\n";
    }

    void pokazPensjePracownika(Pracownik& pracownik) {
        const Pensja& p = pracownik.getPensja();
        std::cout << "\n== DANE PENSJI ==\n";
        std::cout << "Umowa: " << p.getUmowa() << "\n";
        std::cout << "Dniówka: " << p.getDniówka() << "\n";
        std::cout << "Premia: " << p.getPremia() << "\n";
        std::cout << "Mno¿nik: " << p.getMnoznik() << "\n";
        std::cout << "Limity: " << p.getMin() << " - " << p.getMax() << "\n";
        std::cout << "Podatek: " << (p.getStawkaPodatku() * 100) << " %\n";
        std::cout << "Dni pracy: " << p.getDniPracy() << "\n";
        std::cout << "Pensja NETTO: " << p.obliczWynagrodzenie() << " PLN\n";
    }

    void pokazAktywnosc() override {
        std::cout << "[AKTYWNOŒÆ] " << login << ": Zalogowano jako KADRY.\n";
    }
};
