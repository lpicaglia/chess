/**
 * Header de Echiquier.cxx
 *
 * @file Echiquier.h
 */

#if !defined Echiquier_h
#define Echiquier_h

#include "Piece.h"

class Echiquier
{
private:
   Piece* m_cases[ 64 ];

public:

  Echiquier();
  Piece* getPiece( int x, int y );
  bool placer( Piece* p );
  bool deplacer( Piece* p, int x, int y );
  Piece* enleverPiece( int x, int y );
  void affiche();

};

#endif // !defined Echiquier_h

