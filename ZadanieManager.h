#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "utils.h"

// Struktura pojedynczego zadania
struct Zadanie {
    std::string loginOdbiorcy;
    std::string tresc;
    std::string data;
};

class ZadanieManager {
public:
    static void zapiszZadanie(const std::string& login, const std::string& tresc,
        const std::string& sciezka = "zadania.txt") {
        std::ofstream plik(sciezka, std::ios::app);
        if (!plik) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku zadañ do zapisu.\n";
            return;
        }

        std::string data = utils::pobierzDateCzas();
        plik << login << ";" << tresc << ";" << data << "\n";
    }

    static std::vector<Zadanie> wczytajDla(const std::string& login,
        const std::string& sciezka = "zadania.txt") {
        std::vector<Zadanie> lista;
        std::ifstream plik(sciezka);
        if (!plik) return lista;

        std::string linia;
        while (std::getline(plik, linia)) {
            std::stringstream ss(linia);
            std::string log, tresc, data;

            std::getline(ss, log, ';');
            std::getline(ss, tresc, ';');
            std::getline(ss, data, ';');

            if (log == login) {
                lista.push_back({ log, tresc, data });
            }
        }

        return lista;
    }
};
