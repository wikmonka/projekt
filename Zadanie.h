#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

// Struktura reprezentuj¹ca pojedyncze zadanie lub komunikat
struct Zadanie {
    std::string loginOdbiorcy;  // Login pracownika, który ma otrzymaæ zadanie
    std::string tresc;          // Treœæ zadania lub komunikatu
    std::string data;           // Data dodania

    Zadanie(const std::string& login, const std::string& tresc)
        : loginOdbiorcy(login), tresc(tresc) {
        // Automatyczna data systemowa
        time_t t = time(nullptr);
        data = std::string(ctime(&t)); // Zawiera \n na koñcu
    }

    void wypisz() const {
        std::cout << "[" << data << "] Do: " << loginOdbiorcy << "\nTreœæ: " << tresc << "\n";
    }
};
