/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"


// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

bool compare(Piece pa, Piece pb)
{
  if ( (pa.x()==pb.x()) && (pa.y()==pb.y()) )
    return true;
  return false;
}

/**
 * Programme principal
 */
int main( int argc, char** argv )
{
  string jbName, jnName;

  JoueurBlanc jb;
  JoueurNoir jn;

  cout << "Veuillez saisir le nom du joueur blanc : ";
  cin >> jbName;
  jb.setName(jbName);

  cout << "Veuillez saisir le nom du joueur noir : ";
  cin >> jnName;
  jn.setName(jnName);

  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);

  e.affiche();

  /*
  Roi rb(true);
  rb.affiche();
  Roi rn(false);
  rn.affiche();
  Reine qb(true);
  qb.affiche();
  Reine qn(false);
  qn.affiche();

  e.enleverPiece(5,1);
  e.placer(&rb);
  e.enleverPiece(5,8);
  e.placer(&rn);
  e.enleverPiece(4,1);
  e.placer(&qb);
  e.enleverPiece(4,8);
  e.placer(&qn);

  Piece* ptr;
  ptr=&rb;
  Roi* rptr;
  rptr=dynamic_cast<Roi*>(ptr);
  if (rptr==NULL)
    cout << "cast impossible" << endl;
  else
    cout << "cast reussi" << endl;
  */

  // les objets definis dans cette fonction sont automatiquement d�truits.
  // Ex : p1

  cout << "Joueur blanc = " << jb.getName() << "\n";
  cout << "Joueur noir = " << jn.getName() << "\n";
}
