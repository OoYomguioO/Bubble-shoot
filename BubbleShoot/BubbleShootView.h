
// BubbleShootView.h : interface de la classe CBubbleShootView
//

#pragma once


class CBubbleShootView : public CView
{
protected: // création à partir de la sérialisation uniquement
	CBubbleShootView() noexcept;
	DECLARE_DYNCREATE(CBubbleShootView);

// Attributs
public:
	CBubbleShootDoc* GetDocument() const;
	CRect m_fenetre;
	CRect m_rect;
	CBrush m_brushfond;
	CPen m_penfond;

// Opérations
public:
	 void OnBnClickedfacile();
	 void OnBnClickednormal();
	 void OnBnClickeddifficile();

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implémentation
public:
	virtual ~CBubbleShootView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // version Debug dans BubbleShootView.cpp
inline CBubbleShootDoc* CBubbleShootView::GetDocument() const
   { return reinterpret_cast<CBubbleShootDoc*>(m_pDocument); }
#endif

