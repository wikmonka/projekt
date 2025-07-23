#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "utils.h"

// Komunikaty globalne – bez loginu odbiorcy
struct Komunikat {
    std::string tresc;
    std::string data;
};

class KomunikatManager {
public:
    static void zapiszKomunikat(const std::string& tresc,
        const std::string& sciezka = "komunikaty.txt") {
        std::ofstream plik(sciezka, std::ios::app);
        if (!plik) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku komunikatów do zapisu.\n";
            return;
        }

        std::string data = utils::pobierzDateCzas();
        plik << tresc << ";" << data << "\n";
    }

    static std::vector<Komunikat> wczytajWszystkie(const std::string& sciezka = "komunikaty.txt") {
        std::vector<Komunikat> lista;
        std::ifstream plik(sciezka);
        if (!plik) return lista;

        std::string linia;
        while (std::getline(plik, linia)) {
            std::stringstream ss(linia);
            std::string tresc, data;

            std::getline(ss, tresc, ';');
            std::getline(ss, data, ';');

            lista.push_back({ tresc, data });
        }

        return lista;
    }
};
