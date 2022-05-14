#include "pch.h"
#include "CTireur.h"

CTireur::CTireur()
	: m_tire(false)
	, m_posInitBulleX(800)
	, m_posInitBulleY(800)
	, m_difficulte(6)
	, m_couleur(0)
	, m_vie(3)
	, m_vieperdue(0)
{
	m_bullsuiv = new int[m_vie];
	m_posBulleX = m_posInitBulleX;
	m_posBulleY = m_posInitBulleY;
	for (int i = 0; i < m_vie; i++) // remplissage initiale du buffer de bullles
	{
		m_bullsuiv[i] = 1 + rand() % m_difficulte;
	}

}

CTireur::CTireur(int difficulte, int vie)
	: m_tire(false)
	, m_posInitBulleX(800)
	, m_posInitBulleY(800)
	, m_couleur(0)
	, m_vie(vie)
	, m_difficulte(difficulte)
	, m_vieperdue(0)
{
	m_bullsuiv = new int[m_vie];
	m_posBulleX = m_posInitBulleX;
	m_posBulleY = m_posInitBulleY;
	for (int i = 0; i < m_vie; i++) // remplissage initiale du buffer de bullles
	{
		m_bullsuiv[i] = 1 + rand() % difficulte;
	}
}

void CTireur::setPosBulle(int X, int Y)
{
	m_posBulleX = X;
	m_posBulleY = Y;
}

void CTireur::setPosSouris(int X, int Y)
{
	m_posSourisX = X;
	m_posSourisY = Y;
}

void CTireur::setPosInitBulle(int X, int Y)
{
	m_posInitBulleX = X;
	m_posInitBulleY = Y;
}

void CTireur::setPosTire(int X, int Y)
{
	m_posTireX = X;
	m_posTireY = Y;
}

//Méthode qui permette d’initialiser le tir 
void CTireur::tire(int X, int Y)
{
	if (!m_tire &&  Y < m_posInitBulleY)
	{
		setPosTire(X, Y);
		setPosBulle(m_posInitBulleX, m_posInitBulleY);
		m_couleur = m_bullsuiv[m_vie-1];
		m_tire = true;
		m_sensTire = false;

		for (int i = m_vie; i > 0; i--)
			m_bullsuiv[i - 1] = m_bullsuiv[i - 2];

		m_bullsuiv[0] = 1 + rand() % m_difficulte;
	}
}

void CTireur::setTire(bool b)
{
	m_tire = b;
}

int CTireur::getPosBulleX()
{
	return m_posBulleX;
}

int CTireur::getPosBulleY()
{
	return m_posBulleY;
}

int CTireur::getPosInitBulleX()
{
	return m_posInitBulleX;
}

int CTireur::getPosInitBulleY()
{
	return m_posInitBulleY;
}

int CTireur::getPosSourisX()
{
	return m_posSourisX;
}

int CTireur::getPosSourisY()
{
	return m_posSourisY;
}

int CTireur::getPosTireX()
{
	return m_posTireX;
}

int CTireur::getPosTireY()
{
	return m_posTireY;
}

int CTireur::getCouleur()
{
	return m_couleur;
}


bool CTireur::isTire()
{
	return m_tire;
}

//Méthode qui permet d’afficher le viseur 
//si la couleur passer en paramètre et de la même couleur que le fond, efface le viseur
void CTireur::afficheViseur(CDC* pDC, COLORREF Couleur)
{
	if (m_posSourisY > m_posInitBulleY) m_posSourisY = m_posInitBulleY;

	CPen penViseur(PS_SOLID, 5, Couleur);
	pDC->SelectObject(&penViseur);
	pDC->MoveTo(m_posInitBulleX, m_posInitBulleY);
	pDC->LineTo(m_posInitBulleX - 100 * (m_posInitBulleX - m_posSourisX) / sqrt(pow(m_posInitBulleX - m_posSourisX, 2) + pow(m_posInitBulleY - m_posSourisY, 2)), m_posInitBulleY - 100 * (m_posInitBulleY - m_posSourisY) / sqrt(pow(m_posInitBulleX - m_posSourisX, 2) + pow(m_posInitBulleY - m_posSourisY, 2)));
}


