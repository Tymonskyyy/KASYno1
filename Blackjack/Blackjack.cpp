#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Zmienne globalne
string g_imie_gracza = "Gracz";
string g_nazwisko_gracza = "Testowy";
int g_saldo = 0;

void showmenu() {
    system("cls");
    cout << "Centrum gier" << endl;
    cout << "----------" << endl;
    cout << "1. Blackjack" << endl;
    cout << "2. War" << endl;
    cout << "3. Poker" << endl;
    cout << "4. Wyjscie" << endl;
}

void show_bank_menu() {
    system("cls");
    cout << "=== BANK ===" << endl;
    cout << "1. Wplacic" << endl;
    cout << "2. Wyplacic" << endl;
    cout << "3. Stan Konta" << endl;
    cout << "0. WROC DO GRY" << endl;
}

void show_bank_saldo() {
    cout << "Imie i nazwisko: " << g_imie_gracza << " " << g_nazwisko_gracza << endl;
    cout << "SALDO: " << g_saldo << " PLN" << endl;
}

void Wplac() {
    int kwota = 0;
    cout << "Podaj ile chcesz wplacic: ";
    cin >> kwota;
    if (kwota < 0) {
        cout << "Blad: kwota ujemna" << endl;
        system("pause");
    }
    else {
        g_saldo += kwota;
        cout << "Sukces! Wplacono: " << kwota << " PLN" << endl;
        system("pause");
    }
}

void Wyplac() {
    int kwota1 = 0;
    cout << "Twoje saldo: " << g_saldo << endl;
    cout << "Ile chcesz wyplacic (0 - anuluj): ";
    cin >> kwota1;

    if (kwota1 == 0) return;

    if (kwota1 > g_saldo) {
        cout << "Blad: brak srodkow" << endl;
        system("pause");
    }
    else {
        g_saldo -= kwota1;
        cout << "Wyplacono: " << kwota1 << endl;
        cout << "Twoje saldo: " << g_saldo << endl;
        system("pause");
    }
}

void Bank() {
    int bank_deccision = 0;
    do {
        show_bank_menu();
        cout << "Wybierz opcje: ";
        cin >> bank_deccision;

        switch (bank_deccision) {
        case 1: Wplac(); break;
        case 2: Wyplac(); break;
        case 3: show_bank_saldo(); system("pause"); break;
        case 0: return; // Wyjście z banku
        default: cout << "Nie ma takiej opcji" << endl; system("pause");
        }
    } while (bank_deccision != 0);
}

int rozgrywka_blackjack() {
    srand(time(NULL));
    char chce_grac; // Zmienna do decyzji o powtórce

    do {
        // 1. RESETOWANIE PUNKTÓW (To musi byc wewnatrz petli!)
        int gracz = 0;
        int komputer = 0;
        char decyzja;

        system("cls");
        cout << "--- GRA W OCZKO ---" << endl;

        // 2. Sprawdzenie konta i ewentualnie Bank
        if (g_saldo == 0) {
            cout << "Masz puste konto!" << endl;
            cout << "Czy chcesz isc do banku? (t/n): ";
            char ryzyko;
            cin >> ryzyko;

            if (ryzyko == 't' || ryzyko == 'T') {
                Bank();
            }
            else {
                return 0; // Wyjscie do menu glownego
            }
        }

        // Jesli po banku nadal 0, to przerywamy tę rundę
        if (g_saldo == 0) {
            cout << "Brak srodkow. Nie mozesz grac." << endl;
            system("pause");
            return 0;
        }

        // 3. Pobranie zakładu
        int k_zakladu = 0;
        cout << "Twoje saldo: " << g_saldo << endl;
        cout << "Za ile chcesz zagrac? ";
        cin >> k_zakladu;

        if (k_zakladu > g_saldo) {
            cout << "Nie masz tyle pieniedzy!" << endl;
            system("pause");
            // Nie przerywamy programu, tylko wracamy do pytania "czy jeszcze raz"
            // Ale zeby bylo logicznie, ustawiamy, zeby nie pytal o gre, tylko pętla sie przekreci
            // W tym prostym kodzie najlatwiej po prostu zapytac:
            cout << "Sprobuj mniejsza stawke nastepnym razem." << endl;
        }
        else {
            // GRA WŁAŚCIWA
            g_saldo -= k_zakladu;

            // Ruch Gracza
            do {
                system("cls");
                int karta = rand() % 10 + 2;
                gracz += karta;

                cout << "Stawka: " << k_zakladu << endl;
                cout << "Wylosowales: " << karta << ". Masz razem: " << gracz << endl;

                if (gracz > 21) {
                    cout << "PRZEGRALES! (Masz > 21)" << endl;
                    break; // Przerywa dobieranie kart
                }
                if (gracz == 21) {
                    cout << "OCZKO! (21)" << endl;
                    break; // Przerywa dobieranie kart
                }

                cout << "Czy chcesz dobrac karte (t/n)? ";
                cin >> decyzja;
            } while (decyzja == 'T' || decyzja == 't');

            // Rozstrzygniecie (tylko jesli gracz nie spalil od razu > 21)
            if (gracz <= 21) {
                cout << "\nRuch krupiera..." << endl;
                while (komputer < 17) {
                    komputer += rand() % 10 + 2;
                }
                cout << "Krupier ma: " << komputer << endl;

                if (komputer > 21) {
                    cout << "WYGRALES! Krupier > 21." << endl;
                    g_saldo += (k_zakladu * 2);
                }
                else if (gracz > komputer) {
                    cout << "WYGRALES! Masz wiecej." << endl;
                    g_saldo += (k_zakladu * 2);
                }
                else if (gracz == komputer) {
                    cout << "REMIS." << endl;
                    g_saldo += k_zakladu;
                }
                else {
                    cout << "PRZEGRALES." << endl;
                }
            }
            else {
                // Tu wchodzi jesli gracz ma > 21 (juz wyswietlilismy komunikat w petli)
                // Kasa juz przepadla przy zakladzie
            }
        }

        // 4. PYTANIE O NASTEPNA GRE
        if (g_saldo > 0) {
            cout << "\nCzy chcesz zagrac jeszcze raz? (t/n): ";
            cin >> chce_grac;
        }
        else {
            cout << "\nPrzegrales wszystko! Koniec gry." << endl;
            system("pause");
            chce_grac = 'n'; // Wymuszamy koniec
        }

    } while (chce_grac == 't' || chce_grac == 'T');

    return 0; // Powrot do Menu Głównego
}
int main() {
    int deccision = 0;
    // Pętla główna programu
    while (true) {
        showmenu();
        cout << "Wybierz opcje: ";
        cin >> deccision;

        switch (deccision) {
        case 1:
            rozgrywka_blackjack();
            break;
        case 2:
            // Tu bedzie War
            break;
        case 3:
            // Tu bedzie Poker
            break;
        case 4:
            return 0; // Koniec programu
        default:
            cout << "Brak takiej opcji" << endl;
        }
    }
}