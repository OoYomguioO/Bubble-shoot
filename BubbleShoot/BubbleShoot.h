
// BubbleShoot.h : fichier d'en-tête principal de l'application BubbleShoot
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'pch.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       // symboles principaux


// CBubbleShootApp :
// Consultez BubbleShoot.cpp pour l'implémentation de cette classe
//

class CBubbleShootApp : public CWinAppEx
{
public:
	CBubbleShootApp() noexcept;


// Substitutions
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implémentation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBubbleShootApp theApp;
