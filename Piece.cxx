/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include <iostream>
#include <stdlib.h>
#include "Piece.h"
#include "Echiquier.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

//---------------------------------------------------------------------------
//                                 Classe Piece
//---------------------------------------------------------------------------

Piece::Piece()
{
  //cout << "Constructeur Piece" << endl;
}

Piece::~Piece()
{
  //cout << "Destructeur Piece" << endl;
}

Piece::Piece(const Piece & autre)
{
   //cout << "Constructeur Piece par copie" << endl;
   m_x=autre.m_x;
   m_y=autre.m_y;
   m_white=autre.m_white;
}

Piece &
Piece::operator=(const Piece & autre)
{
  //cout << "Operateur affectation Piece" << endl;
  m_x=autre.m_x;
  m_y=autre.m_y;
  m_white=autre.m_white;
  return *this;
}

Piece::Piece( int x, int y, bool white )
{
  //cout << "Constructeur Piece Specialise" << endl;
  m_x = x;
  m_y = y;
  m_white = white;
}

bool
Piece::mouvementValide(Echiquier &e, int x, int y)
{
    // Vérifie si la pièce est sur l'échiquier
    if(x < 1 || x > 8 || y < 1 || y > 8){
        return false;
    }

    // Vérifie si les coordonnées de destination sont différentes des coordonnées d'origine
    if(x==m_x && y == m_y){
        return false;
    }

    // Vérifie si une pièce se trouve déjà sur la case de destination
    if(e.getPiece(x, y)){
        // Vérifie si la pièce présente sur la case est de la meme couleur
        if(e.getPiece(x, y) -> m_white == m_white){
            return false;
        }
    }
    return true;
}

void
Piece::init( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
}

void
Piece::move( int x, int y )
{
  m_x = x;
  m_y = y;
}

int
Piece::x()
{
  return m_x;
}

int
Piece::y()
{
  return m_y;
}

bool
Piece::isWhite()
{
  return m_white;
}


bool
Piece::isBlack()
{
  return !m_white;
}

void
Piece::affiche()
{
  //cout << "Piece: x=" << m_x << " y=" << m_y << " "
  //     << ( m_white ? "blanche" : "noire" ) << endl;
}

char
Piece::codePiece()
{
  return (m_white)?'B': 'n';
}

vector<int*>
Piece::ctrlCases(Echiquier &e)
{
    vector<int*> m_ctrl;

    for(int i = 1; i < 9 ; i++){
        for(int j = 1; j < 9; j++){
            if(mouvementValide(e,i,j)){
                int* coord = new int[2]();
                coord[0] = i;
                coord[1] = j;
                m_ctrl.push_back(coord);
            }
        }
    }
    return m_ctrl;
}

//---------------------------------------------------------------------------
//                                 Classe Roi
//---------------------------------------------------------------------------

Roi::Roi(bool white) : Piece(5,(white?1:8),white)
{
  //cout << "Constructeur Roi" << endl;
}

bool
Roi::roque()
{
    if(m_white){

    }
    else{


    }
    return false;
}

bool
Roi::mouvementValide(Echiquier &e, int x, int y)
{
    if(Piece::mouvementValide(e, x, y)){

        if(abs(x-m_x) == 1 || abs(y-m_y) == 1){
            return true;
        }
    }
    return false;
}

char
Roi::codePiece()
{
  return (m_white)?'R':'r';
}

//---------------------------------------------------------------------------
//                                 Classe Tour
//---------------------------------------------------------------------------

Tour::Tour(bool white, bool left) : Piece((left?1:8),(white?1:8),white)
{
  //cout << "Constructeur Tour" << endl;
}

