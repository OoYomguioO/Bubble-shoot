#pragma once


// boîte de dialogue de Cdlgniv

class Cdlgniv : public CDialog
{
	DECLARE_DYNAMIC(Cdlgniv)

public:
	Cdlgniv(CWnd* pParent = nullptr);   // constructeur standard
	virtual ~Cdlgniv();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
	
public:
	
	int m_choix;
	
	afx_msg void OnBnClickedfacile();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};
