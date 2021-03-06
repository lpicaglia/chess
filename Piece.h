/**
 * Header de Piece.cxx
 *
 * @file Piece.h
 */

#if !defined Piece_h
#define Piece_h

#include <vector>

using namespace std;

//#include "Echiquier.h"
class Echiquier;

/**
 * Declaration d'une classe modélisant une piece de jeu d'echec.
 */
class Piece{

protected:
  int m_x;
  int m_y;
  bool m_white;

public:
  Piece();
  virtual ~Piece();
  Piece( int x, int y, bool white );
  Piece( const Piece & autre );
  Piece & operator=(const Piece & autre);
  virtual bool mouvementValide(Echiquier &e, int x, int y);
  void init( int x, int y, bool white );
  void move( int x, int y );
  int x();
  int y();
  bool isWhite();
  bool isBlack();
  void affiche();
  virtual char codePiece();
  vector<int*> ctrlCases(Echiquier &e);
};

class Roi : virtual public Piece{
  
public:
  Roi(bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char codePiece();
  bool roque(Echiquier &e, int x, int y);
};

class Tour : virtual public Piece{

public:
  Tour(bool white, bool left);
  bool mouvementValide(Echiquier &e, int x, int y);
  char codePiece();
};

class Fou : virtual public Piece{

public:
  Fou(bool white, bool left);
  bool mouvementValide(Echiquier &e, int x, int y);
  char codePiece();
};

class Reine : public Tour, public Fou{

public:
  Reine(bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char codePiece();
};

class Cavalier : public Tour, public Fou{

public:
  Cavalier(bool white, bool left);
  bool mouvementValide(Echiquier &e, int x, int y);
  char codePiece();
};

class Pion : virtual public Piece{

private:
  bool m_premierDeplacement;

public:
  Pion(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char codePiece();
};


#endif // !defined Piece_h
