#include "prostopadloscian.hh"
#include "Wector.hh"


/** 
 * Metoda dla klasy prostopadloscian
 * Przyjmuje wierzcholki oraz wspolrzedne srodka
 * Przypisuje przyjete wierzcholki do prostopadloscianu
*/


prostopadloscian::prostopadloscian(Vector3D wierzcholekA,Vector3D wierzcholekB,Vector3D wierzcholekC,Vector3D wierzcholekD,Vector3D wierzcholekE,
    Vector3D wierzcholekF,Vector3D wierzcholekG,Vector3D wierzcholekH,Vector3D srodek)
    {
        wierzcholki[0]=wierzcholekA;
        wierzcholki[1]=wierzcholekB;
        wierzcholki[2]=wierzcholekC;
        wierzcholki[3]=wierzcholekD;
        wierzcholki[4]=wierzcholekE;
        wierzcholki[5]=wierzcholekF;
        wierzcholki[6]=wierzcholekG;
        wierzcholki[7]=wierzcholekH;
        

        for(int i = 0; i < ILWIERZCHOLKOW; ++i)   
        wierzcholki[i] = wierzcholki[i] + srodek; 

    }

/** 
 * Konstruktor bezparametryczny dla klasy prostopadloscian
*/

prostopadloscian::prostopadloscian()
{
    for (int i=0 ; i<ILWIERZCHOLKOW ;i++)
    {
        wierzcholki[i] = Vector3D();
    }
        srodek=Vector3D();
    

}


/** 
 * Przeciazenie operatora [], ktore zwraca wartosc wierzcholka prostopadloscianu w danym miejscu
*/
const Vector3D &prostopadloscian::operator[](int wspolrzedna) const
{
    if (wspolrzedna < 0 || wspolrzedna >= ILWIERZCHOLKOW){
        throw std::runtime_error("Nie ma takiego indeksu prostopadloscianu.");
    }
    return wierzcholki[wspolrzedna];
}


/**                  Zwraca wartosc wierzcholka prostopadloscianu w danym miejscu                */



Vector3D &prostopadloscian::operator[](int wspolrzedna)
{
    return const_cast <Vector3D &> (const_cast <const prostopadloscian *> (this)->operator[](wspolrzedna));
}


std::ostream &operator<<(std::ostream &out, prostopadloscian const &rec)
{

    for (int i = 0; i < 8; i++)
    {
       
            out << rec[i] << std::endl;
            if((i+1)%2==0)
         out << std::endl;
    }

    return out;
}

/**-----------------------------------------------------------| 
|                                                             |
|           Metoda przesuniecia figury o dany wektor          |
|                              lub                            |
|                       obrotu o zadany kat                   |
|                                                             |
|-------------------------------------------------------------*/


void prostopadloscian::przemieszczenie(Vector3D const & wektor_przes,Matrix3x3 const & macierz_obrotu)
{
    Matrix3x3 macierz_chwilowa = macierz_obrotu;
        for (int i = 0; i < ILWIERZCHOLKOW; ++i)
        {
            wierzcholki[i] = (macierz_chwilowa * wierzcholki[i]) + wektor_przes + srodek;
        }

}





