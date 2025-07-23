#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

class Pensja {
private:
    std::string umowa = "UoP";      // Typ umowy: UoP, UZ, B2B
    double dni�wka = 100.0;         // Stawka za dzie� pracy
    double premia = 0.0;            // Premia dodatkowa
    double mnoznik = 1.0;           // Dodatkowy mno�nik stanowiskowy
    double minKwota = 0.0;          // Minimalna pensja dla danego stanowiska
    double maxKwota = 10000.0;      // Maksymalna pensja
    double stawkaPodatku = 0.17;    // Domy�lnie 17%
    int dniPracy = 0;

public:
    Pensja() = default;

    Pensja(const std::string& umowa,
        double dni�wka,
        double premia,
        double mnoznik,
        double minKwota,
        double maxKwota)
        : umowa(umowa), dni�wka(dni�wka), premia(premia),
        mnoznik(mnoznik), minKwota(minKwota), maxKwota(maxKwota)
    {
        ustawStawkePodatku();
    }

    void ustawStawkePodatku() {
        if (umowa == "UoP") stawkaPodatku = 0.17;
        else if (umowa == "UZ") stawkaPodatku = 0.12;
        else if (umowa == "B2B") stawkaPodatku = 0.19;
        else stawkaPodatku = 0.20; // warto�� domy�lna
    }

    double obliczWynagrodzenie() const {
        double kwotaBrutto = (dni�wka * dniPracy * mnoznik) + premia;

        if (kwotaBrutto < minKwota) {
            kwotaBrutto = minKwota;
        }

        if (kwotaBrutto > maxKwota) {
            kwotaBrutto = maxKwota;
        }

        double netto = kwotaBrutto * (1.0 - stawkaPodatku);
        return netto;
    }

    // Dni pracy
    void dodajDzienPracy() { dniPracy++; }
    void ustawDniPracy(int dni) { dniPracy = dni; }

    // Settery
    void ustawDni�wke(double nowa) { dni�wka = nowa; }
    void ustawPremie(double kwota) { premia = kwota; }
    void ustawMnoznik(double m) { mnoznik = m; }
    void ustawLimity(double minP, double maxP) { minKwota = minP; maxKwota = maxP; }
    void ustawUmowe(const std::string& nowa) {
        umowa = nowa;
        ustawStawkePodatku();
    }

    // Gettery
    std::string getUmowa() const { return umowa; }
    double getDni�wka() const { return dni�wka; }
    double getPremia() const { return premia; }
    double getMnoznik() const { return mnoznik; }
    double getMin() const { return minKwota; }
    double getMax() const { return maxKwota; }
    double getStawkaPodatku() const { return stawkaPodatku; }
    int getDniPracy() const { return dniPracy; }

    // Zapis do pliku
    void zapiszDoPliku(const std::string& login, std::ofstream& plik) const {
        plik << login << ";"
            << umowa << ";"
            << dni�wka << ";"
            << premia << ";"
            << mnoznik << ";"
            << minKwota << ";"
            << maxKwota << ";"
            << stawkaPodatku << ";"
            << dniPracy << "\n";
    }

    // Wczytaj z linii pliku
    static Pensja wczytajZLinii(const std::string& linia, std::string& loginOut) {
        std::stringstream ss(linia);
        std::string login, umowa;
        double dni�wka, premia, mnoznik, min, max, podatek;
        int dni;

        std::getline(ss, login, ';');
        std::getline(ss, umowa, ';');
        ss >> dni�wka; ss.ignore();
        ss >> premia; ss.ignore();
        ss >> mnoznik; ss.ignore();
        ss >> min; ss.ignore();
        ss >> max; ss.ignore();
        ss >> podatek; ss.ignore();
        ss >> dni;

        loginOut = login;

        Pensja p;
        p.umowa = umowa;
        p.dni�wka = dni�wka;
        p.premia = premia;
        p.mnoznik = mnoznik;
        p.minKwota = min;
        p.maxKwota = max;
        p.stawkaPodatku = podatek;
        p.dniPracy = dni;

        return p;
    }
};
