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

/*bool isJoueurEnEchec(Joueur* joueurToCheck,Joueur* attaquant, Echiquier* e){
  cout<<"DEBUG:debut isJoueurEnEchec"<<endl;
  bool ret = false;
  vector<Piece*> findTheKing = joueurToCheck->getPieces();
  Piece* roi=NULL;
  for(vector<Piece*>::size_type i=0;i<findTheKing.size();i++){
    if(findTheKing[i]->codePiece()==(joueurToCheck->isWhite()?'R':'r')){
      roi = findTheKing[i];
      cout<<"DEBUG:roi trouvé"<<endl<< roi->x() << endl << roi->y() << endl;
    }
  }
  if (roi==NULL){
    return false;
  }
  for(vector<Piece*>::size_type i=0;i<attaquant->getPieces().size();i++){
    if(attaquant->getPieces()[i]->mouvementValide(e, roi->x(), roi->y())){
      cout<<"DEBUG:joueur en echec"<<endl;
      ret = true;
    }
  }
  cout<<"DEBUG:fin isJoueurEchec"<<endl;
  return ret;
}*/

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

    // Vérifie si on trouve le roi blanc
    if(p_defenseur[i]->codePiece() == codeATrouver){
      cout << "DEBUG : Roi trouvé" << endl;
      roi = p_defenseur[i];
    }
    i++;
  }

  i = 0;
  // Parcour des pièces de l'attaquant
  while (i < p_attaquant.size()){
    if(p_attaquant[i]->mouvementValide(e, roi->x(), roi->y())){
      cout << "DEBUG : Mise en echec " << p_attaquant[i]->codePiece() << " -> "<< roi->codePiece() << endl;
      cout << " roi => X : " << roi->x() << " ; Y : " << roi->y() << endl;
      cout << " attaquant => X : " << p_attaquant[i]->x() << " ; Y : " << p_attaquant[i]->y() << endl;
      return true;
    }
    i++;
  }

  cout << "DEBUG : Pas d'échec" << endl;
  return false;
}

// Vérifie si un joueur est mat
bool isMat(Joueur* joueur, Echiquier* e)
{
  return false;
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

  cout << "*============================================================*" << endl;
  cout << "|                  ________  __________________              |" << endl;
  cout << "|                 / ____/ / / / ____/ ___/ ___/              |" << endl;
  cout << "|                / /   / /_/ / __/  \\__ \\\\__ \\               |" << endl; 
  cout << "|               / /___/ __  / /___ ___/ /__/ /               |" << endl;
  cout << "|               \\____/_/ /_/_____//____/____/                |" << endl;
  cout << "|                                                            |" << endl;
  cout << "*============================================================*" << endl;                            

  e.affiche();

  while(!finPartie){      

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
        e.deplacer(p, destXInt, destYInt);

        // Echec joueur noir
        if(isEchec(jn, jb, e) || isEchec(jb, jn, e)){

            cout << "      ___________ ___________" << endl;
            cout << "     / __/ ___/ // / __/ ___/" << endl;
            cout << "    / _// /__/ _  / _// /__  " << endl;
            cout << "   /___/\\___/_//_/___/\\___/  " << endl;
        }

      }
      else{
        cout << "DEBUG : Déplacement impossible !!!" << endl;
      }

      e.affiche();

      //Victoire joueur blanc
      if(isMat(&jn, &e)){

        cout << "     ______  __  ________  _____    ___  __   ___   _  _______  _      _______  __" << endl;
        cout << " __ / / __ \\/ / / / __/ / / / _ \\  / _ )/ /  / _ | / |/ / ___/ | | /| / /  _/ |/ /" << endl;
        cout << "/ // / /_/ / /_/ / _// /_/ / , _/ / _  / /__/ __ |/    / /__   | |/ |/ // //    / " << endl;
        cout << "\\___/\\____/\\____/___/\\____/_/|_| /____/____/_/ |_/_/|_/\\___/   |__/|__/___/_/|_/  " << endl;

      }

      //Victoire joueur noir
      if(isMat(&jb, &e)){

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
