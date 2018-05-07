#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>

#include <mech.h>
#include <menu.h>
#include <plansza.h>



using namespace std;

menu MENU;


// TABLICA;
void mech::wymiary_planszy()
{
    system("cls");
    MENU.okno_powitalne();
    MENU.podaj_wymiary_planszy(rozmiar_planszy);
}

void mech::ilosc_symboli()
{
    system("cls");
    MENU.okno_powitalne();
    MENU.podaj_ilosc_symboli(ilosc_symboli_linia, rozmiar_planszy);
}

void mech::nowa_plansza()
{
    tablica = new char *[rozmiar_planszy];
    for (int i = 0; i < rozmiar_planszy; i++)
        tablica[i] = new char [rozmiar_planszy];

    for (int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            tablica[i][j]= '_';
        }
    }
}

void mech::usuwanie_dynamicznych()
{
    for (int i = 0; i < rozmiar_planszy; i++)
        delete [] tablica[i];
    delete [] tablica;
}

void mech::drukuj_plansze()
{
    for (int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            cout << tablica[i][j] << '\t';
        }
        cout << endl << endl;
    }
}

// GRACZE

void mech::dane_graczy()
{
    gracz1.nick = MENU.nick("pierwszy");
    if(gvsg == true)
    {
        gracz2.nick = MENU.nick("drugi");
    }
    else if(gvsg == false)
    {
        gracz2.nick = "KOMPUTER";
    }

    zmienna_char = MENU.znak(gracz1.nick);
    switch (zmienna_char)
    {
    case 'O':
        gracz1.znak = 'O';
        gracz2.znak = 'X';
        break;
    case 'X':
        gracz1.znak = 'X';
        gracz2.znak = 'O';
        break;
    }

    zmienna_int = MENU.wartosc(gracz1.nick);
    switch (zmienna_int)
    {
    case 1:
        gracz1.wartosc = 1;
        gracz2.wartosc = 0;
        break;
    case 0:
        gracz1.wartosc = 0;
        gracz2.wartosc = 1;
    default:
        break;
    }
}

//GRACZ VS GRACZ

void mech::pelna_mechanika_gg()
{
    mech::wymiary_planszy();
    mech::ilosc_symboli();
    mech::nowa_plansza();
    mech::rozgrywka_gg();

}
void mech::dane_testowe()
{
    gracz1.wartosc = 1;
    gracz2.wartosc = 0;
    gracz1.znak = 'O';
    gracz2.znak = 'X';
    gracz1.nick = "KOLKO";
    gracz2.nick = "KRZYZYK";

}
void mech::pelna_mechanika_test()
{
    mech::dane_testowe();
    mech::wymiary_planszy();
    mech::ilosc_symboli();
    mech::nowa_plansza();
    mech::rozgrywka_test();
}

void mech::rozgrywka_test()
{
    liczba_ruchow = 0;
    srand(time(0));
    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");

        MENU.okno_powitalne();

        if(gracz1.wartosc == 1)
        {
            gracz_pomocniczy = gracz1;
        }
        else if(gracz1.wartosc == 0)
        {
            gracz_pomocniczy = gracz2;
        }

        mech::drukuj_plansze();
        x = rand()%(rozmiar_planszy);
        y = rand()%(rozmiar_planszy);
        while(tablica[x][y]!=('_'))
        {
            x = rand()%(rozmiar_planszy);
            y = rand()%(rozmiar_planszy);
        }
        tablica[x][y] = gracz_pomocniczy.znak;

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        liczba_ruchow++;
        mech::wynik();
    }
}


void mech::rozgrywka_gg()
{
    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");
        MENU.okno_powitalne();
        drukuj_plansze();

        if(gracz1.wartosc == 1)
        {
            gracz_pomocniczy = gracz1;
        }
        else if(gracz1.wartosc == 0)
        {
            gracz_pomocniczy = gracz2;
        }

        cout << gracz_pomocniczy.nick << ", twoj ruch "<< gracz_pomocniczy.znak << endl;

        mech::wspolrzedne_ruchu(gracz_pomocniczy);

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        liczba_ruchow++;
        mech::wynik();
    }
}

// RUCH

void mech::powtorka()
{
    mech::nowa_plansza();
    if(gracz1.wartosc == 0)
    {
        gracz1.wartosc = 1;
        gracz2.wartosc = 0;
    }
    else if(gracz1.wartosc == 1)
    {
        gracz1.wartosc = 0;
        gracz2.wartosc = 1;
    }

    if(test == false)
    {
        if(gvsg == true)
        {
            mech::rozgrywka_gg();
        }
        if(gvsg == false)
        {
            mech::rozgrywka_gvsk();
        }
    }
    if(test == true)
    {
        mech::rozgrywka_test();
    }

}

