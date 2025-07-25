#pragma once

#include <string>

// Klasa opisująca pojedynczy wniosek pracownika
class Wniosek {
private:
    std::string loginPracownika; // Login osoby składającej wniosek
    std::string typ;             // Typ wniosku (np. "delegacja", "urlop", "uprawnienia")
    std::string tresc;           // Szczegóły treści
    std::string status;          // Status (np. "oczekujący", "zatwierdzony", "odrzucony")

public:
    Wniosek() = default;

    Wniosek(const std::string& login, const std::string& typ,
        const std::string& tresc, const std::string& status = "oczekujący")
        : loginPracownika(login), typ(typ), tresc(tresc), status(status) {}

    // Gettery
    std::string getLoginPracownika() const { return loginPracownika; }
    std::string getTyp() const { return typ; }
    std::string getTresc() const { return tresc; }
    std::string getStatus() const { return status; }

    // Settery
    void ustawStatus(const std::string& nowyStatus) { status = nowyStatus; }
};

