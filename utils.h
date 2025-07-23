#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <limits>

namespace utils {

    // Zwraca aktualn� dat� i godzin� w formacie YYYY-MM-DD HH:MM:SS
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

    // Wczytuje liczb� ca�kowit� z zabezpieczeniem przed b��dami wej�cia
    inline int pobierzLiczbe(const std::string& prompt = "Wybierz opcj�: ") {
        int liczba;
        while (true) {
            std::cout << prompt;
            std::cin >> liczba;

            if (std::cin.fail()) {
                std::cin.clear(); // czy�ci flagi b��du
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // usuwa b��dny input
                std::cout << "B��d: wpisz liczb� ca�kowit�.\n";
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // usuwa pozosta�o�ci
                return liczba;
            }
        }
    }

}
