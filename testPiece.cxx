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

  Piece * p = e.getPiece(2,1);

  // Test du déplacement d'une pièce
  if(p != NULL && p -> mouvementValide(e,3,3)){
    cout << "DEBUG : Premier déplacement" << endl;
    e.deplacer(p, 3, 3);
  }
  else{
    cout << "DEBUG : Déplacement impossible !!!" << endl;
  }

  e.affiche();

  p = e.getPiece(3, 3);
  // Test du déplacement d'une pièce
  if(p != NULL && p -> mouvementValide(e,4,6)){
    cout << "DEBUG : Second déplacement" << endl;
    e.deplacer(p, 4, 6);
  }
  else{
    cout << "DEBUG : Déplacement impossible !!!" << endl;
  }

  e.affiche();

  cout << "Joueur blanc = " << jb.getName() << endl;
  cout << "Joueur noir = " << jn.getName() << endl;
}
