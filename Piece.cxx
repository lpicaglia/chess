/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include <iostream>
#include "Piece.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

Piece::Piece()
{
  // ne fait rien => objet instancie mais non valide.
  cout << "Constructeur Piece" << endl;
}

Piece::~Piece()
{
   cout << "Destructeur Piece" << endl;
}

Piece::Piece(const Piece & autre)
{
   cout << "Constructeur Piece par copie" << endl;
   m_x=autre.m_x;
   m_y=autre.m_y;
   m_white=autre.m_white;
}

Piece &
Piece::operator=(const Piece & autre)
{
  cout << "Operateur affectation Piece" << endl;
  m_x=autre.m_x;
  m_y=autre.m_y;
  m_white=autre.m_white;
  return *this;
}

Piece::Piece( int x, int y, bool white )
{
  cout << "Constructeur Piece Specialise" << endl;
  m_x = x;
  m_y = y;
  m_white = white;
}

bool
Piece::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Piece" << endl;
  return false;
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
  cout << "Piece: x=" << m_x << " y=" << m_y << " "
       << ( m_white ? "blanche" : "noire" ) << endl;
}

char
Piece::codePiece()
{
  if (m_white) return 'P';
  return 'p';
}

Roi::Roi(bool white) : Piece(5,(white?1:8),white)
{
  cout << "Constructeur Roi" << endl;
}

bool
Roi::roque()
{
  cout << "Roque Roi" << endl;
  return false;
}

Tour::Tour(bool white, bool left) : Piece((left?1:8),(white?1:8),white)
{
  cout << "Constructeur Tour" << endl;
}

Fou::Fou(bool white, bool left) : Piece((left?3:6),(white?1:8),white)
{
  cout << "Constructeur Fou" << endl;
}

Reine::Reine(bool white) : Piece(4,(white?1:8),white), Fou(white,true), Tour(white,true)
{
  cout << "Constructeur Reine" << endl;
}

bool
Roi::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Roi" << endl;
  return false;
}

bool
Tour::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Tour" << endl;
  return false;
}

bool
Fou::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Fou" << endl;
  return false;
}

bool
Reine::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Reine" << endl;
  return Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y);
}

char
Roi::codePiece()
{
  return (m_white)?'R':'r';
}

char
Tour::codePiece()
{
  return (m_white)?'T':'t';
}

char
Fou::codePiece()
{
  return (m_white)?'F':'f';
}

char
Reine::codePiece()
{
  return (m_white)?'Q':'q';
}

