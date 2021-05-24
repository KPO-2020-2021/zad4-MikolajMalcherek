

#include "Scena.hh"
/*!
    \brief Metoda 
*/

void Scena::dodaj_prostopad(Vector3D const & srodek, double const & dlOX, double const & dlOY, double const & dlOZ){
    Vector3D wierzcholek[8], VecOX, VecOY, VecOZ;
  
    VecOX[0] = dlOX/2; 
    VecOY[1] = dlOY/2; 
    VecOZ[2] = dlOZ/2;

    wierzcholek[0] = wierzcholek[0] - VecOX - VecOY - VecOZ;
    wierzcholek[1] = wierzcholek[1] + VecOX - VecOY - VecOZ;
    wierzcholek[2] = wierzcholek[2] - VecOX + VecOY - VecOZ;
    wierzcholek[3] = wierzcholek[3] + VecOX + VecOY - VecOZ;
    wierzcholek[4] = wierzcholek[4] - VecOX + VecOY + VecOZ;
    wierzcholek[5] = wierzcholek[5] + VecOX + VecOY + VecOZ;
    wierzcholek[6] = wierzcholek[6] - VecOX - VecOY + VecOZ;
    wierzcholek[7] = wierzcholek[7] + VecOX - VecOY + VecOZ;

    prostopadloscian prostopad(wierzcholek[0], wierzcholek[1], wierzcholek[2], wierzcholek[3], wierzcholek[4], wierzcholek[5], wierzcholek[6], wierzcholek[7], srodek);


    wszystkie_prostopadlosciany.push_back(prostopad); 
    macierze_obrotu.push_back(Matrix3x3());
    wektory_przesuniecia.push_back(Vector3D());   
}



Scena::Scena(){
    double srodektablica[]={20,20,20};
    Vector3D A(srodektablica);
    dodaj_prostopad(A,100,100,100);
}

/*!
    Publiczny destrukor czyszczacy pliki tymczasowe, w ktorych zapisywane sa wspolrzedne globalne prostopadloscianow. 
*/

Scena::~Scena(){
    std::string sciezka_zapisanych_plikow = "../datasets";
    for (const auto& entry : std::filesystem::directory_iterator(sciezka_zapisanych_plikow)) 
        std::filesystem::remove_all(entry.path());
}

/*!
    Przeciezenie operatora [], sluzace do wskazania wspolrzednych konkretnego prostopadloscianu ze sceny

*/

const prostopadloscian & Scena::operator [] (unsigned int indeks) const{
    if (indeks>=wszystkie_prostopadlosciany.size())
        throw std::runtime_error("Nie ma tylu figur");
    return wszystkie_prostopadlosciany.at(indeks);
}

/*!
    Metoda pokazujaca wartosci macierzy rotacji konkretnego prostopadloscianu

*/

Matrix3x3 Scena::odczytajmacierz(int indeks){
    return macierze_obrotu.at(indeks);
}

/*!
    Modyfikowanie macierzy rotacji wskazanego prostopadloscianu na scenie.
*/

void Scena::update_matrix(Matrix3x3 const & mtx, int index){
    Matrix3x3 temp_matrix = mtx;
    macierze_obrotu.at(index) = temp_matrix * macierze_obrotu.at(index);
}

/*!
    Modyfikowanie wektora przesuniecia wskazanego prostopadloscianu na scenie.

*/

void Scena::update_vector(Vector3D const & vec, int index){
    Vector3D wektor = vec;
    wektory_przesuniecia.at(index) = wektory_przesuniecia.at(index) + wektor;
}

/*!
    Metoda pozwalajaca na przemieszanie prostopadloscianu na scenie.
    
*/

void Scena::ruszanie_prostopadloscianem(int index){
    wszystkie_prostopadlosciany.at(index).przemieszczenie(wektory_przesuniecia.at(index), macierze_obrotu.at(index));
}

/*!
    Metoda sprawdzajaca ilosc prostopadloscianow na scenie.

*/

int Scena::ileprostopadloscianow(){
    return wszystkie_prostopadlosciany.size();
}





