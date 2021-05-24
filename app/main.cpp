/* Executables must have the following defined if the library contains
doctest definitions. For builds with this disabled, e.g. code shipped to
users, this can be left out. */

/*!
    \file
        \brief Plik zawierajacy glowna funkcje programu.
*/

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <iomanip>




#include "exampleConfig.h"
#include "example.h"
#include "Macierz.hh"
#include "Wector.hh"
#include "Wector3D.hh"
#include "Macierz3x3.hh"
#include "../include/lacze_do_gnuplota.hh"
#include "prostopadloscian.hh"
#include "Scena.hh"



int main() {



std::cout << "szdzsd";

std::string nowy_plik;


std::vector <std::string> adres_pliku;
std::string nazwa_pliku_do_wspolrzednych;


    PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //


Scena przestrzen;

Vector3D wektor_przesuniecia;
Vector3D srodeknowejfigury;
Matrix3x3 macierz_obrotu;
int indeks_aktualnego_prostopadloscianu=0;

  adres_pliku.push_back("../datasets/prostopadloscian.dat");  

  Lacze.DodajNazwePliku(adres_pliku.at(0).c_str(),PzG::RR_Ciagly,2);
   
   //
   //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  Lacze.ZmienTrybRys(PzG::TR_3D);



przestrzen[indeks_aktualnego_prostopadloscianu].wpisz_wspolrzedne_do_pliku(adres_pliku.at(indeks_aktualnego_prostopadloscianu).c_str()); /*Zapis i wyswietlenie w GNUplot stanu poczatkowego, pierwszego, przykladowego prostopadloscianu */
        Lacze.Rysuj();



char wybor;
double kat=0;
int ile_obrotow=1;
double nowadl=0;
double nowawys=0;
double nowagleb=0;


try{
        przestrzen[indeks_aktualnego_prostopadloscianu].wpisz_wspolrzedne_do_pliku(adres_pliku.at(indeks_aktualnego_prostopadloscianu).c_str()); /*Zapis i wyswietlenie w GNUplot stanu poczatkowego, pierwszego, przykladowego prostopadloscianu */
        Lacze.Rysuj();

std::cout << "Poczatkowy stan bokow prostopadloscianu: " << std::endl;
        przestrzen[indeks_aktualnego_prostopadloscianu].czy_prostopadloscian(); 

        std::cout << "Menu wyboru opcji:" << std::endl
                  << "\ta - zmien aktywny prostopadloscian" << std::endl
                  << "\to - obrot bryly o zadane katy wokol osi X,Y,Z" << std::endl
                  << "\tt - powtorz poprzedni obrot" << std::endl
                  << "\tr - wyswietl macierzy rotacji" << std::endl
                  << "\tp - przesun bryle o zadany wektor " << std::endl
                  << "\tw - wyswietl wspolrzedne wierzcholkow " << std::endl
                  << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
                  << "\tm - wyswietl menu" << std::endl
                  << "\td - dodaj kolejny prostopadloscian" << std::endl
                  << "\tk - zakoncz program" << std::endl << std::endl;

















        while (wybor != 'k'){ 
            std::cout << "Numer aktualnego prostopadloscianu: " << indeks_aktualnego_prostopadloscianu << std::endl;
            std::cout << "Podaj opcje dzialania: ";
            std::cin >> wybor;
            switch(wybor){
                
                case 'a': /* zmiana aktywnego prostopaloscianu */
                    while (true){
                        try{
                            std::cout << "Jest 0-" << przestrzen.ileprostopadloscianow()-1  << " prostopadloscianow" << std::endl;
                            std::cout << "Ktory prostopadloscian ma byc aktualnym: " << std::endl;;
                            std::cin >> indeks_aktualnego_prostopadloscianu; 
                            if(std::cin.fail() || indeks_aktualnego_prostopadloscianu > (przestrzen.ileprostopadloscianow()-1))
                                throw std::invalid_argument("Podano nieprawidlowy numer prostopadloscianu ");
                            else   
                                break;
                        }
                        catch (std::invalid_argument & blad){ 
                            std::cerr << blad.what() << std::endl << "Sprobuj ponownie"  << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');   
                        }
                    } 
                break;

                case 'o': /* Obrot prostopadloscianu o zadany kat oraz ilosc powtorzen*/
                    macierz_obrotu = Matrix3x3();
                    std::cout << "Podaj wartosci katow, o jakie ma zostac wykonany obrot wokol konkretnych osi w postaci " << std::endl; 
                    std::cout << "x wartosc kata wokol osi X" << std::endl;
                    std::cout << "y wartosc kata obrotu wokol osi Y" << std::endl;
                    std::cout << "z wartosc kata obrotu wokol osi Z" << std::endl;
                    std::cout << "Wpiswanie katow zakonczy wpisanie zanku '.'" << std::endl;
                    while (wybor !='.'){  
                        try{
                            std::cin >> wybor;
                            switch(wybor){
                                case 'x':
                                std::cin >> kat;
                                if(std::cin.fail())
                                    throw std::invalid_argument("Nieprawidlowa wartosc kata obrotu "); 
                                else 
                                    macierz_obrotu = Wypelnianie_macierzy_OX(kat) * macierz_obrotu;
                                break;

                                case 'y':
                                std::cin >> kat;
                                if(std::cin.fail())
                                    throw std::invalid_argument("Nieprawidlowa wartosc kata obrotu ");
                                else
                                    macierz_obrotu = Wypelnianie_macierzy_OY(kat) * macierz_obrotu;
                                break;

                                case 'z':
                                std::cin >> kat;
                                if(std::cin.fail())
                                    throw std::invalid_argument("Nieprawidlowa wartosc kata obrotu ");
                                else
                                    macierz_obrotu = Wypelnianie_macierzy_OZ(kat) * macierz_obrotu;
                                break;

                                case '.':    
                                    std::cout << "Podawanie katow obrotow zakonczone pomyslnie. " << std::endl;      
                                break;

                                default:
                                    std::cout << "Nie ma takich osi. Dopuszczalne znaki to: (x, y, z, .)" << std::endl; 
                                    std::cout << "Sprobuj ponownie" << std::endl;
                                    std::cin.ignore(10000,'\n');
                                break;            
                              } 
                        }
                        catch (std::invalid_argument & d){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby program poinformuje o tym i usunie blad ze strumienia */
                            std::cerr << d.what() << std::endl << "Sprobuj jeszcze raz"  << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');   
                        }
                    }

                    while (true){
                        try{
                            std::cout << "Ile obrotow wykonac? "<< std::endl; /* Okreslenie ile razy wprowadzony obrot ma sie wykonac*/
                            std::cin >> ile_obrotow; 
                            if(std::cin.fail() || ile_obrotow < 0)
                                throw std::invalid_argument("Bledna ilosc obrotow");
                            else   
                                break;
                        }
                        catch (std::invalid_argument & f){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby program poinformuje o tym i usunie blad ze strumienia */
                            std::cerr << f.what() << std::endl << "Sprobuj jeszcze raz"  << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');   
                        }
                    } 

                    for (int i=0; i<ile_obrotow;++i)
                        przestrzen.update_matrix(macierz_obrotu, indeks_aktualnego_prostopadloscianu);
                    
                    przestrzen.ruszanie_prostopadloscianem(indeks_aktualnego_prostopadloscianu); 
                    przestrzen[indeks_aktualnego_prostopadloscianu].czy_prostopadloscian();
                    przestrzen[indeks_aktualnego_prostopadloscianu].wpisz_wspolrzedne_do_pliku(adres_pliku.at(indeks_aktualnego_prostopadloscianu).c_str());
                    Lacze.Rysuj();
                break;

                case 'p': /* Opcja translacji o wektor */
                    std::cout << "Wprowadz wspolrzedne wektora translacji w postaci liczb x,y,z klikajac enter po kazdej wprowadzonej liczbie: ";
                    std::cin >> wektor_przesuniecia;

                    przestrzen.update_vector(wektor_przesuniecia,indeks_aktualnego_prostopadloscianu);
                    przestrzen.ruszanie_prostopadloscianem(indeks_aktualnego_prostopadloscianu);

                    przestrzen[indeks_aktualnego_prostopadloscianu].wpisz_wspolrzedne_do_pliku(adres_pliku[indeks_aktualnego_prostopadloscianu].c_str());
                    przestrzen[indeks_aktualnego_prostopadloscianu].czy_prostopadloscian();
                    
                    Lacze.Rysuj();
                break;

                case 'w': /*    Wyswietlanie wspolrzedne prostopadloscianu    */
                    std::cout << "Aktualne wspolrzedne prostopadloscianu: " << std::endl;
                    std::cout << przestrzen[indeks_aktualnego_prostopadloscianu];
                break;

                case 't':
                    for (int i=0; i<ile_obrotow;++i)
                        przestrzen.update_matrix(macierz_obrotu,indeks_aktualnego_prostopadloscianu);  
                    przestrzen.ruszanie_prostopadloscianem(indeks_aktualnego_prostopadloscianu);
                    przestrzen[indeks_aktualnego_prostopadloscianu].wpisz_wspolrzedne_do_pliku(adres_pliku[indeks_aktualnego_prostopadloscianu].c_str());
                    przestrzen[indeks_aktualnego_prostopadloscianu].czy_prostopadloscian();
                    Lacze.Rysuj();
                break;

                case 'r': /*       Ponawianie ostatni obrot prostopadloscianu       */   
                    std::cout << "Macierz rotacji " << std::endl << przestrzen.odczytajmacierz(indeks_aktualnego_prostopadloscianu) << std::endl; 
                break;

                case 'm': /*    Wyswietlanie opcji w menu    */        
                    std::cout << "Menu wyboru opcji:" << std::endl
                              << "\ta - zmien aktywny prostopadloscian" << std::endl
                              << "\to - obrot bryly o zadana sekwencje katow" << std::endl
                              << "\tt - powtorzenie poprzedniego obrotu" << std::endl
                              << "\tr - wyswietlenie macierzy rotacji" << std::endl
                              << "\tp - przesuniecie bryly o zadany wektor " << std::endl
                              << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                              << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
                              << "\tm - wyswietl menu" << std::endl
                              << "\td - dodaj nowy prostopadloscian" << std::endl
                              << "\tk - koniec dzialania programu" << std::endl << std::endl;
                break;

                case 'k': /*    Koniec programu    */
                    std::cout << ":) Konczenie pracy programu" << std::endl;
                break;

                case 's': /*    Wyswietlanie wspolrzednych prostopadloscianu    */
                    przestrzen[indeks_aktualnego_prostopadloscianu].czy_prostopadloscian();
                break;

                case 'd': /*    Dodawanie do sceny nowego prostopadloscianu    */
                    std::cout << "Podaj wspolrzedne punktow, na ktorych zostanie rozpiety nowy prostopadloscian: " << std::endl; 
                    std::cout << "Podaj wspolrzedne x y z pierwszego punktu: "; 
                    std::cin >> srodeknowejfigury;
                    std::cout << "Podaj kolejno polowy dlugosci,wysokosci oraz glebokosci nowego prostopadloscianu " << std::endl; 
                    std::cin >> nowadl>> nowawys >>nowagleb;
                    if (std::cin.fail() || (nowadl == 0 && nowawys == 0 && nowagleb == 0)){
                        std::cerr << ":( Niepoprawne oznaczenie dlugosci, dodawanie przerwane." << std::endl; 
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');   
                        break;
                    }   


                    

                    nowy_plik = "../datasets/cuboid.dat";
                    nowy_plik.insert(18, std::to_string(przestrzen.ileprostopadloscianow() + 1));
                    adres_pliku.push_back(nowy_plik);
                    Lacze.DodajNazwePliku(nowy_plik.c_str(),PzG::RR_Ciagly, 2);

                    przestrzen.dodaj_prostopad(srodeknowejfigury,nowadl,nowawys,nowagleb);

                    przestrzen[przestrzen.ileprostopadloscianow()-1].wpisz_wspolrzedne_do_pliku(nowy_plik.c_str());

                    Lacze.Rysuj();
                break;

                default: /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
                    std::cout << "Nie ma takiej mozliwosci przesuniecia" << std::endl;
            }
        }/*   while   */

}
    catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
        std::cerr << "Wystapil blad!"<< std::endl << e.what() << std::endl;
        exit(1);
    }
    return 0;

}