//Méthode qui affiche la bulle
void CTireur::afficheBulle(CDC* pDC)
{
	CBrush penbleu(RGB(0, 0, 255));
	CBrush pencyan(RGB(0, 255, 255));
	CBrush penjaune(RGB(255, 255, 0));
	CBrush penrouge(RGB(255, 0, 0));
	CBrush penvert(RGB(0, 255, 0));
	CBrush penmagenta(RGB(255, 0, 255));
	CBrush penorange(RGB(255, 200, 0));
	CBrush penrose(RGB(255, 140, 250));

	if (m_couleur == 1) CBrush* poldbrush = pDC->SelectObject(&penbleu);
	if (m_couleur == 2) CBrush* poldbrush = pDC->SelectObject(&pencyan);
	if (m_couleur == 3) CBrush* poldbrush = pDC->SelectObject(&penjaune);
	if (m_couleur == 4) CBrush* poldbrush = pDC->SelectObject(&penmagenta);
	if (m_couleur == 5) CBrush* poldbrush = pDC->SelectObject(&penrouge);
	if (m_couleur == 6) CBrush* poldbrush = pDC->SelectObject(&penvert);
	if (m_couleur == 7) CBrush* poldbrush = pDC->SelectObject(&penorange);
	if (m_couleur == 8) CBrush* poldbrush = pDC->SelectObject(&penrose);

	pDC->Ellipse(m_posBulleX - 25, m_posBulleY - 25, m_posBulleX + 25, m_posBulleY + 25);
}

//Méthode qui affiche la vie du joueur
void CTireur::affichageVie(CDC* pDC)
{
	int positionx = 300; // pas utile de faire un lien avec le rect puisque l'origine du rect de bouge pas 
	int positiony = 800;

	CBrush penbleu(RGB(0, 0, 255));
	CBrush pencyan(RGB(0, 255, 255));
	CBrush penjaune(RGB(255, 255, 0));
	CBrush penrouge(RGB(255, 0, 0));
	CBrush penvert(RGB(0, 255, 0));
	CBrush penmagenta(RGB(255, 0, 255));
	CBrush penorange(RGB(255, 200, 0));
	CBrush penrose(RGB(255, 140, 250));


	for (int i = 0; i < m_vie; i++)
	{
		if (m_bullsuiv[i] == 1) CBrush* poldbrush = pDC->SelectObject(&penbleu);
		if (m_bullsuiv[i] == 2) CBrush* poldbrush = pDC->SelectObject(&pencyan);
		if (m_bullsuiv[i] == 3) CBrush* poldbrush = pDC->SelectObject(&penjaune);
		if (m_bullsuiv[i] == 4) CBrush* poldbrush = pDC->SelectObject(&penmagenta);
		if (m_bullsuiv[i] == 5) CBrush* poldbrush = pDC->SelectObject(&penrouge);
		if (m_bullsuiv[i] == 6) CBrush* poldbrush = pDC->SelectObject(&penvert);
		if (m_bullsuiv[i] == 7) CBrush* poldbrush = pDC->SelectObject(&penorange);
		if (m_bullsuiv[i] == 8) CBrush* poldbrush = pDC->SelectObject(&penrose);

		pDC->Ellipse(positionx - 22 + (i * 50), positiony - 25, positionx + 25 + (i * 50), positiony + 22);
	}
}

//Méthode qui permet de mettre à jour la position de la bulle
void CTireur::updateBulle(CRect rect)
{
	float ang = atan(((float)m_posTireY - (float)m_posInitBulleY) / ((float)m_posTireX - (float)m_posInitBulleX));
	
	if (m_posBulleY <= rect.TopLeft().y) m_tire = false;
	if (m_posBulleX - 25 <= rect.TopLeft().x || m_posBulleX + 25 >= rect.TopLeft().x + rect.Width()) m_sensTire = !m_sensTire;

	if (m_posTireX > m_posInitBulleX)
	{
		m_posBulleX += 10 * cos(ang)*pow(-1, m_sensTire);
		m_posBulleY += 10 * sin(ang);
	}

	else
	{
		m_posBulleX -= 10 * cos(ang)*pow(-1, m_sensTire);
		m_posBulleY -= 10 * sin(ang);
	}
}