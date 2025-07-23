#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <limits>

namespace utils {

    // Zwraca aktualn¹ datê i godzinê w formacie YYYY-MM-DD HH:MM:SS
    inline std::string pobierzDateCzas() {
        time_t t = time(nullptr);
        struct tm local;
        char buf[20];

#ifdef _MSC_VER
        localtime_s(&local, &t);
#else
        local = *localtime(&t);
#endif

        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local);
        return std::string(buf);
    }

    // Wczytuje liczbê ca³kowit¹ z zabezpieczeniem przed b³êdami wejœcia
    inline int pobierzLiczbe(const std::string& prompt = "Wybierz opcjê: ") {
        int liczba;
        while (true) {
            std::cout << prompt;
            std::cin >> liczba;

            if (std::cin.fail()) {
                std::cin.clear(); // czyœci flagi b³êdu
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // usuwa b³êdny input
                std::cout << "B³¹d: wpisz liczbê ca³kowit¹.\n";
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // usuwa pozosta³oœci
                return liczba;
            }
        }
    }

}
