#include <iostream>
#include "Joueur.h"

using namespace std;

Joueur::Joueur()
{
  //cout << "Constructeur Joueur defaut" << endl;
}

Joueur::~Joueur()
{
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      delete *p;
      p++;
    }
  //cout << "Destructeur Joueur" << endl;
}

Joueur::Joueur(bool white)
{

}

void
Joueur::affiche(){
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      (*p)->affiche();
      p++;
    }
}

bool
Joueur::isWhite()
{
  return m_pieces[0]->isWhite();
}

void
Joueur::placerPieces(Echiquier &e)
{
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      e.placer(*p);
      p++;
    }
}

JoueurBlanc::JoueurBlanc() //: Joueur(true)
{
  //cout << "Constructeur Joueur Blanc" << endl;
  Roi* rb = new Roi(true);
  Reine* qb = new Reine(true);
  Fou* fbl = new Fou(true, true);
  Fou* fbr = new Fou(true, false);
  Tour* tbl = new Tour(true, true);
  Tour* tbr = new Tour(true, false);
  Cavalier* cbl = new Cavalier(true, true);
  Cavalier* cbr = new Cavalier(true, false);

  m_pieces.push_back(rb);
  m_pieces.push_back(qb);
  m_pieces.push_back(fbl);
  m_pieces.push_back(fbr);
  m_pieces.push_back(tbl);
  m_pieces.push_back(tbr);
  m_pieces.push_back(cbl);
  m_pieces.push_back(cbr);


  for (int i=1; i<=8; i++){
	  Piece* p = new Pion(i,2, true);
	  m_pieces.push_back(p);
  }
}

JoueurNoir::JoueurNoir(){
  //cout << "Constructeur Joueur Noir" << endl;
  Roi* rn = new Roi(false);
  Reine* qn = new Reine(false);
  Fou* fnl = new Fou(false, true);
  Fou* fnr = new Fou(false, false);
  Tour* tnl = new Tour(false, true);
  Tour* tnr = new Tour(false, false);
  Cavalier* cnl = new Cavalier(false, true);
  Cavalier* cnr = new Cavalier(false, false);

  m_pieces.push_back(rn);
  m_pieces.push_back(qn);
  m_pieces.push_back(fnl);
  m_pieces.push_back(fnr);
  m_pieces.push_back(tnl);
  m_pieces.push_back(tnr);
  m_pieces.push_back(cnl);
  m_pieces.push_back(cnr);

  for (int i=1; i<=8; i++){
	  Piece* p = new Pion(i,7, false);
	  m_pieces.push_back(p);
  }
}
