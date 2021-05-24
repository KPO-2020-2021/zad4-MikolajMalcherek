#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <filesystem>
#include <vector>

#include "Wector.hh"
#include "Macierz.hh"
#include "Macierz3x3.hh"
#include "prostopadloscian.hh"
#include "lacze_do_gnuplota.hh"




class Scena{
    private:
        /*! \brief  */
        std::vector <prostopadloscian> wszystkie_prostopadlosciany;
        
        /*! \brief  */
        std::vector <Matrix3x3> macierze_obrotu;

        /*! \brief  */
        std::vector <Vector3D> wektory_przesuniecia;

    public:
        /*! \brief  */
        Scena();

        /*! \brief  */
        ~Scena();
        
        /*! \brief  */
        void ruszanie_prostopadloscianem(int index);
        
        /*! \brief  */
        void update_matrix(Matrix3x3 const & mtx, int index);

        /*! \brief  */
        void update_vector(Vector3D const & vec,int index);
        
        /*! \brief  */
        Matrix3x3 odczytajmacierz(int index);
        
        /*! \brief . */
        const prostopadloscian & operator [] (unsigned int index) const;

        /*! \brief  */
        int ileprostopadloscianow();        

        /*! \brief  */
        void dodaj_prostopad(Vector3D const & Apx0, double const & tra_OX, double const & tra_OY, double const & tra_OZ);
};