#ifndef __CTIREUR_H
#define __CTIREUR_H

#pragma once
class CTireur
{
protected:
	int m_couleur;
	int m_posBulleX;
	int m_posBulleY;
	int m_posSourisX;
	int m_posSourisY;
	int m_posInitBulleX;
	int m_posInitBulleY;
	int m_posTireX;
	int m_posTireY;
	bool m_sensTire;
	bool m_tire;
	int m_vie;
	int m_difficulte;
	int m_vieperdue;
	int* m_bullsuiv;

public:

	CTireur();
	CTireur(int difficulte, int vie);

	void setPosBulle(int X, int Y);
	void setPosSouris(int X, int Y);
	void setPosInitBulle(int X, int Y);
	void setPosTire(int X, int Y);
	void tire(int X, int Y);
	void setTire(bool b);

	int getPosBulleX();
	int getPosBulleY();
	int getPosInitBulleX();
	int getPosInitBulleY();
	int getPosSourisX();
	int getPosSourisY();
	int getPosTireX();
	int getPosTireY();
	int getCouleur();
	bool isTire();

	void afficheViseur(CDC* pDC, COLORREF Couleur);
	void afficheBulle(CDC* pDC);
	void affichageVie(CDC* pDC);
	void updateBulle(CRect rect);

};

#endif