void mech::wspolrzedne_ruchu(zawodnik gracz)
{
    cout << "Podaj wspolrzedna x " ;
    cin >> x;
    while(x<1 || x>rozmiar_planszy)
    {
        cout << "Podaj wspolrzedna x " ;
        cin >> x;
    }

    cout << "Podaj wspolrzedna y " ;
    cin >> y;
    while(y<1 || y>rozmiar_planszy)
    {
        cout << "Podaj wspolrzedna y " ;
        cin >> y;
    }

    if(tablica[x-1][y-1]!='_')
    {
        cout << "Pole zajete!" << endl;
        mech::wspolrzedne_ruchu(gracz);
    }
    tablica[x-1][y-1] = gracz.znak;

}

//bool mech::analiza_ruchu()
//{
//    mech::wyp_tab_pom();

//    for(int i = 0; i < rozmiar_planszy; i++)
//    {
//        for (int j = 0; j < rozmiar_planszy; j++)
//        {
//            if(tablica_pom[i][j] == '_')
//            {

//                tablica_pom[i][j] = gracz2.znak;

//                for(int i = 0; i < rozmiar_planszy; i++)
//                {
//                    for (int j = 0; j < rozmiar_planszy; j++)
//                    {
//                        cout << tablica_pom[i][j] << '\t';
//                    }
//                    cout << endl;
//                }
//                cout << endl << "**********************************" << endl;


//                zmienna_char = gracz2.znak;
//                if(mech::sprawdzenie(tablica_pom, gracz2.znak) == true)
//                {
//                    x = i;
//                    y = j;
//                    tablica_pom[i][j] = '_';
//                    return true;
//                }

//               tablica_pom[i][j] = gracz1.znak;
//                zmienna_char = gracz1.znak;

//                if(mech::sprawdzenie(tablica_pom, gracz1.znak) == true)
//                {
//                    x = i;
//                    y = j;
//                    tablica_pom[i][j] = '_';
//                    return true;
//                }
//                tablica_pom[i][j] = '_';
//            }
//        }
//    }
//    return false;
//}

// G VS K

void mech::pelna_mechanika_gvsk()
{
    mech::wymiary_planszy();
    mech::ilosc_symboli();
    mech::nowa_plansza();
    mech::rozgrywka_gvsk();
}

void mech::rozgrywka_gvsk()
{
    liczba_ruchow = 0;
    for(int i = 0; i < rozmiar_planszy*rozmiar_planszy; i++)
    {
        system("cls");

        MENU.okno_powitalne();
        drukuj_plansze();

        if(gracz1.wartosc == 1)
        {
            cout << gracz1.nick << ", twoj ruch "<< gracz1.znak << endl;
            mech::wspolrzedne_ruchu(gracz1);
        }
        else if(gracz1.wartosc == 0)
        {
            mech::wspolrzedne_ruchu_komputera(gracz2.znak, 0);
        }

        gracz_pomocniczy.wartosc = gracz1.wartosc;
        gracz1.wartosc = gracz2.wartosc;
        gracz2.wartosc = gracz_pomocniczy.wartosc;

        liczba_ruchow++;
        mech::wynik();
    }
}



// SPRAWDZENIA



