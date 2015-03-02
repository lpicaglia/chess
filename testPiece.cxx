/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include <cstdlib>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"
#include "string.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

// Vérifie si un joueur est en échec
bool isEchec(Joueur &defenseur, Joueur &attaquant, Echiquier &e)
{
  Piece* roi = NULL;
  char codeATrouver = (defenseur.isWhite()?'R':'r');

  // Récupération des pointeurs des pièces des deux joueur
  vector<Piece *> p_defenseur = defenseur.getPieces();
  vector<Piece *> p_attaquant = attaquant.getPieces();

  int i = 0;
  // Parcour des pièces du defenseur pour retrouver son roi
  while (i < p_defenseur.size()){

    // Vérifie si on trouve le roi
    if(p_defenseur[i]->codePiece() == codeATrouver){
      roi = p_defenseur[i];
    }
    i++;
  }

  i = 0;
  // Parcour des pièces de l'attaquant
  while (i < p_attaquant.size()){
    if(p_attaquant[i]->mouvementValide(e, roi->x(), roi->y())){
      return true;
    }
    i++;
  }
  return false;
}

// Vérifie si un joueur est mat
bool isMat(Joueur &defenseur, Joueur &attaquant, Echiquier &e)
{
  Piece* roi = NULL;
  char codeATrouver = (defenseur.isWhite()?'R':'r');

  // Récupération des pointeurs des pièces des deux joueur
  vector<Piece *> p_defenseur = defenseur.getPieces();
  vector<Piece *> p_attaquant = attaquant.getPieces();

  
  // Parcour des pièces du defenseur pour retrouver son roi
  int i = 0;
  while (i < p_defenseur.size()){

    // Vérifie si on trouve le roi
    if(p_defenseur[i]->codePiece() == codeATrouver){
      roi = p_defenseur[i];
    }
    i++;
  }

  // On recupère les cases que le roi controle
  vector<int*> roiCtrl;
  bool case_libre = false;

  // Tant qu'il n'y a pas de case de libre
  while(!case_libre){
    roiCtrl = roi->ctrlCases(e);
    
    // Parcour des cases libre sur lesquelles le roi peut se rendre
    int j = 0;
    while(j < roiCtrl.size()){
      /*cout << "DEBUG : Roi controle x : " << roiCtrl[j][0] << " y : " << roiCtrl[j][1] << endl;*/
      
      // Parcour des pièces de l'attaquant
      int k = 0;
      while(k < p_attaquant.size() && !case_libre){

        case_libre = true;
        // Vérifie si la pièce de l'attaquant peut attaquer la case
        if(p_attaquant[k]->mouvementValide(e, roiCtrl[j][0], roiCtrl[j][1])){
          /*cout << "DEBUG : Casse x : " << roiCtrl[j][0] << " y : " << roiCtrl[j][1] << " attaqué !" << endl;*/
          
          case_libre = false;
        }
        k++;
      }
      j++;
    }
  }

  return (case_libre)?false:true;
}

