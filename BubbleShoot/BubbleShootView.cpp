
// BubbleShootView.cpp : implémentation de la classe CBubbleShootView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS peuvent être définis dans les gestionnaires d'aperçu, de miniature
// et de recherche d'implémentation de projet ATL, et permettent le partage de code de document avec ce projet.
#ifndef SHARED_HANDLERS
#include "BubbleShoot.h"
#endif

#include "BubbleShootDoc.h"
#include "BubbleShootView.h"
#include "Cdlgniv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBubbleShootView

IMPLEMENT_DYNCREATE(CBubbleShootView, CView)

BEGIN_MESSAGE_MAP(CBubbleShootView, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBubbleShootView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// construction/destruction de CBubbleShootView

CBubbleShootView::CBubbleShootView() noexcept
	: m_penfond(PS_SOLID, 0, RGB(106, 182, 233))
	, m_brushfond(RGB(106, 182, 233))
	, m_fenetre(0, 0, 1900, 900)
	, m_rect(m_fenetre.CenterPoint().x - 450, m_fenetre.CenterPoint().y - 400, m_fenetre.CenterPoint().x + 450, m_fenetre.CenterPoint().y + 400)
{
	//m_fenetre = CRect(0, 0, 1900, 900);
	//m_rect = CRect(m_fenetre.CenterPoint().x - 450, m_fenetre.CenterPoint().y - 400, m_fenetre.CenterPoint().x + 450, m_fenetre.CenterPoint().y + 400);
	//m_brushfond = CBrush(RGB(106, 182, 233));
	//m_penfond = CPen(PS_SOLID, 0, RGB(106, 182, 233));
}

CBubbleShootView::~CBubbleShootView()
{
}

BOOL CBubbleShootView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// dessin de CBubbleShootView

void CBubbleShootView::OnDraw(CDC* pDC)
{
	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//Initialise le timer
	SetTimer(1, 1, NULL);

	//Affiche les différents éléments du jeu 
	pDC->SelectObject(&m_brushfond);
	pDC->Rectangle(m_rect);

	pDoc->m_Tireur->setPosInitBulle(m_rect.CenterPoint().x, m_rect.bottom);
	pDoc->m_Partie->Affichage(m_rect, pDC);
	pDoc->m_Tireur->affichageVie(pDC);


	pDC->TextOut(200, 310, _T("BubbleShoot"));
	pDC->TextOut(245, 330, _T("by"));
	pDC->TextOut(120, 350, _T("Guillaume Herpin & Sevan Larue"));
	pDC->TextOut(200, 500, _T("Scores:"));

	pDC->TextOut(20, 650, _T("Clic gauche pour tirer"));
	pDC->TextOut(20, 670, _T("Clic droit pour changer de niveau de difficulte"));
	
	CString temp;
	temp.Format(_T("%d"), pDoc->m_Partie->getScore());
	pDC->TextOut(270, 500, temp);

	pDoc->m_Partie->setUpdate(false);
	ReleaseDC(pDC);
}


// impression de CBubbleShootView


void CBubbleShootView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBubbleShootView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// préparation par défaut
	return DoPreparePrinting(pInfo);
}

void CBubbleShootView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez une initialisation supplémentaire avant l'impression
}

void CBubbleShootView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez un nettoyage après l'impression
}

void CBubbleShootView::OnRButtonUp(UINT  nFlags , CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	Cdlgniv dlg;
	INT_PTR Result = dlg.DoModal();
	if (Result == IDOK)
	{
		if (dlg.m_choix == 1) OnBnClickedfacile();
		if (dlg.m_choix == 2) OnBnClickednormal();
		if (dlg.m_choix == 3) OnBnClickeddifficile();
	}
}

void CBubbleShootView::OnContextMenu(CWnd* pWnd , CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDD_DIALOG1, point.x, point.y, this, TRUE);
#endif
}


// diagnostics de CBubbleShootView

#ifdef _DEBUG
void CBubbleShootView::AssertValid() const
{
	CView::AssertValid();
}

void CBubbleShootView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBubbleShootDoc* CBubbleShootView::GetDocument() const // la version non Debug est inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBubbleShootDoc)));
	return (CBubbleShootDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages de CBubbleShootView


//Initialise le jeu en mode facile
void CBubbleShootView::OnBnClickedfacile()
{
	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_Partie->m_tab != NULL) delete[] pDoc->m_Partie->m_tab;
	pDoc->m_Partie = new CPlateau(17,10, 6);

	m_rect = CRect(m_fenetre.CenterPoint().x - 450, m_fenetre.CenterPoint().y - 400, m_fenetre.CenterPoint().x + 100, m_fenetre.CenterPoint().y + 400);
	pDoc->m_Tireur = new CTireur(6, 4);

	RedrawWindow();
}


//Initialise le jeu en mode normal
void CBubbleShootView::OnBnClickednormal()
{
	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_Partie->m_tab != NULL) delete[] pDoc->m_Partie->m_tab;
	pDoc->m_Partie = new CPlateau(15, 17, 6);

	m_rect = CRect(m_fenetre.CenterPoint().x - 450, m_fenetre.CenterPoint().y - 400, m_fenetre.CenterPoint().x + 450, m_fenetre.CenterPoint().y + 400);
	pDoc->m_Tireur = new CTireur(6, 3);

	RedrawWindow();
}


//Initialise le jeu en mode difficile
void CBubbleShootView::OnBnClickeddifficile()
{
	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if (pDoc->m_Partie->m_tab != NULL) delete[] pDoc->m_Partie->m_tab;
	pDoc->m_Partie = new CPlateau(17, 20, 8);
	
	m_rect = CRect(m_fenetre.CenterPoint().x - 450, m_fenetre.CenterPoint().y - 400, m_fenetre.CenterPoint().x + 600, m_fenetre.CenterPoint().y + 400);
	pDoc->m_Tireur = new CTireur(8, 2);
	RedrawWindow();

}

//tir
void CBubbleShootView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);

	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->m_Tireur->tire(point.x, point.y);

	RedrawWindow(0);
}


void CBubbleShootView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CDC* pDC = GetDC();

	pDoc->m_Tireur->afficheViseur(pDC, RGB(106, 182, 233));
	pDoc->m_Tireur->setPosSouris(point.x, point.y);
	pDoc->m_Tireur->afficheViseur(pDC, RGB(0, 0, 0));
}


void CBubbleShootView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);

	CBubbleShootDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();

	CPen* poldpen = pDC->SelectObject(&m_penfond);
	CBrush* poldbrush = pDC->SelectObject(&m_brushfond);

	if (pDoc->m_Tireur->isTire())
	{
		pDC->Ellipse(pDoc->m_Tireur->getPosBulleX() - 25, pDoc->m_Tireur->getPosBulleY() - 25, pDoc->m_Tireur->getPosBulleX() + 25, pDoc->m_Tireur->getPosBulleY() + 25);
		
		pDoc->m_Tireur->updateBulle(m_rect);
		pDoc->m_Tireur->afficheBulle(pDC);
		pDoc->m_Partie->Collision(m_rect, pDoc->m_Tireur);
	}

	pDoc->m_Tireur->afficheViseur(pDC, RGB(0, 0, 0));

	ReleaseDC(pDC);
	if (pDoc->m_Partie->isUpdate()) RedrawWindow(0);
}
