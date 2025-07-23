#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

class Pensja {
private:
    std::string umowa = "UoP";      // Typ umowy: UoP, UZ, B2B
    double dniówka = 100.0;         // Stawka za dzieñ pracy
    double premia = 0.0;            // Premia dodatkowa
    double mnoznik = 1.0;           // Dodatkowy mno¿nik stanowiskowy
    double minKwota = 0.0;          // Minimalna pensja dla danego stanowiska
    double maxKwota = 10000.0;      // Maksymalna pensja
    double stawkaPodatku = 0.17;    // Domyœlnie 17%
    int dniPracy = 0;

public:
    Pensja() = default;

    Pensja(const std::string& umowa,
        double dniówka,
        double premia,
        double mnoznik,
        double minKwota,
        double maxKwota)
        : umowa(umowa), dniówka(dniówka), premia(premia),
        mnoznik(mnoznik), minKwota(minKwota), maxKwota(maxKwota)
    {
        ustawStawkePodatku();
    }

    void ustawStawkePodatku() {
        if (umowa == "UoP") stawkaPodatku = 0.17;
        else if (umowa == "UZ") stawkaPodatku = 0.12;
        else if (umowa == "B2B") stawkaPodatku = 0.19;
        else stawkaPodatku = 0.20; // wartoœæ domyœlna
    }

    double obliczWynagrodzenie() const {
        double kwotaBrutto = (dniówka * dniPracy * mnoznik) + premia;

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
    void ustawDniówke(double nowa) { dniówka = nowa; }
    void ustawPremie(double kwota) { premia = kwota; }
    void ustawMnoznik(double m) { mnoznik = m; }
    void ustawLimity(double minP, double maxP) { minKwota = minP; maxKwota = maxP; }
    void ustawUmowe(const std::string& nowa) {
        umowa = nowa;
        ustawStawkePodatku();
    }

    // Gettery
    std::string getUmowa() const { return umowa; }
    double getDniówka() const { return dniówka; }
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
            << dniówka << ";"
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
        double dniówka, premia, mnoznik, min, max, podatek;
        int dni;

        std::getline(ss, login, ';');
        std::getline(ss, umowa, ';');
        ss >> dniówka; ss.ignore();
        ss >> premia; ss.ignore();
        ss >> mnoznik; ss.ignore();
        ss >> min; ss.ignore();
        ss >> max; ss.ignore();
        ss >> podatek; ss.ignore();
        ss >> dni;

        loginOut = login;

        Pensja p;
        p.umowa = umowa;
        p.dniówka = dniówka;
        p.premia = premia;
        p.mnoznik = mnoznik;
        p.minKwota = min;
        p.maxKwota = max;
        p.stawkaPodatku = podatek;
        p.dniPracy = dni;

        return p;
    }
};