void prostopadloscian::wpisz_wspolrzedne_do_pliku(const char *sNazwaPliku) const
{
    std::ofstream StrumienPlikowy;
    Vector3D P1,P2, temp_vec[]={wierzcholki[0],wierzcholki[7],wierzcholki[2],wierzcholki[5]};
     
    StrumienPlikowy.open(sNazwaPliku);
    if (!StrumienPlikowy.is_open()){
      throw std::runtime_error("Operacja otwarcia pliku nie powiodla sie.");
    }
    
    P1 = (temp_vec[0] + temp_vec[1])/2;
    P2 = (temp_vec[2] + temp_vec[3])/2;

    StrumienPlikowy << P1 << std::endl
             << wierzcholki[6] << std::endl
             << wierzcholki[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;

    StrumienPlikowy << P1 << std::endl
             << wierzcholki[7] << std::endl
             << wierzcholki[5] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    StrumienPlikowy << P1 << std::endl
             << wierzcholki[1] << std::endl
             << wierzcholki[3] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    StrumienPlikowy << P1 << std::endl
             << wierzcholki[0] << std::endl
             << wierzcholki[2] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    StrumienPlikowy << P1 << std::endl
             << wierzcholki[6] << std::endl
             << wierzcholki[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    StrumienPlikowy.close();
}





bool czyrowneboki(double const tablica[]){
    for (int i = 0; i < 4 ; ++i)
        for (int j = i + 1; j < 4; ++j){
            if (tablica[i] - tablica[j] < -MAKSYMALNAROZNICA || tablica[i] - tablica[j] > MAKSYMALNAROZNICA )
              return false;
        }
    return true;
}



/** 
 * Metoda dla klasy prostopadloscian sprawdzajaca, czy po jakiejkolwiek operacji figura nadal jest 
 * prostopadloscianem na podstawie jego bokow i ich dlugosci
*/


void prostopadloscian::czy_prostopadloscian() const{
 
    double  A[4] = {length(wierzcholki[0],wierzcholki[1]), length(wierzcholki[2],wierzcholki[3]), length(wierzcholki[4],wierzcholki[5]), length(wierzcholki[6],wierzcholki[7])},
            B[4] = {length(wierzcholki[0],wierzcholki[2]), length(wierzcholki[1],wierzcholki[3]), length(wierzcholki[4],wierzcholki[6]), length(wierzcholki[5],wierzcholki[7])},
            C[4] = {length(wierzcholki[0],wierzcholki[6]), length(wierzcholki[1],wierzcholki[7]), length(wierzcholki[2],wierzcholki[4]), length(wierzcholki[3],wierzcholki[5])};
            
    if (czyrowneboki(A)){
        if (A[0] == B[0])
            std::cout << "Przeciwlegle boki sa sobie rowne." << std::endl;
        else if (A[0] > B[0])
            std::cout << "Przeciwlegle, dluzsze boki prostopadloscianu sa sobie rowne." << std::endl;
        else 
            std::cout << "rzeciwlegle, krotsze boki prostopadloscianu sa sobie rowne." << std::endl;
    }   
    else {
        if (A[0] == B[0]){
            std::cout << "Przeciwlegle boki nie sa sobie rowne." << std::endl;
        }
        else if (A[0] > B[0])
            std::cout << "Przeciwlegle, dluzsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
        else 
            std::cout << "Przeciwlegle, krotsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
    }
    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << A[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << A[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << A[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << A[3] << std::endl << std::endl;

    if (czyrowneboki(B)){
        if (A[0] == B[0])
            std::cout << "Przeciwlegle boki sa sobie rowne." << std::endl;
        else if (B[0] > A[0])
            std::cout << "Przeciwlegle, dluzsze boki prostopadloscianu sa sobie rowne." << std::endl;
        else 
            std::cout << "Przeciwlegle, krotsze boki prostopadloscianu sa sobie rowne." << std::endl;
    }   
    else{
        if (A[0] == B[0]){
            std::cout << "Przeciwlegle boki nie sa sobie rowne." << std::endl;
        }
        else if (B[0] > A[0])
            std::cout << "Przeciwlegle, dluzsze boki prostopadloscianu nie sa sobie rowne." << std::endl;
        else 
            std::cout << "Przeciwlegle, krotsze boki prostopadloscianu nie sa sobie rowne." << std::endl;  
    }
    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << B[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << B[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << B[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << B[3] << std::endl << std::endl;

    if (czyrowneboki(C))
        std::cout << ":) Poprzeczne boki prostopadloscianu sa sobie rowne." << std::endl;
    else 
        std::cout << ":( Poprzeczne boki prostopadloscianu nie sa sobie rowne." << std::endl;       

    std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(20) << C[0] << std::endl 
              << "\tDlugosc drugiego boku: "   << std::fixed << std::setprecision(20) << C[1] << std::endl 
              << "\tDlugosc trzeciego boku: "  << std::fixed << std::setprecision(20) << C[2] << std::endl 
              << "\tDlugosc czwartego boku: "  << std::fixed << std::setprecision(20) << C[3] << std::endl << std::endl;
}