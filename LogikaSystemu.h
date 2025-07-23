#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Zatrudnieni.h"
#include "Pracownik.h"
#include "Kadry.h"
#include "Administrator.h"
#include "SystemWnioskow.h"
#include "Wniosek.h"
#include "WniosekManager.h"
#include "KomunikatManager.h"
#include "ZadanieManager.h"
#include "utils.h"

class LogikaSystemu {
public:
    Zatrudnieni* logowanie(const std::vector<std::unique_ptr<Zatrudnieni>>& uzytkownicy) {
        std::string login, haslo;
        std::cout << "\n=== LOGOWANIE ===\n";
        std::cout << "Login: ";
        std::cin >> login;
        std::cout << "Has�o: ";
        std::cin >> haslo;

        for (const auto& u : uzytkownicy) {
            if (u->getLogin() == login && u->getHaslo() == haslo) {
                std::cout << "Zalogowano pomy�lnie jako: " << login << "\n";
                u->wyswietlKomunikaty();
                u->pokazAktywnosc();
                return u.get();
            }
        }

        std::cout << "B��d: nieprawid�owy login lub has�o.\n";
        return nullptr;
    }

    void menuPracownika(Pracownik* pracownik, SystemWnioskow& system) {
        int wybor;
        do {
            std::cout << "\n=== MENU PRACOWNIKA ===\n";
            std::cout << "1. Wy�wietl zadania\n";
            std::cout << "2. Z�� wniosek\n";
            std::cout << "3. Sprawd� pensj�\n";
            std::cout << "4. Cofnij\n";
            std::cout << "5. Dodaj odbicie dnia\n";
            wybor = utils::pobierzLiczbe("Wyb�r: ");

            if (wybor == 1) {
                pracownik->wyswietlZadania();
            }
            else if (wybor == 2) {
                std::string typ, tresc;
                std::cin.ignore();
                std::cout << "Typ wniosku: ";
                std::getline(std::cin, typ);
                std::cout << "Tre�� wniosku: ";
                std::getline(std::cin, tresc);

                Wniosek w(pracownik->getLogin(), typ, tresc);
                system.przetworz(w, pracownik);
                WniosekManager::zapiszWniosek(w);
            }
            else if (wybor == 3) {
                std::cout << "[INFO] Pensja netto: " << pracownik->getPensja().obliczWynagrodzenie() << " PLN\n";
            }
            else if (wybor == 5) {
                pracownik->dodajDzienPracy();
            }

        } while (wybor != 4);
    }

    void menuKadry(Kadry* kadry, SystemWnioskow& system, const std::vector<std::unique_ptr<Zatrudnieni>>& uzytkownicy) {
        int wybor;
        do {
            std::cout << "\n=== MENU KADR ===\n";
            std::cout << "1. Przetw�rz pierwszy oczekuj�cy wniosek\n";
            std::cout << "2. Dodaj zadanie pracownikowi\n";
            std::cout << "3. Zmie� dni�wk� pracownika\n";
            std::cout << "4. Dodaj premi� pracownikowi\n";
            std::cout << "5. Ustaw limity pensji\n";
            std::cout << "6. Poka� szczeg�y pensji pracownika\n";
            std::cout << "7. Cofnij\n";

            wybor = utils::pobierzLiczbe("Wyb�r: ");

            if (wybor == 1) {
                auto lista = WniosekManager::wczytajWszystkie();
                bool znaleziono = false;
                for (auto& w : lista) {
                    if (w.getStatus() == "oczekuj�cy") {
                        system.przetworz(w, kadry);
                        znaleziono = true;
                        break;
                    }
                }
                if (!znaleziono)
                    std::cout << "Brak oczekuj�cych wniosk�w.\n";

                WniosekManager::nadpiszWszystkie(lista);
            }
            else if (wybor == 2) {
                std::cin.ignore();
                std::string login, tresc;
                std::cout << "Login pracownika: ";
                std::getline(std::cin, login);
                std::cout << "Tre�� zadania: ";
                std::getline(std::cin, tresc);
                ZadanieManager::zapiszZadanie(login, tresc);
                std::cout << "[KADRY] Zadanie zapisane.\n";
            }
            else if (wybor >= 3 && wybor <= 6) {
                std::cin.ignore();
                std::string login;
                std::cout << "Login pracownika: ";
                std::getline(std::cin, login);

                // Znajd� pracownika na li�cie
                Pracownik* wybrany = nullptr;
                for (const auto& u : uzytkownicy) {
                    if (auto* p = dynamic_cast<Pracownik*>(u.get())) {
                        if (p->getLogin() == login) {
                            wybrany = p;
                            break;
                        }
                    }
                }

                if (!wybrany) {
                    std::cout << "[B��D] Nie znaleziono pracownika o loginie: " << login << "\n";
                    continue;
                }

                if (wybor == 3) {
                    double nowa;
                    std::cout << "Nowa dni�wka: ";
                    std::cin >> nowa;
                    kadry->zmienPodstawePensji(*wybrany, nowa);
                }
                else if (wybor == 4) {
                    double kwota;
                    std::cout << "Kwota premii: ";
                    std::cin >> kwota;
                    kadry->dodajPremie(*wybrany, kwota);
                }
                else if (wybor == 5) {
                    double min, max;
                    std::cout << "Minimalna pensja: ";
                    std::cin >> min;
                    std::cout << "Maksymalna pensja: ";
                    std::cin >> max;
                    kadry->ustawLimity(*wybrany, min, max);
                }
                else if (wybor == 6) {
                    kadry->pokazPensjePracownika(*wybrany);
                }
            }

        } while (wybor != 7);
    }


    void menuAdmin(Administrator* admin, SystemWnioskow& system) {
        int wybor;
        do {
            std::cout << "\n=== MENU ADMINISTRATORA ===\n";
            std::cout << "1. Przetw�rz pierwszy wniosek o uprawnienia\n";
            std::cout << "2. Cofnij\n";
            std::cout << "3. Wy�lij komunikat globalny\n";
            std::cout << "4. Dodaj zadanie pracownikowi\n";
            wybor = utils::pobierzLiczbe("Wyb�r: ");

            if (wybor == 1) {
                auto lista = WniosekManager::wczytajWszystkie();
                bool znaleziono = false;
                for (auto& w : lista) {
                    if (w.getTyp() == "uprawnienia" && w.getStatus() == "oczekuj�cy") {
                        system.przetworz(w, admin);
                        znaleziono = true;
                        break;
                    }
                }
                if (!znaleziono)
                    std::cout << "Brak oczekuj�cych wniosk�w o uprawnienia.\n";

                WniosekManager::nadpiszWszystkie(lista);
            }
            else if (wybor == 3) {
                std::cin.ignore();
                std::string tresc;
                std::cout << "Tre�� komunikatu (globalnego): ";
                std::getline(std::cin, tresc);
                KomunikatManager::zapiszKomunikat(tresc);
                std::cout << "[ADMIN] Komunikat zosta� zapisany.\n";
            }
            else if (wybor == 4) {
                std::cin.ignore();
                std::string login, tresc;
                std::cout << "Login pracownika: ";
                std::getline(std::cin, login);
                std::cout << "Tre�� zadania: ";
                std::getline(std::cin, tresc);
                ZadanieManager::zapiszZadanie(login, tresc);
                std::cout << "[ADMIN] Zadanie zosta�o zapisane do pliku.\n";
            }

        } while (wybor != 2);
    }
};
