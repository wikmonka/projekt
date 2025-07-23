#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Wniosek.h"

class WniosekManager {
public:
    static void zapiszWniosek(const Wniosek& wniosek, const std::string& sciezka = "wnioski.txt") {
        std::ofstream plik(sciezka, std::ios::app); // dopisz na koñcu
        if (!plik) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku do zapisu: " << sciezka << "\n";
            return;
        }
        plik << wniosek.getLoginPracownika() << ";"
            << wniosek.getTyp() << ";"
            << wniosek.getTresc() << ";"
            << wniosek.getStatus() << "\n";
        plik.close();
    }

    static std::vector<Wniosek> wczytajWszystkie(const std::string& sciezka = "wnioski.txt") {
        std::vector<Wniosek> wnioski;
        std::ifstream plik(sciezka);
        if (!plik) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku do odczytu: " << sciezka << "\n";
            return wnioski;
        }

        std::string linia;
        while (std::getline(plik, linia)) {
            std::stringstream ss(linia);
            std::string login, typ, tresc, status;

            std::getline(ss, login, ';');
            std::getline(ss, typ, ';');
            std::getline(ss, tresc, ';');
            std::getline(ss, status, ';');

            wnioski.emplace_back(login, typ, tresc, status);
        }
        return wnioski;
    }

    // Prosty zapis wszystkich (np. po modyfikacji statusu)
    static void nadpiszWszystkie(const std::vector<Wniosek>& wnioski, const std::string& sciezka = "wnioski.txt") {
        std::ofstream plik(sciezka);
        if (!plik) {
            std::cerr << "[B£¥D] Nie mo¿na nadpisaæ pliku: " << sciezka << "\n";
            return;
        }

        for (const auto& w : wnioski) {
            plik << w.getLoginPracownika() << ";"
                << w.getTyp() << ";"
                << w.getTresc() << ";"
                << w.getStatus() << "\n";
        }
        plik.close();
    }
};
