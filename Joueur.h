/**
 * Header de Joueur.cxx
 *
 * @file Joueur.h
 */

#if !defined Joueur_h
#define Joueur_h

#include <vector>
#include "Piece.h"
#include "Echiquier.h"

using namespace std;

class Joueur{

 protected:
  vector<Piece*> m_pieces;
  string joueurName;
 public:
  Joueur();
  Joueur(bool white);
  ~Joueur();
  void affiche();
  bool isWhite();
  void placerPieces(Echiquier &e);
  void setName(string name);
  string getName();
};

class JoueurBlanc : public Joueur{

 public:
  JoueurBlanc();
};

class JoueurNoir : public Joueur{

 public:
  JoueurNoir();
};

#endif
