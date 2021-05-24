#pragma once


#include "size.hh"
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>


#include "Wector3D.hh"
#include "Macierz.hh"
#include "Macierz3x3.hh"
#include "lacze_do_gnuplota.hh"


class prostopadloscian
{
private:

    Vector3D srodek;
    Vector3D wierzcholki[ILWIERZCHOLKOW]; 
    Vector3D wierzcholki_oryginalne[ILWIERZCHOLKOW];

public:
    prostopadloscian(Vector3D wierzcholekA,Vector3D wierzcholekB,Vector3D wierzcholekC,Vector3D wierzcholekD,Vector3D wierzcholekE,
    Vector3D wierzcholekF,Vector3D wierzcholekG,Vector3D wierzcholekH,Vector3D srodek);

    prostopadloscian();

    const Vector3D &operator[](int index) const;

    Vector3D &operator[](int index);

    void check_length();

    void przemieszczenie(Vector3D const & wektor_przes, Matrix3x3 const & macierz_obrotu);

    void wpisz_wspolrzedne_do_pliku(const char *sNazwaPliku) const;

    void czy_prostopadloscian() const;
};

std::istream &operator>>(std::istream &in, prostopadloscian &mat);

std::ostream &operator<<(std::ostream &out, prostopadloscian const &mat);
