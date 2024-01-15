#include <iostream>
#include <fstream>
#include <string>
#include "funkcja.hpp"
#include <time.h>
using namespace std;
struct macierz
{
    string wiersz1;
    string wiersz2;
    string wiersz3;
    string odpowiedz;
};
struct zestaw 
{
    string pytanie;
    string odpowiedz1;
    string odpowiedz2;
    string odpowiedz3;
    string odpowiedz4;
    string poprawna;
};
void Menu()
{//w tej funkcji ukazywane jest menu u¿ytkownikowi
    cout << "---------------TESTOWNIK-----------------------" << endl;
    cout << "-------(pytania sa przyporzadkowyane losowo!)---" << endl;
    cout << "            MENU:" << endl;
    cout << "[1] Poziom latwy" << endl;
    cout << "[2] Poziom sredni" << endl;
    cout << "[3] Poziom trudny" << endl;
    cout << "Wybierz poziom:";
}
void poziomy()//funkcja ktora jest odpowiedzialna pytania z konktretnych poziomow trudnosci
{
    string cos;
    int poziom;
    fstream plik;
   

    do
    {
        
        cin >> poziom;
        switch (poziom)//tutaj decyduje jaki poziom wybrac czyli jaki plik otowrzyc z jakimi pytaniami
        {
        case(1):
            plik.open("pytanialatwe.txt", ios::in);
            break;
        case(2):
            plik.open("pytaniasrednie.txt", ios::in);
            break;
        case(3):
            plik.open("pytaniatrudne.txt", ios::in);
            break;
        default:
            system("cls");
            cout << "NIE POPRAWNA LICZBA,POWTORZ" << endl;
            cout << "-----------------------------" << endl;
            cout << "            MENU:" << endl;
            cout << "[1] Poziom latwy" << endl;
            cout << "[2] Poziom sredni" << endl;
            cout << "[3] Poziom trudny" << endl;
            cout << "Wybierz poiom:";
            break;
        }
    } while (poziom > 3 || poziom < 1);

    system("cls");


    int rozmiar=0;
    string wiersz;//tutaj petla liczby ile jest wierszy zeby obliczyc ilosc pytan
    for (int u = 0; !plik.eof(); u++)
    {
        getline(plik, wiersz);
        rozmiar++;
        

    }
    
    rozmiar /= 6;
    plik.close();
    
    if(poziom==1)
    plik.open("pytanialatwe.txt", ios::in);
    if(poziom==2)
    plik.open("pytaniasrednie.txt", ios::in);
    if(poziom==3)
    plik.open("pytaniatrudne.txt", ios::in);

    zestaw* pakiet = new zestaw[rozmiar];//tworzymy wskaznik na strukture
    for (int i = 0; i < rozmiar; i++)//tutaj pêtla przyporzadkowuje nam konkretne dane odpowiowiedniej rzeczy w strukturze
    { 
        zestaw calyzestaw;
        getline(plik, calyzestaw.pytanie);
        getline(plik, calyzestaw.odpowiedz1);
        getline(plik, calyzestaw.odpowiedz2);
        getline(plik, calyzestaw.odpowiedz3);
        getline(plik, calyzestaw.odpowiedz4);
        getline(plik, calyzestaw.poprawna);

        pakiet[i] = calyzestaw;

    }
    
    
        int ilosc=1;
        do
        {
            cout << "Ile chcesz pytan?(maksymalnie mozesz " << rozmiar<< " )" << endl;
            cout << "Wybierz ilosc pytan:";
            cin >> ilosc;
            if (ilosc <= 0 || ilosc>rozmiar)
            {  
                system("cls");
                cout << "NIE PRAWIDLOWA LICZBA PYTAN, NAPISZ PONOWNIE LICZBE PYTAN!" << endl;
            }
        } while (ilosc <= 0 || ilosc>rozmiar);
    


    
    system("cls");
    
    int *los=new int[ilosc];//tutaj tworzymy tablice dynamiczna na liczy losowe bez powtorzen
    int c;
    srand(time(NULL));
    int wylosowane = 0;
    bool o;

    do//tutaj losuje nam liczby bez powtorzen
    {
        c =rand() % rozmiar;

        o = true;
        for (int i = 0; i < wylosowane; i++)
            if (los[i] == c)
            {
                o = false;
                break;
            }

        if (o) los[wylosowane++] = c;

    } while (wylosowane < ilosc);
   
   
    
    int punkty = 0;
    int *zlaodpowiedz=new int[ilosc];
    int pomylka = 0;
    for (int a = 0; a < ilosc; a++)
    {
        int u;
        char wybor;
        string poprawna1;
        cout << "Pytanie:" << a + 1 << endl;
        u = los[a];
        cout << pakiet[u].pytanie << endl;//tutaj pokazuje nam pytania oraz udzielamy odpowiedzi
        cout << pakiet[u].odpowiedz1 << endl;
        cout << pakiet[u].odpowiedz2 << endl;
        cout << pakiet[u].odpowiedz3 << endl;
        cout << pakiet[u].odpowiedz4 << endl;
        cout << "Wpisz swoja odpowiedz:";
        cin >> wybor;
        char tab;
        poprawna1 = pakiet[u].poprawna;//tutaj przerabiamy odpowiedz z stringa na char
        tab= poprawna1[0];
        if (tab == wybor || tab == wybor + 32 || tab == wybor - 32)//tutaj sprawdza czy odpowiedz jest prawidlowa
            punkty++;
        else //tutaj poprzez tablice dynamiczna patrzy ktore sa zle
        {
            zlaodpowiedz[a] = a + 1;
            pomylka++;
        }
        cout <<"PRAWIDLOWA ODPOWIEDZ TO:" << tab<<"               ";
        system("pause");
        system("cls");
        
    }
    cout << "Twoja liczba punktow to: " << punkty << endl;
    if(pomylka>=1)//sprawdza czy wogole sa bledy
    cout << "Zlej odpowiedzi udzieliles w pytaniu: ";
    for (int t = 0; t < ilosc; t++)//tutaj petla wypisuje w ktorych pytaniach popelnilismy bledy
    {
        

        if (zlaodpowiedz[t] >= 1 && zlaodpowiedz[t] <= rozmiar)
        {
            cout << zlaodpowiedz[t] << ",  ";
          
            
        }

    }
    //zwalniamy zarezerwowana pamiec
    pomylka = 0;
    rozmiar = 0;
    cout << endl;
    plik.close();
    delete[]los;
    delete[]pakiet;
    delete[]zlaodpowiedz;
    
}
void losowe()
{   
    int rozmiar1=0;
    int rozmiar2=0;
    int rozmiar3=0;
    string rekord;
    int rozmiarsuma=1000;//musze okrelisc jakas duza poczatkowa liczbe ale i tak potem zmienie jej rozmiar
    fstream plik;
        //zliczmy ile jest pytan w kazdym pliku
    plik.open("pytanialatwe.txt", ios::in);
    for (int u = 0; !plik.eof(); u++)
      {
      getline(plik, rekord);
       rozmiar1++;

      }
     rozmiar1 /= 6;
      plik.close();
            
    plik.open("pytaniasrednie.txt", ios::in);
    for (int u = 0; !plik.eof(); u++)
    {
    getline(plik, rekord);
    rozmiar2++;

      }
     rozmiar2 /= 6;
      plik.close();
             
     plik.open("pytaniatrudne.txt", ios::in);
     for (int u = 0; !plik.eof(); u++)
     {
      getline(plik, rekord);
       rozmiar3++;

      }
      rozmiar3 /= 6;
             
     plik.close();      
     rozmiarsuma = rozmiar1 + rozmiar2 + rozmiar3;
  zestaw* pakiet = new zestaw[rozmiarsuma];//tworzymy tyle struktur ile jest pytan
  plik.open("pytanialatwe.txt", ios::in);
  for (int i = 0; i < rozmiar1; i++)//tutaj pêtla przyporzadkowuje nam konkretne dane odpowiowiedniej rzeczy w strukturze
    { 
        zestaw calyzestaw;
        getline(plik, calyzestaw.pytanie);
        getline(plik, calyzestaw.odpowiedz1);
        getline(plik, calyzestaw.odpowiedz2);
        getline(plik, calyzestaw.odpowiedz3);
        getline(plik, calyzestaw.odpowiedz4);
        getline(plik, calyzestaw.poprawna);

        pakiet[i] = calyzestaw;

   }
  plik.close();
  plik.open("pytaniasrednie.txt", ios::in);
  for (int i = rozmiar1; i < rozmiar2+rozmiar1; i++)//tutaj pêtla przyporzadkowuje nam konkretne dane odpowiowiedniej rzeczy w strukturze
  {
      zestaw calyzestaw;
      getline(plik, calyzestaw.pytanie);
      getline(plik, calyzestaw.odpowiedz1);
      getline(plik, calyzestaw.odpowiedz2);
      getline(plik, calyzestaw.odpowiedz3);
      getline(plik, calyzestaw.odpowiedz4);
      getline(plik, calyzestaw.poprawna);

      pakiet[i] = calyzestaw;

  }
  plik.close();
  plik.open("pytaniatrudne.txt", ios::in);
  for (int i = rozmiar2+rozmiar1; i < rozmiar3+rozmiar1+rozmiar2; i++)//tutaj pêtla przyporzadkowuje nam konkretne dane odpowiowiedniej rzeczy w strukturze
  {
      zestaw calyzestaw;
      getline(plik, calyzestaw.pytanie);
      getline(plik, calyzestaw.odpowiedz1);
      getline(plik, calyzestaw.odpowiedz2);
      getline(plik, calyzestaw.odpowiedz3);
      getline(plik, calyzestaw.odpowiedz4);
      getline(plik, calyzestaw.poprawna);

      pakiet[i] = calyzestaw;

  }
  plik.close();
  system("cls");
  int ilosc = 1;
  do
  {
      cout << "Ile chcesz pytan?(maksymalnie mozesz " << rozmiarsuma << " )" << endl;
      cout << "Wybierz ilosc pytan:";
      cin >> ilosc;
      if (ilosc <= 0 || ilosc > rozmiarsuma)
      {
          system("cls");
          cout << "NIE PRAWIDLOWA LICZBA PYTAN, NAPISZ PONOWNIE LICZBE PYTAN!" << endl;
      }
  } while (ilosc <= 0 || ilosc > rozmiarsuma);
  system("cls");

  int* los = new int[ilosc];//tutaj tworzymy tablice dynamiczna na liczy losowe bez powtorzen
  int c;
  srand(time(NULL));
  int wylosowane = 0;
  bool o;
  do//tutaj losuje nam liczby bez powtorzen
  {
      c = rand() % rozmiarsuma;

      o = true;
      for (int i = 0; i < wylosowane; i++)
          if (los[i] == c)
          {
              o = false;
              break;
          }

      if (o) los[wylosowane++] = c;

  } while (wylosowane < ilosc);
 



  int punkty = 0;
  int* zlaodpowiedz = new int[ilosc];
  int pomylka = 0;
  for (int a = 0; a < ilosc; a++)
  {
      int u;
      char wybor;
      string poprawna1;
      cout << "Pytanie:" << a + 1 << endl;
      u = los[a];
      cout << pakiet[u].pytanie << endl;//tutaj pokazuje nam pytania oraz udzielamy odpowiedzi
      cout << pakiet[u].odpowiedz1 << endl;
      cout << pakiet[u].odpowiedz2 << endl;
      cout << pakiet[u].odpowiedz3 << endl;
      cout << pakiet[u].odpowiedz4 << endl;
      cout << "Wpisz swoja odpowiedz:";
      cin >> wybor;
      char tab;
      poprawna1 = pakiet[u].poprawna;//tutaj przerabiamy odpowiedz z stringa na char
      tab = poprawna1[0];
      if (tab == wybor || tab == wybor + 32 || tab == wybor - 32)//tutaj sprawdza czy odpowiedz jest prawidlowa
          punkty++;
      else //tutaj poprzez tablice dynamiczna patrzy ktore sa zle
      {
          zlaodpowiedz[a] = a + 1;
          pomylka++;
      }
      cout << "PRAWIDLOWA ODPOWIEDZ TO:" << tab << "               ";
      system("pause");
      system("cls");

  }
  cout << "Twoja liczba punktow to: " << punkty << endl;
  if (pomylka >= 1)//sprawdza czy wogole sa bledy
      cout << "Zlej odpowiedzi udzieliles w pytaniu: ";
  for (int t = 0; t < ilosc; t++)//tutaj petla wypisuje w ktorych pytaniach popelnilismy bledy
  {


      if (zlaodpowiedz[t] >= 1 && zlaodpowiedz[t] <= rozmiarsuma)
      {
          cout << zlaodpowiedz[t] << ",  ";


      }

  }
  pomylka = 0;
  cout << endl;
  plik.close();
  delete[]los;
  delete[]pakiet;
  delete[]zlaodpowiedz;
}
void dodawanie()
{
            int wybor;
            char tab[100] = { 0 };
            bool t = true;
            fstream plik;
            string tekst;
            system("cls");
            cout << "Do ktorego pliku chcesz dodac pytanie?" << endl;
            cout << "[1]Latwe" << endl;
            cout << "[2]Srednie" << endl;
            cout << "[3]Trudne" << endl;
            cout << "Wpisz numer pliku: ";
            
            do
            {
                cin >> wybor;
                switch (wybor)
                {
                case(1):
                {
                    plik.open("pytanialatwe.txt", ios_base::app);
                }
                break;
                case(2):
                {
                    plik.open("pytaniasrednie.txt", ios_base::app);
                }
                break;
                case(3):
                {
                    plik.open("pytaniatrudne.txt", ios_base::app);
                }
                break;
                default:
                {
                    system("cls");
                    cout << "Zly numer" << endl;
                    cout << "[1]Latwe" << endl;
                    cout << "[2]Srednie" << endl;
                    cout << "[3]Trudne" << endl;
                    cout << "Wpisz numer pliku: ";
                    
                }
                break;
                }
            } while (wybor < 1 || wybor>3);

            system("cls");
            cout << "Napisz pytanie(wcijsnij enter jesli chcesz to pytanie zatwierdzic)" << endl;
            plik << endl;
            getline(cin, tekst);
            getline(cin, tekst);//Czemu dwa razy?Nie wiem , jak dalem raz to nie chcialo dzialac
            plik << tekst;
            plik << endl;
            system("cls");
            cout << "Jaka chcesz odpowiedz A?(po prostu ja napisz i zatwierdz enterem)" << endl;
            plik << "A:";
            getline(cin, tekst);
            plik << tekst;
            plik << endl;
            system("cls");
            cout << "Jaka chcesz odpowiedz B?(po prostu ja napisz i zatwierdz enterem)" << endl;
            plik << "B:";
            getline(cin, tekst);
            plik << tekst;
            plik << endl;
            system("cls");
            cout << "Jaka chcesz odpowiedz C?(po prostu ja napisz i zatwierdz enterem)" << endl;
            plik << "C:";
            getline(cin, tekst);
            plik << tekst;
            plik << endl;
            system("cls");
            cout << "Jaka chcesz odpowiedz D?(po prostu ja napisz i zatwierdz enterem)" << endl;
            plik << "D:";
            getline(cin, tekst);
            plik << tekst;
            plik << endl;
            system("cls");
            cout << "Jaka jest poprawna odpowiedz?(zatwierdzasz enterem)" << endl;
            getline(cin, tekst);
            plik << tekst;
   
            plik.close();
}
void losowaniemacierzy()
{
    fstream plik;
    plik.open("macierze.txt", ios::in);
    int rozmiar = 0;
    string wiersz;//tutaj petla liczby ile jest wierszy zeby obliczyc ilosc pytan
    for (int u = 0; !plik.eof(); u++)
    {
        getline(plik, wiersz);
        rozmiar++;
    }
    rozmiar /= 4;
    plik.close();
    plik.open("macierze.txt", ios::in);
    macierz* pakiet = new macierz[rozmiar];//tworzymy wskaznik na strukture 
    for (int i = 0; i < rozmiar; i++)//tutaj pêtla przyporzadkowuje nam konkretne dane odpowiowiedniej rzeczy w strukturze
    {
        macierz pytanie;
        getline(plik, pytanie.wiersz1);
        getline(plik, pytanie.wiersz2);
        getline(plik, pytanie.wiersz3);
        getline(plik, pytanie.odpowiedz);

        pakiet[i] = pytanie;

    }
    system("cls");
    int ilosc = 1;
    do
    {
        cout << "Ile chcesz pytan?(maksymalnie mozesz " << rozmiar << " )" << endl;
        cout << "Wybierz ilosc pytan:";
        cin >> ilosc;
        if (ilosc <= 0 || ilosc > rozmiar)
        {
            system("cls");
            cout << "NIE PRAWIDLOWA LICZBA PYTAN, NAPISZ PONOWNIE LICZBE PYTAN!" << endl;
        }
    } while (ilosc <= 0 || ilosc > rozmiar);

    system("cls");

    int* los = new int[ilosc];//tutaj tworzymy tablice dynamiczna na liczy losowe bez powtorzen
    int c;
    srand(time(NULL));
    int wylosowane = 0;
    bool o;

    do//tutaj losuje nam liczby bez powtorzen
    {
        c = rand() % rozmiar;

        o = true;
        for (int i = 0; i < wylosowane; i++)
            if (los[i] == c)
            {
                o = false;
                break;
            }

        if (o) los[wylosowane++] = c;

    } while (wylosowane < ilosc);
    int punkty = 0;
    int* zlaodpowiedz = new int[ilosc];
    int pomylka = 0;
    for (int a = 0; a < ilosc; a++)
    {
        int u;
        string wybor;
        string poprawna1;
        cout << "Oblicz wyznacznik, Macierz: " << a + 1 << endl;
        u = los[a];
        cout << pakiet[u].wiersz1 << endl;//tutaj pokazuje nam pytania oraz udzielamy odpowiedzi
        cout << pakiet[u].wiersz2 << endl;
        cout << pakiet[u].wiersz3 << endl;
        cout << "Wpisz swoja odpowiedz:";
        cin >> wybor;
        poprawna1 = pakiet[u].odpowiedz;//tutaj przerabiamy odpowiedz z stringa na char
        if (poprawna1 == wybor)//tutaj sprawdza czy odpowiedz jest prawidlowa
            punkty++;
        else //tutaj poprzez tablice dynamiczna patrzy ktore sa zle
        {
            zlaodpowiedz[a] = a + 1;
            pomylka++;
        }
        cout << "PRAWIDLOWA ODPOWIEDZ TO:" << poprawna1 << "               ";
        system("pause");
        system("cls");

    }
    cout << "Twoja liczba punktow to: " << punkty << endl;
    if (pomylka >= 1)//sprawdza czy wogole sa bledy
        cout << "Zlej odpowiedzi udzieliles w pytaniu: ";
    for (int t = 0; t < ilosc; t++)//tutaj petla wypisuje w ktorych pytaniach popelnilismy bledy
    {


        if (zlaodpowiedz[t] >= 1 && zlaodpowiedz[t] <= rozmiar)
        {
            cout << zlaodpowiedz[t] << ",  ";


        }

    }
}
void generatormacierzy()
{
    bool pytanie = true;
    string q;
    int wyznacznik;
    int odpowiedz;
    int tab[3][3];
    srand(time(NULL));
    int los = rand() % 9 + 1;
    //tworzenie macierzy
    for (int a = 0; a < 3; a++)
    {
        for (int b = 0; b < 3; b++)
        {
            tab[a][b] = rand() % 9 + 1;
        }
    }
    system("cls");
    //wypisanie mcierzy
    cout << "Oblicz wyznacznik tej macierzy:" << endl;
    for (int a = 0; a < 3; a++)//przypisywanie macierzy do tablicy
    {
        for (int b = 0; b < 3; b++)
        {
            if (a == 0 && b == 0)
                cout << "|";

            if (a == 0 && b == 2)
            {
                cout << " " << tab[a][b];
                cout << "|";
            }

            if (a == 1 && b == 0)
                cout << "|";

            if (a == 1 && b == 2)
            {
                cout << " " << tab[a][b];
                cout << "|";
            }
               

            if (a == 2 && b == 0)
                cout << "|";

            if (a == 2 && b == 2)
            {
                cout << " " << tab[a][b];
                cout << "|";
            }
                


            if(b!=2)
            cout << " " << tab[a][b];
        }
        cout << endl;
        
        

    }
    cout << endl;
    odpowiedz = tab[0][0] * tab[1][1] * tab[2][2] + tab[1][0] * tab[2][1] * tab[0][2] + tab[2][0] * tab[0][1] * tab[1][2] - tab[0][2] * tab[1][1] * tab[2][0] - tab[1][2] * tab[2][1] * tab[0][0] - tab[2][2] * tab[0][1] * tab[1][0];
    cout << "Napisz ile wynosi wyznacznik:";
    cin >> wyznacznik;

    if (wyznacznik == odpowiedz)//sprawdza czy dobra odpowiedz
        cout << "Brawo, dobrze obliczyles" << endl;

    else
    {
        cout << "Niestety zle obliczyles" << endl;
        cout << "Prawidlowa odpowiedz to:" << odpowiedz << endl;
    }

    cout << endl << endl;
    cout << "Czy chcesz zeby ta macierz zostala zapisana do pliku?(jesli chcesz napisz tak)" << endl;
    cin >> q;
    if (q == "tak")//zapisuje macierz do pliku
    {
        fstream plik;
        plik.open("macierze.txt", ios_base::app);
        plik << endl;
        for (int a = 0; a < 3; a++)
        {
            for (int b = 0; b < 3; b++)
            {
                if (a == 0 && b == 0)
                    plik << "|";

                if (a == 0 && b == 2)
                {
                    plik << " " << tab[a][b];
                    plik << "|";
                }

                if (a == 1 && b == 0)
                    plik << "|";

                if (a == 1 && b == 2)
                {
                    plik << " " << tab[a][b];
                    plik << "|";
                }


                if (a == 2 && b == 0)
                    plik << "|";

                if (a == 2 && b == 2)
                {
                    plik << " " << tab[a][b];
                    plik << "|";
                }



                if (b != 2)
                    plik << " " << tab[a][b];
            }
            if(a!=2)
            plik << endl;



        }
        plik << endl;
        plik << odpowiedz;


    }
}
