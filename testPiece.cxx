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
  int nbTour = 1;
  bool tourBlanc = true;

  JoueurBlanc jb;
  JoueurNoir jn;

  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);

  cout << "*============================================================*" << endl;
  cout << "|                  ________  __________________              |" << endl;
  cout << "|                 / ____/ / / / ____/ ___/ ___/              |" << endl;
  cout << "|                / /   / /_/ / __/  \\__ \\\\__ \\               |" << endl; 
  cout << "|               / /___/ __  / /___ ___/ /__/ /               |" << endl;
  cout << "|               \\____/_/ /_/_____//____/____/                |" << endl;
  cout << "|                                                            |" << endl;
  cout << "*============================================================*" << endl;                            

  e.affiche();

  while(!jb.isMat() && !jn.isMat()){      

      if(tourBlanc){
        cout << endl << "===================== TOUR " << nbTour << " DU JOUEUR BLANC =====================" << endl << endl;
      }
      else{
        cout << endl << "===================== TOUR " << nbTour << " DU JOUEUR NOIR =====================" << endl << endl;
      }

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

      //Victoire joueur blanc
      if(jn.isMat()){

        cout << "     ______  __  ________  _____    ___  __   ___   _  _______  _      _______  __" << endl;
        cout << " __ / / __ \\/ / / / __/ / / / _ \\  / _ )/ /  / _ | / |/ / ___/ | | /| / /  _/ |/ /" << endl;
        cout << "/ // / /_/ / /_/ / _// /_/ / , _/ / _  / /__/ __ |/    / /__   | |/ |/ // //    / " << endl;
        cout << "\\___/\\____/\\____/___/\\____/_/|_| /____/____/_/ |_/_/|_/\\___/   |__/|__/___/_/|_/  " << endl;

      }

      //Victoire joueur noir
      if(jb.isMat()){

        cout << "     ______  __  ________  _____    _  ______  _______    _      _______  __" << endl;
        cout << " __ / / __ \\/ / / / __/ / / / _ \\  / |/ / __ \\/  _/ _ \\  | | /| / /  _/ |/ /" << endl;
        cout << "/ // / /_/ / /_/ / _// /_/ / , _/ /    / /_/ // // , _/  | |/ |/ // //    / " << endl;
        cout << "\\___/\\____/\\____/___/\\____/_/|_| /_/|_/\\____/___/_/|_|   |__/|__/___/_/|_/  " << endl;

      }

      //Changement de joueur
      if(tourBlanc){
        tourBlanc = false;
      }
      else{
        nbTour++;
        tourBlanc = true;
      }

      origine = "";
      destination = "";
    }
    
    cout << "  ________   __  _______  ____ _   _________ " << endl;
    cout << " / ___/ _ | /  |/  / __/ / __ \\ | / / __/ _ \\" << endl;
    cout << "/ (_ / __ |/ /|_/ / _/  / /_/ / |/ / _// , _/" << endl;
    cout << "\\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_| " << endl;
}
