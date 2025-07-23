// === main.cpp ===
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include "Zatrudnieni.h"
#include "Pracownik.h"
#include "Kadry.h"
#include "Administrator.h"
#include "LogikaSystemu.h"
#include "SystemWnioskow.h"
#include "FileLoader.h"
#include "PensjaManager.h"
#include <windows.h>

int main() {

	SetConsoleCP(1250); // Ustawienie kodowania konsoli na CP1250
	SetConsoleOutputCP(1250); // Ustawienie kodowania konsoli na CP1250

    std::vector<std::unique_ptr<Zatrudnieni>> uzytkownicy;
    std::map<std::string, Pensja> bazaPensji = PensjaManager::wczytajPensje();

    FileLoader::zaladujUzytkownikow("uzytkownicy.txt", uzytkownicy, bazaPensji);

    SystemWnioskow system;
    LogikaSystemu logika;

    int wybor;
    do {
        std::cout << "\n=== SYSTEM ZARZADZANIA PRACOWNIKAMI ===\n";
        std::cout << "1. Zaloguj siê\n";
        std::cout << "2. Wyjœcie\n";
        wybor = utils::pobierzLiczbe("Wybór: ");

        if (wybor == 1) {
            Zatrudnieni* zalogowany = logika.logowanie(uzytkownicy);
            if (!zalogowany) continue;

            if (auto* p = dynamic_cast<Pracownik*>(zalogowany))
                logika.menuPracownika(p, system);
            else if (auto* a = dynamic_cast<Administrator*>(zalogowany))
                logika.menuAdmin(a, system);
            else {
                Kadry* kadry = nullptr;
                for (const auto& u : uzytkownicy) {
                    if (auto* k = dynamic_cast<Kadry*>(u.get())) {
                        kadry = k;
                        break;
                    }
                }
                if (kadry)
                    logika.menuKadry(kadry, system, uzytkownicy);
                else
                    std::cout << "[B£¥D] Nie znaleziono obiektu kadry.\n";
            }
        }
    } while (wybor != 2);

    std::cout << "Zamykanie programu...\n";

    // zapis aktualnych pensji do pliku
    PensjaManager::zapiszPensje(bazaPensji);

    return 0;
}
