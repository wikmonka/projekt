#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>
#include "Zatrudnieni.h"
#include "Pracownik.h"
#include "Kadry.h"
#include "Administrator.h"
#include "Pensja.h"

class FileLoader {
public:
    static void zaladujUzytkownikow(const std::string& sciezka,
        std::vector<std::unique_ptr<Zatrudnieni>>& uzytkownicy,
        std::map<std::string, Pensja>& pensje) {
        std::ifstream plik(sciezka);
        if (!plik.is_open()) {
            std::cerr << "[B£¥D] Nie mo¿na otworzyæ pliku: " << sciezka << "\n";
            return;
        }

        std::string linia;
        while (std::getline(plik, linia)) {
            std::stringstream ss(linia);
            std::string typ, imie, nazwisko, stanowisko, login, haslo, umowa;
            std::string tmp;
            double podstawa, mnoznik, premia, min, max;

            std::getline(ss, typ, ';');
            std::getline(ss, imie, ';');
            std::getline(ss, nazwisko, ';');
            std::getline(ss, stanowisko, ';');
            std::getline(ss, login, ';');
            std::getline(ss, haslo, ';');
            std::getline(ss, umowa, ';');
            std::getline(ss, tmp, ';'); podstawa = std::stod(tmp);
            std::getline(ss, tmp, ';'); mnoznik = std::stod(tmp);
            std::getline(ss, tmp, ';'); premia = std::stod(tmp);
            std::getline(ss, tmp, ';'); min = std::stod(tmp);
            std::getline(ss, tmp, ';'); max = std::stod(tmp);

            // stwórz lub zaktualizuj pensjê
            pensje[login] = Pensja(umowa, podstawa, premia, mnoznik, min, max);

            if (typ == "Pracownik") {
                Pensja& ref = pensje[login];
                uzytkownicy.push_back(std::make_unique<Pracownik>(
                    imie, nazwisko, stanowisko, login, haslo, ref, umowa));
            }
            else if (typ == "Kadry") {
                uzytkownicy.push_back(std::make_unique<Kadry>(
                    imie, nazwisko, stanowisko, login, haslo, pensje[login]));
            }
            else if (typ == "Administrator") {
                uzytkownicy.push_back(std::make_unique<Administrator>(
                    imie, nazwisko, stanowisko, login, haslo, pensje[login]));
            }
        }

        std::cout << "[INFO] Za³adowano u¿ytkowników z pliku: " << sciezka << "\n";
    }
};
