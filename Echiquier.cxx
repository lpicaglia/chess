/**
 * Mise en oeuvre de Echiquier.h
 *
 * @file Echiquier.cxx
 */

#include <iostream>
#include "Echiquier.h"

using namespace std;

Echiquier::Echiquier(){
  for (int i=0; i<64; i++)
    m_cases[i]=NULL;
}

Piece*
Echiquier::getPiece( int x, int y ){

  if ((x>=1) && (x<=8) && (y>=1) && (y<=8))
    return m_cases[(x-1)+8*(y-1)];
  return NULL;
}

bool
Echiquier::placer( Piece* p ){

  if (p==NULL) return false;
  int position=(p->x()-1)+8*(p->y()-1);
  if ((p->x()>=1) && (p->x()<=8) && (p->y()>=1) && (p->y()<=8) && m_cases[position]==NULL){
      m_cases[position]=p;
      return true;
  }
  return false;
}

bool
Echiquier::deplacer( Piece* p, int x, int y ){
    enleverPiece(p->x(), p->y());
    p->move(x,y);
    m_cases[(x-1)+8*(y-1)]=p;
    return true;
}

Piece*
Echiquier::enleverPiece( int x, int y ){
  if ((x>=1) && (x<=8) && (y>=1) && (y<=8) && getPiece(x,y)!=NULL){
      Piece * tmp=m_cases[(x-1)+8*(y-1)];
      m_cases[(x-1)+8*(y-1)]=NULL;
      return tmp;
  }
  return NULL;
}

void
Echiquier::affiche(){
  cout << endl << "  ABCDEFGH" << endl;
  for ( int y = 1; y <= 8; ++y ){
      cout << y << " ";
      for ( int x = 1; x <= 8; ++x ){
	  char c;
	  Piece* p = getPiece( x, y );
	  if ( p == 0 )
	    c = ( ( x + y ) % 2 ) == 0 ? '#' : '.';
	  else
	    c = p->codePiece();
	  cout << c;
	  }
      cout << " " << y << endl;
  }
  cout << "  ABCDEFGH" << endl;
}