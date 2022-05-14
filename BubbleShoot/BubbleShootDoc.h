
// BubbleShootDoc.h : interface de la classe CBubbleShootDoc
//

#pragma once

#include "CPlateau.h"
#include "CTireur.h"


class CBubbleShootDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CBubbleShootDoc() noexcept;
	DECLARE_DYNCREATE(CBubbleShootDoc)

// Attributs
public:
	CPlateau* m_Partie;
	CTireur* m_Tireur;



// Opérations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implémentation
public:
	virtual ~CBubbleShootDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()


#ifdef SHARED_HANDLERS
	// Fonction d'assistance qui définit le contenu de recherche pour un gestionnaire de recherche
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnRafraichir();

};


