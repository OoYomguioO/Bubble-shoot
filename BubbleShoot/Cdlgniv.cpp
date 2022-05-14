// Cdlgniv.cpp : fichier d'implémentation
//

#include "pch.h"
#include "BubbleShoot.h"
#include "Cdlgniv.h"
#include "afxdialogex.h"


// boîte de dialogue de Cdlgniv

IMPLEMENT_DYNAMIC(Cdlgniv, CDialog)

Cdlgniv::Cdlgniv(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_choix(0)

{

}

Cdlgniv::~Cdlgniv()
{
}

void Cdlgniv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


}


BEGIN_MESSAGE_MAP(Cdlgniv, CDialog)


	ON_BN_CLICKED(IDC_RADIO1, &Cdlgniv::OnBnClickedfacile)
	ON_BN_CLICKED(IDC_RADIO2, &Cdlgniv::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Cdlgniv::OnBnClickedRadio3)
END_MESSAGE_MAP()


// gestionnaires de messages de Cdlgniv




void Cdlgniv::OnBnClickedfacile()
{
	m_choix = 1;
}


void Cdlgniv::OnBnClickedRadio2()
{
	m_choix = 2;
}


void Cdlgniv::OnBnClickedRadio3()
{
	m_choix = 3;
}