// Vérifie la validité des coordonnées saisie
bool coordonneeValide(string coord)
{
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
  bool finPartie = false;

  JoueurBlanc jb;
  JoueurNoir jn;

  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);

  system("clear");

  while(!finPartie){      

      cout << "*============================================================*" << endl;
      cout << "|                  ________  __________________              |" << endl;
      cout << "|                 / ____/ / / / ____/ ___/ ___/              |" << endl;
      cout << "|                / /   / /_/ / __/  \\__ \\\\__ \\               |" << endl; 
      cout << "|               / /___/ __  / /___ ___/ /__/ /               |" << endl;
      cout << "|               \\____/_/ /_/_____//____/____/                |" << endl;
      cout << "|                                                            |" << endl;
      cout << "*============================================================*" << endl;   

      e.affiche();

      // Vérifie la mise en echec
      if(!finPartie && (isEchec(jn, jb, e) || isEchec(jb, jn, e))){

        cout << "      ___________ ___________" << endl;
        cout << "     / __/ ___/ // / __/ ___/" << endl;
        cout << "    / _// /__/ _  / _// /__  " << endl;
        cout << "   /___/\\___/_//_/___/\\___/  " << endl;
      }

      if(tourBlanc){
        cout << endl << "===================== TOUR " << nbTour << " DU JOUEUR BLANC =====================" << endl << endl;
      }
      else{
        cout << endl << "===================== TOUR " << nbTour << " DU JOUEUR NOIR  =====================" << endl << endl;
      }

      // Saisie des coordonnées de la pièce a déplacer
      while(!coordonneeValide(origine)){
        cout << "Veuillez saisir les coordonnées de la pièce que vous souhaitez déplacer :" << endl;
        cin >> origine;
        if(!coordonneeValide(origine)){
            cout << endl << "/!\\ Coordonnées non valide ! Veuillez recommencer (ex. : A1). /!\\" << endl << endl;
        }
        else{
            origXInt = toupper(origine[0])-64;
            origYInt = origine[1]-48;
        }
      }

      Piece * p = e.getPiece(origXInt, origYInt);

      if(p != NULL){
        if((tourBlanc && p->isWhite()) || (!tourBlanc && p->isBlack())){ 

          // Saisie des coordonnées de la case de destination de la pièce
          while(!coordonneeValide(destination)){
            cout << "Veuillez saisir les coordonnées de la case de destination de la pièce :" << endl;
            cin >> destination;
            if(!coordonneeValide(destination)){
                cout << endl << "/!\\ Coordonnées non valide ! Veuillez recommencer (ex. : A1). /!\\" << endl << endl;
            }
            else{
                destXInt = toupper(destination[0])-64;
                destYInt = destination[1]-48;
            }
          }

          // Test du déplacement d'une pièce
          if(p -> mouvementValide(e,destXInt, destYInt)){
            system("clear");
            e.deplacer(p, destXInt, destYInt);

            //Victoire joueur blanc
            if(isMat(jn, jb, e)){

              cout << "            ___________ ___________       __     __  ______ ______  ______" << endl;
              cout << "           / __/ ___/ // / __/ ___/  ___ / /_   /  |/  / _ /_  __/ / / / /" << endl;
              cout << "          / _// /__/ _  / _// /__   / -_) __/  / /|_/ / __ |/ /   /_/_/_/ " << endl;
              cout << "         /___/\\___/_//_/___/\\___/   \\__/\\__/  /_/  /_/_/ |_/_/   (_|_|_)  " << endl;
              cout << "     ______  __  ________  _____    ___  __   ___   _  _______  _      _______  __" << endl;
              cout << " __ / / __ \\/ / / / __/ / / / _ \\  / _ )/ /  / _ | / |/ / ___/ | | /| / /  _/ |/ /" << endl;
              cout << "/ // / /_/ / /_/ / _// /_/ / , _/ / _  / /__/ __ |/    / /__   | |/ |/ // //    / " << endl;
              cout << "\\___/\\____/\\____/___/\\____/_/|_| /____/____/_/ |_/_/|_/\\___/   |__/|__/___/_/|_/  " << endl;

              finPartie = true;
            }

            //Victoire joueur noir
            if(isMat(jb, jn, e)){

              cout << "          ___________ ___________       __     __  ______ ______  ______" << endl;
              cout << "         / __/ ___/ // / __/ ___/  ___ / /_   /  |/  / _ /_  __/ / / / /" << endl;
              cout << "        / _// /__/ _  / _// /__   / -_) __/  / /|_/ / __ |/ /   /_/_/_/ " << endl;
              cout << "       /___/\\___/_//_/___/\\___/   \\__/\\__/  /_/  /_/_/ |_/_/   (_|_|_)  " << endl;
              cout << "     ______  __  ________  _____    _  ______  _______    _      _______  __" << endl;
              cout << " __ / / __ \\/ / / / __/ / / / _ \\  / |/ / __ \\/  _/ _ \\  | | /| / /  _/ |/ /" << endl;
              cout << "/ // / /_/ / /_/ / _// /_/ / , _/ /    / /_/ // // , _/  | |/ |/ // //    / " << endl;
              cout << "\\___/\\____/\\____/___/\\____/_/|_| /_/|_/\\____/___/_/|_|   |__/|__/___/_/|_/  " << endl;

              finPartie = true;
            }

            //Changement de joueur
            if(tourBlanc){
              tourBlanc = false;
            }
            else{
              nbTour++;
              tourBlanc = true;
            }
          }
          else{
            system("clear");
            cout << endl <<"/!\\ Déplacement Interdit /!\\" << endl;
          }
        }
        else{
          system("clear");
          cout << endl << "/!\\ Vous ne pouvez choisir une pièce qui n'est pas de votre couleur. /!\\" << endl;
        }
      }
      else{
        system("clear");
        cout << endl << "/!\\ Aucune pièces ne se trouve aux coordonnées que vous avez saisi. /!\\" << endl;
      }
      origine = "";
      destination = "";
    }
    
    cout << "              ________   __  _______  ____ _   _________ " << endl;
    cout << "             / ___/ _ | /  |/  / __/ / __ \\ | / / __/ _ \\" << endl;
    cout << "            / (_ / __ |/ /|_/ / _/  / /_/ / |/ / _// , _/" << endl;
    cout << "            \\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_| " << endl << endl;
}
