#include <iostream>
#include <fstream>
#include "funkcja.hpp"
#include <string>
using namespace std;

int main()
{  
    int  wyborr;
    string a="tak";
    do
    {
        cout << "--------------------------TESTOWNIK----------------------------" << endl;
        cout << "-------(pytania sa losowej kolejnosci w kazdym trybie)---------\n\n" << endl;
        cout << "PYTANIA ZAMKNIETE" << endl;
        cout << "[1] Wybor poziomu trudnosci" << endl;
        cout << "[2] Losowanie ze wszytskich poziomow" << endl;
        cout << "[3] Dodaj pytanie do bazy pytan" << endl;
        cout << endl << endl;
        cout << "MACIERZE" << endl;
        cout << "[4] Losowanie macierzy z pliku" << endl;
        cout << "[5] Generator nowych macierzy" << endl;
        
        cout << "Wybierz tryb: ";
        
        do
        {
            cin >> wyborr;
             switch (wyborr)
                {
                case(1):
                {
                    system("cls");
                    Menu();
                    poziomy();
                }break;
                case(2):
                {
                    losowe();

                }
                break;
                case(3):
                {

                    dodawanie();
                }
                break;
                case(4):
                {
                    losowaniemacierzy();
                }
                break;
                case(5):
                {
                    generatormacierzy();
                }
                break;
                default:
                {
                    system("cls");
                    cout << "Wybrałes zle opcje , prosze o ponowne wpisanie" << endl;
                    cout << "PYTANIA ZAMKNIETE" << endl;
                    cout << "[1] Wybor poziomu trudnosci" << endl;
                    cout << "[2] Losowanie ze wszytskich poziomow" << endl;
                    cout << "[3] Dodaj pytanie do bazy pytan" << endl;
                    cout << endl << endl;
                    cout << "MACIERZE" << endl;
                    cout << "[4] Losowanie macierzy z pliku" << endl;
                    cout << "[5] Generator nowych macierzy" << endl;
                    cout << "Wybierz tryb: ";
                }

                }
            
            
        } while (wyborr < 1 || wyborr > 5);

        cout << endl;
        cout << "Powtorzyc? (nacisnij t) ";
        cin >> a;
        system("cls");
    } while (a=="t");
}