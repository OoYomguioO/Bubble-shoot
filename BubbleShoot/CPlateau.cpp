#include "pch.h"
#include "CPlateau.h"
#include "time.h"


CPlateau::CPlateau()
    : m_ligne(15)
    , m_colonne(17)
    , m_score(0)
	, m_update(false)
	, m_diametre(50)
	, m_difficulte(6)

{
	m_tab = new int[m_ligne * m_colonne];

    for (int i = 0; i < getLigne() * 2/3 * getColonne(); i++)
    {
		m_tab[i] = 1 + rand() % m_difficulte;
    }

    for (int i = getLigne() * 2/3 * getColonne(); i < getLigne() * getColonne(); i++)
    {
		m_tab[i] = 0;
    }
}

CPlateau::CPlateau(int ln, int cl, int m_difficulte)
    : m_score(0)
	, m_update(false)
	, m_diametre(50)
{
    setLigne(ln);
    setColonne(cl);
    
	m_tab = new int[m_ligne * m_colonne];
	m_tabDestruction = new int[0];
	m_difficulte = m_difficulte;

    for (int i = 0; i < getLigne() * 2 / 3 * getColonne(); i++)
    {
		m_tab[i] = 1 + rand() % m_difficulte;
    }

    for (int i = getLigne() * 2 / 3 * getColonne(); i < getLigne() * getColonne(); i++)
    {
		m_tab[i] = 0;
    }
}

CPlateau::~CPlateau()
{
    delete[] m_tab;
	delete[] m_tabDestruction;
}

int CPlateau::getLigne()
{
    return m_ligne;
}

int CPlateau::getColonne()
{
    return m_colonne;
}

int CPlateau::getScore()
{
    return m_score;
}

int CPlateau::getTab(int i)
{
    return m_tab[i];
}

int CPlateau::getTabLength()
{
	return m_ligne * m_colonne;
}

bool CPlateau::isUpdate()
{
	return m_update;
}

void CPlateau::setLigne(int ln)
{
	m_ligne = ln;
}

void CPlateau::setColonne(int cl)
{
	m_colonne = cl;
}

void CPlateau::setUpdate(bool up)
{
	m_update = up;
}

//mMthode qui permet d’afficher le tableau
//La variable lgpaire permet de gérer le décalage du tableau
void CPlateau::Affichage(CRect rect, CDC* pDC)
{
	bool lgpaire;

	if (m_ligne % 2 == 0) lgpaire = true;
	else lgpaire = false;

	CBrush penbleu(RGB(0, 0, 255));
	CBrush pencyan(RGB(0, 255, 255));
	CBrush penjaune(RGB(255, 255, 0));
	CBrush penrouge(RGB(255, 0, 0));
	CBrush penvert(RGB(0, 255, 0));
	CBrush penmagenta(RGB(255, 0, 255));
	CBrush penvide(RGB(255, 255, 255));
	CBrush penorange(RGB(255, 200, 0));
	CBrush penrose(RGB(255, 140, 250));

	// ---------------- affichage du tabelau -----------------

	for (int i = 0; i < m_ligne; i++) // ligne
	{

		lgpaire = !lgpaire;

		for (int j = 0; j < m_colonne; j++) // colonne 
		{
			// 1 -> bleu
			// 2 -> cyan
			// 3 -> jaune
			// 4 -> magnenta
			// 5 -> rouge
			// 6 -> vert
			// 7 -> orange
			// 8 -> rose

			if (m_tab[i * m_colonne + j] == 0) continue;
			if (m_tab[i * m_colonne + j] == 1) CBrush* poldbrush = pDC->SelectObject(&penbleu);
			if (m_tab[i * m_colonne + j] == 2) CBrush* poldbrush = pDC->SelectObject(&pencyan);
			if (m_tab[i * m_colonne + j] == 3) CBrush* poldbrush = pDC->SelectObject(&penjaune);
			if (m_tab[i * m_colonne + j] == 4) CBrush* poldbrush = pDC->SelectObject(&penmagenta);
			if (m_tab[i * m_colonne + j] == 5) CBrush* poldbrush = pDC->SelectObject(&penrouge);
			if (m_tab[i * m_colonne + j] == 6) CBrush* poldbrush = pDC->SelectObject(&penvert);
			if (m_tab[i * m_colonne + j] == 7) CBrush* poldbrush = pDC->SelectObject(&penorange);
			if (m_tab[i * m_colonne + j] == 8) CBrush* poldbrush = pDC->SelectObject(&penrose);
			
			pDC->Ellipse((rect.TopLeft().x) + m_diametre * (j + 0.5 * lgpaire)//x1
				, (rect.TopLeft().y) + m_diametre * i //y1
				, (rect.TopLeft().x) + m_diametre * (j + 1 + 0.5 * lgpaire)  // x2
				, (rect.TopLeft().y) + m_diametre * (i + 1)); //y2
		}
	}
}

