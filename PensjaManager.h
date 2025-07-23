#pragma once

#include "Pensja.h"
#include <map>
#include <fstream>
#include <iostream>

class PensjaManager {
public:
    // Wczytuje wszystkie pensje z pliku i przypisuje login -> Pensja
    static std::map<std::string, Pensja> wczytajPensje(const std::string& sciezka = "pensje.txt") {
        std::map<std::string, Pensja> mapa;
        std::ifstream plik(sciezka);
        if (!plik.is_open()) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku pensji do odczytu.\n";
            return mapa;
        }

        std::string linia;
        while (std::getline(plik, linia)) {
            std::string login;
            Pensja p = Pensja::wczytajZLinii(linia, login);
            mapa[login] = p;
        }

        return mapa;
    }

    // Zapisuje wszystkie pensje do pliku (login -> pensja)
    static void zapiszPensje(const std::map<std::string, Pensja>& dane,
        const std::string& sciezka = "pensje.txt") {
        std::ofstream plik(sciezka);
        if (!plik.is_open()) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku pensji do zapisu.\n";
            return;
        }

        for (const auto& [login, pensja] : dane) {
            pensja.zapiszDoPliku(login, plik);
        }

        std::cout << "[INFO] Zapisano pensje do pliku.\n";
    }
};