bool mech::sprawdzenie(char **tablica, char znak)
{

    suma = 0;

    for(int i = 0; i < rozmiar_planszy; i++)
    {
        for(int j = 0; j < rozmiar_planszy-1; j++)
        {
            if(tablica[i][j]== znak)
            {
                if(suma<1)
                {
                    suma = 1;
                }
                if(tablica[i][j+1] == znak)
                {
                    suma++;
                }
                else
                {
                    suma = 0;
                }
            }
            if(suma == ilosc_symboli_linia)
            {
                return true;
            }
        }
        suma = 0;

        for(int j = 0; j < rozmiar_planszy-1; j++)
        {
            if(tablica[j][i]== znak)
            {
                if(suma<1)
                {
                    suma = 1;
                }
                if(tablica[j+1][i] == znak)
                {
                    suma++;
                }
                else
                {
                    suma = 0;
                }
            }
            if(suma == ilosc_symboli_linia)
            {
                return true;
            }
        }
        suma = 0;
    }

    for(int a = ilosc_symboli_linia-rozmiar_planszy; a<=rozmiar_planszy-ilosc_symboli_linia; a++)
    {
        for(int i = 0; i < rozmiar_planszy-1; i++)
        {
            if(a+i>=0 && a+i<rozmiar_planszy)
            {
                if(tablica[a+i][i] == znak)
                {
                    if(suma < 1)
                    {
                        suma = 1;
                    }
                    if(tablica[a+i+1][i+1] == znak)
                    {
                        suma++;
                    }
                    else
                    {
                        suma = 0;
                    }
                }
                if(suma == ilosc_symboli_linia)
                {
                    return true;
                }
            }
        }
        suma = 0;
    }

    for(int a = ilosc_symboli_linia-rozmiar_planszy; a<=rozmiar_planszy-ilosc_symboli_linia; a++)
    {
        for(int i = 0; i < rozmiar_planszy-1; i++)
        {
            if(rozmiar_planszy-2-i+a>=0 && rozmiar_planszy-1-i+a<rozmiar_planszy)
            {
                if(tablica[rozmiar_planszy-1-i+a][i] == znak)
                {
                    if(suma < 1)
                    {
                        suma = 1;
                    }
                    if(tablica[rozmiar_planszy-2-i+a][i+1] == znak)
                    {
                        suma++;
                    }
                    else
                    {
                        suma = 0;
                    }                 
                }
                if(suma == ilosc_symboli_linia)
                {
                    return true;
                }
            }
        }
        suma = 0;
    }
    return false;

}
void mech::wynik()
{
    if(mech::sprawdzenie(tablica, gracz1.znak) == true)
    {
        MENU.zwyciestwo(gracz1);
    }
    else if(mech::sprawdzenie(tablica, gracz2.znak) == true)
    {
        MENU.zwyciestwo(gracz2);
    }
    else if(liczba_ruchow == rozmiar_planszy*rozmiar_planszy)
    {
        MENU.remis();
    }
}



int mech::wspolrzedne_ruchu_komputera(char gracz, int poziom)
{
  int licznik = 0;

  for(int i = 0; i < rozmiar_planszy; i++)
  {
    for(int j = 0; j < rozmiar_planszy; j++)
    {
      if(tablica[i][j] == '_')
      {
        tablica[i][j] = gracz;
        x = i;
        y = j;  // gdyby był remis
        licznik++;     // zliczamy wolne pola

        warunek = mech::sprawdzenie(tablica, gracz);
        tablica[i][j] = '_';

        if(warunek == true)
        {
            if(poziom == 0)
            {
                tablica[i][j] = gracz;
            }
            if(gracz == 'X')
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }

//        if(gracz == 'X')
//        {
//            gracz = 'O';
//        }
//        else
//        {
//            gracz = 'X';
//        }

//        test = mech::sprawdzenie(tablica, gracz);
//        tablica[i][j] = '_';

//        if(gracz == 'X')
//        {
//            gracz = 'O';
//        }
//        else
//        {
//            gracz = 'X';
//        }

//        if(test == true)
//        {
//            if(poziom == 0)
//            {
//                tablica[i][j] = gracz;
//            }
//            if(gracz == 'X')
//            {
//                return -1;
//            }
//            else
//            {
//                return 1;
//            }
//        }
      }
    }
  }

  // sprawdzamy, czy jest remiS

  if(licznik == 1)
  {
    if(poziom == 0)
    {
        tablica[x][y] = gracz;
    }
    return 0;
  }

  if(gracz == 'X')
  {
      maksymalna_wartosc_ruchu = -2;
  }
  else
  {
      maksymalna_wartosc_ruchu = 2;
  }

  for(int i = 0; i < rozmiar_planszy; i++)
    for(int j = 0; j < rozmiar_planszy; j++)
      if(tablica[i][j] == '_')
      {
        tablica[i][j] = gracz;

        if(gracz == 'X')
        {
            gracz = 'O';
        }
        else
        {
            gracz = 'X';
        }
        wartosc_ruchu = mech::wspolrzedne_ruchu_komputera(gracz, poziom + 1);
        tablica[i][j] = '_';

        if(((gracz == 'X') && (wartosc_ruchu > maksymalna_wartosc_ruchu)) || ((gracz == 'O') && (wartosc_ruchu < maksymalna_wartosc_ruchu)))
        {
          maksymalna_wartosc_ruchu = wartosc_ruchu;
          x = i;
          y = j;
        }
      }

   if(poziom == 0)
   {
       tablica[x][y] = gracz;
   }
   return maksymalna_wartosc_ruchu;
}


