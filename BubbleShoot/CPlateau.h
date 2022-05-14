#ifndef __CPLATEAU_H
#define __CPLATEAU_H

#include "CTireur.h"

#pragma once
class CPlateau
{
protected:
	int m_ligne;
	int m_colonne;
	int m_score;
	bool m_update;
	int m_diametre;
	int m_difficulte;

	int* m_tabDestruction;
	int m_tailleTabDestruction;

public:
	int* m_tab;

	CPlateau();
	CPlateau(int ln, int cl, int difficulte);
	~CPlateau();

	int getLigne();
	int getColonne();
	int getScore();
	int getTab(int i);
	int getTabLength();
	bool isUpdate();

	void setLigne(int ln);
	void setColonne(int cl);
	void setUpdate(bool up);

	void Affichage(CRect Rect, CDC* pDC);
	void Collision(CRect Rect, CTireur* tir);
	void Destruction(int Pos, int C);
};

#endif