bool
Tour::mouvementValide(Echiquier &e, int x, int y)
{
    if(Piece::mouvementValide(e, x, y)){

        // Déplacement horizontale
        if(y == m_y){

            // Vérifie si une piece gène le déplacement
            for(int i = min(x, m_x)+1 ; i < max(x, m_x); i++){
                if(e.getPiece(i,y)){
                    return false;
                }
            }
            return true;
        }

        // Déplacement verticale
        if(x == m_x){

            // Vérifie si une piece gène le déplacement
            for(int i = min(y, m_y)+1 ; i < max(y, m_y); i++){
                if(e.getPiece(x,i)){
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

char
Tour::codePiece()
{
  return (m_white)?'T':'t';
}

//---------------------------------------------------------------------------
//                                 Classe Fou
//---------------------------------------------------------------------------

Fou::Fou(bool white, bool left) : Piece((left?3:6),(white?1:8),white)
{
  //cout << "Constructeur Fou" << endl;
}

bool
Fou::mouvementValide(Echiquier &e, int x, int y)
{
    if(Piece::mouvementValide(e, x, y)){

        // Vérifie si les valeurs absolues des coordonnées sont identique
        if(abs(x-m_x) == abs(y-m_y)){

            int axeY;

            if((x > m_x && y < m_y) || (x < m_x && y > m_y)){
                axeY = max(y,m_y)-1;
            }
            else{
                axeY = min(y,m_y)+1;
            }

            for(int i=min(x,m_x)+1 ; i<max(x,m_x); i++){

                // Vérifie si une piece gène le déplacement
                if(e.getPiece(i,axeY)){
                    return false;
                }

                if((x > m_x && y < m_y) || (x < m_x && y > m_y)){
                    axeY--;
                }
                else{
                    axeY++;
                }
            }
            return true;
        }
    }
    return false;
}

char
Fou::codePiece()
{
  return (m_white)?'F':'f';
}

//---------------------------------------------------------------------------
//                                 Classe Reine
//---------------------------------------------------------------------------

Reine::Reine(bool white) : Piece(4,(white?1:8),white), Fou(white,true), Tour(white,true)
{
  //cout << "Constructeur Reine" << endl;
}

bool
Reine::mouvementValide(Echiquier &e, int x, int y)
{

    if(Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y)){
        return true;
    }
    return false;
}

char
Reine::codePiece()
{
  return (m_white)?'Q':'q';
}

//---------------------------------------------------------------------------
//                                 Classe Cavalier
//---------------------------------------------------------------------------

Cavalier::Cavalier(bool white, bool left) : Piece((left?2:7),(white?1:8),white), Fou(white,true), Tour(white,true)
{
  //cout << "Constructeur Cavalier" << endl;
}

bool
Cavalier::mouvementValide(Echiquier &e, int x, int y)
{

    if(!Fou::mouvementValide(e,x,y) && !Tour::mouvementValide(e,x,y)){

        if((abs(x - m_x) == 2 && abs(y - m_y) == 1) || (abs(x - m_x) == 1 && abs(y - m_y) == 2)){
            return true;
        }
    }
    return false;
}

char
Cavalier::codePiece()
{
  return (m_white)?'C':'c';
}

//---------------------------------------------------------------------------
//                                 Classe Pion
//---------------------------------------------------------------------------

Pion::Pion(int x, int y, bool white ) : Piece(x,y,white)
{
    premierDeplacement = true;
}

bool
Pion::mouvementValide(Echiquier &e, int x, int y)
{

    if(x == m_x){
        if(!e.getPiece(x,y)){
            // Vérifie si le pion s'est déjà déplacé
            if(premierDeplacement && abs(y - m_y) == 2){

                // Premier déplacement d'un pion blanc
                if(m_white && y > m_y){

                     // Vérifie si une piece gène le déplacement
                    if(!e.getPiece(m_x,(m_y+1))){
                        premierDeplacement = false;
                        return true;
                    }
                }

                // Premier déplacement d'un pion noir
                if(!m_white && y < m_y){

                    // Vérifie si une piece gène le déplacement
                    if(!e.getPiece(m_x,(m_y-1))){
                        premierDeplacement = false;
                        return true;
                    }
                }
            }
            else{
                if(y == (m_y+1) && m_white){
                    premierDeplacement = false;
                    return true;
                }

                if(y == (m_y-1) && !m_white){
                    premierDeplacement = false;
                    return true;
                }
            }
        }
    }

    // Attaque du pion en diagonale
    if(abs(x - m_x) == abs(y - m_y ) && abs(x-m_x) == 1){

        if(Piece* p = e.getPiece(x,y)){

            if(m_white && p->isWhite() != m_white && y == (m_y+1)){
                premierDeplacement = false;
                return true;
            }

            if(!m_white && p->isWhite() != m_white && y == (m_y-1)){
                premierDeplacement = false;
                return true;
            }
        }
    }

    // En passant pion blanc
    if(m_white && m_y == 5 && y == (m_y+1)){

        if(Piece* p = e.getPiece((m_x-1), m_y)){
            if(p -> codePiece() == 'p' && x == (m_x-1)){
                e.enleverPiece((m_x-1), m_y);
                return true;
            }
        }

        if(Piece* p = e.getPiece((m_x+1), m_y)){
            if(p -> codePiece() == 'p' && x == (m_x+1)){
                e.enleverPiece((m_x+1), m_y);
                return true;
            }
        }
    }

    // En passant pion noir
    if(!m_white && m_y == 4 && y == (m_y-1)){

        if(Piece* p = e.getPiece((m_x-1), m_y)){
            if(p-> codePiece() == 'P' && x == (m_x-1)){
                e.enleverPiece((m_x-1), m_y);
                return true;
            }
        }

        if(Piece* p = e.getPiece((m_x+1), m_y)){
            if(p -> codePiece() == 'P' && x == (m_x+1)){
                e.enleverPiece((m_x+1), m_y);
                return true;
            }
        }
    }
    return false;
}

char
Pion::codePiece()
{
  return (m_white)?'P':'p';
}