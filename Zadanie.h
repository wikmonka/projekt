#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

// Struktura reprezentuj�ca pojedyncze zadanie lub komunikat
struct Zadanie {
    std::string loginOdbiorcy;  // Login pracownika, kt�ry ma otrzyma� zadanie
    std::string tresc;          // Tre�� zadania lub komunikatu
    std::string data;           // Data dodania

    Zadanie(const std::string& login, const std::string& tresc)
        : loginOdbiorcy(login), tresc(tresc) {
        // Automatyczna data systemowa
        time_t t = time(nullptr);
        data = std::string(ctime(&t)); // Zawiera \n na ko�cu
    }

    void wypisz() const {
        std::cout << "[" << data << "] Do: " << loginOdbiorcy << "\nTre��: " << tresc << "\n";
    }
};
