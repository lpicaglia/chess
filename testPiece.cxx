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
#include "string.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

// Vérifie la validité des coordonnées saisie
bool coordonneeValide(string coord){
    if(coord.length() == 2){
        coord[0] = toupper(coord[0]);
        if(coord[0] >= 'A' && coord[0] <= 'H' && coord[1] >= '1' && coord[1] <= '8'){
            return true;
        }
    }
    return false;
}

/**
 * Programme principal
 */
int main( int argc, char** argv )
{
  string origine, destination;
  int origXInt, origYInt, destXInt, destYInt;

  JoueurBlanc jb;
  JoueurNoir jn;

  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);

  e.affiche();

  for(int i=1; i<=2; i++){

      // Saisie des coordonnées de la pièce a déplacer
      while(!coordonneeValide(origine)){
        cout << "Veuillez saisir les coordonnées de la pièce que vous souhaitez déplacer :" << endl;
        cin >> origine;
        if(!coordonneeValide(origine)){
            cout << "Coordonnées non valide ! Veuillez recommencer (ex. : A1)." << endl;
        }
        else{
            origXInt = toupper(origine[0])-64;
            origYInt = origine[1]-48;
        }
      }

      origine = "";

      // Saisie des coordonnées de la case de destination de la pièce
      while(!coordonneeValide(destination)){
        cout << "Veuillez saisir les coordonnées de la case de destination de la pièce :" << endl;
        cin >> destination;
        if(!coordonneeValide(destination)){
            cout << "Coordonnées non valide ! Veuillez recommencer (ex. : A1)." << endl;
        }
        else{
            destXInt = toupper(destination[0])-64;
            destYInt = destination[1]-48;
        }
      }

      destination = "";

      Piece * p = e.getPiece(origXInt, origYInt);

      // Test du déplacement d'une pièce
      if(p != NULL && p -> mouvementValide(e,destXInt, destYInt)){
        cout << "DEBUG : Premier déplacement" << endl;
        e.deplacer(p, destXInt, destYInt);
      }
      else{
        cout << "DEBUG : Déplacement impossible !!!" << endl;
      }

      e.affiche();
    }
}