//Méthode récursive qui permet de génère le tableau de destruction
void CPlateau::Destruction(int Pos, int C)
{
	//Agrandi le tableau destruction 
	m_tailleTabDestruction++;
	int* temp = new int[m_tailleTabDestruction];

	for (int i = 0; i < m_tailleTabDestruction - 1; i++)
		temp[i]=m_tabDestruction[i];

	delete[] m_tabDestruction;
	m_tabDestruction = new int[m_tailleTabDestruction];

	for (int i = 0; i < m_tailleTabDestruction - 1; i++)
		m_tabDestruction[i]=temp[i] ;

	delete[] temp;

	m_tabDestruction[m_tailleTabDestruction-1] = Pos;

	
	//Vérifie si les bulles adjacentes ne sont pas déjà dans le tableau
	bool DesHaut = true;
	bool DesBas = true;
	bool DesDroit = true;
	bool DesGauche = true;

	for (int i = 0; i < m_tailleTabDestruction; i++)
	{
		
		if ((m_tabDestruction[i] == Pos + 1)) DesDroit = false;
		if ((m_tabDestruction[i] == Pos - 1)) DesGauche = false;
		if ((m_tabDestruction[i] == Pos + m_colonne)) DesBas = false;
		if ((m_tabDestruction[i] == Pos - m_colonne)) DesHaut = false;
		
	}

	//Vérifie si les bulles adjacentes sont de la même couleur 
	if ((m_tab[Pos + 1] == C) && DesDroit) Destruction(Pos + 1, C);
	if ((m_tab[Pos - 1] == C) && DesGauche) Destruction(Pos - 1, C);
	if ((m_tab[Pos + m_colonne] == C) && DesBas) Destruction(Pos + m_colonne, C);
	if ((m_tab[Pos - m_colonne] == C) && DesHaut) Destruction(Pos - m_colonne, C);
}

//Méthode qui gère la collision des bulles
void CPlateau::Collision(CRect rect, CTireur* tir)
{
	bool lgpaire;
	int position=0;

	if (m_ligne % 2 == 0) lgpaire = true;
	else lgpaire = false;


	for (int i = 0; i < getLigne(); i++)
	{
		lgpaire = !lgpaire;

		for (int j = 0; j < getColonne(); j++)
		{
			int centreX = rect.TopLeft().x + m_diametre * (j + 0.5 * lgpaire) + m_diametre / 2;
			int centreY = rect.TopLeft().y + m_diametre * i + m_diametre / 2;

			//Vérifie s’il y a collision 
			if ((sqrt(pow(centreX - tir->getPosBulleX(), 2) + pow(centreY - tir->getPosBulleY(), 2))) < m_diametre && m_tab[i * m_colonne + j] != 0)
			{
				tir->setTire(false);
				
				//Vérifie où placer la bulle dans le tableau
				if ((tir->getPosBulleY() >= centreY) && (tir->getPosBulleX() <= centreX)) position = (i + 1) * getColonne() + j - 1 * !lgpaire;
				if ((tir->getPosBulleY() >= centreY) && (tir->getPosBulleX() >= centreX)) position = (i + 1) * getColonne() + j + 1 * lgpaire;
				if ((tir->getPosBulleX() >= centreX) && (tir->getPosBulleY() <= centreY + m_diametre / 2) && (tir->getPosBulleY() >= centreY - m_diametre / 2)) position = i * getColonne() + j + 1;
				if ((tir->getPosBulleX() <= centreX) && (tir->getPosBulleY() <= centreY + m_diametre / 2) && (tir->getPosBulleY() >= centreY - m_diametre / 2)) position = i * getColonne() + j - 1;
				
				m_tab[position]= tir->getCouleur();
				m_update = true;
				
				//Initialise le tableau destruction 
				m_tabDestruction = new int[0];
				m_tailleTabDestruction = 0;
				Destruction(position, tir->getCouleur());

				//Supprime les bulles
				if (m_tailleTabDestruction>=3){
					for (int i = 0; i < m_tailleTabDestruction; i++)
					{
						m_tab[m_tabDestruction[i]] = 0;
					}
					m_score += m_tailleTabDestruction * 10;
				}
				delete[] m_tabDestruction;
			}
			if (!tir->isTire()) break;
		}
		if (!tir->isTire()) break;
	}
}

