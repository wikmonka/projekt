#pragma once

#include <string>

// Klasa opisuj�ca pojedynczy wniosek pracownika
class Wniosek {
private:
    std::string loginPracownika; // Login osoby sk�adaj�cej wniosek
    std::string typ;             // Typ wniosku (np. "delegacja", "urlop", "uprawnienia")
    std::string tresc;           // Szczeg�y tre�ci
    std::string status;          // Status (np. "oczekuj�cy", "zatwierdzony", "odrzucony")

public:
    Wniosek() = default;

    Wniosek(const std::string& login, const std::string& typ,
        const std::string& tresc, const std::string& status = "oczekuj�cy")
        : loginPracownika(login), typ(typ), tresc(tresc), status(status) {}

    // Gettery
    std::string getLoginPracownika() const { return loginPracownika; }
    std::string getTyp() const { return typ; }
    std::string getTresc() const { return tresc; }
    std::string getStatus() const { return status; }

    // Settery
    void ustawStatus(const std::string& nowyStatus) { status = nowyStatus; }
};

