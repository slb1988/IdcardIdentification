// pinyindlg.cpp : implementation of the CPinyinDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "pinyindlg.h"

LRESULT CPinyinDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CPinyinDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CPinyinDlg::GetChineseSpell(CString strText, CString& strPY)
{
	USES_CONVERSION;
	CStringW    strRw;
	int            iRet        = 0;
	wchar_t*    pwText        = NULL;
	int            i            = 0;
	int            j            = 0;
	if(!strText.IsEmpty())
	{
		pwText = (wchar_t*)(LPCTSTR)strText;
		for(i = 0; i< wcslen(pwText); i++)
		{
			if((pwText[i] >= L'£°' && pwText[i] <= L'£¹'))
			{
				strRw.AppendChar(L'0'+(pwText[i]-L'£°'));
			}
			else if(pwText[i] >= L'£Á' && pwText[i] <= L'£Ú')
			{
				strRw.AppendChar(L'A'+(pwText[i]-L'£Á'));
			}
			else if(pwText[i] >= L'£á' && pwText[i] <= L'£ú')
			{
				strRw.AppendChar(L'A'+(pwText[i]-L'£á'));
			}
			else if((pwText[i] >= L'a' && pwText[i] <= L'z') || (pwText[i] >= L'A' && pwText[i] <= L'Z'))
			{
				strRw.AppendChar(pwText[i]);
			}
			else if(int(pwText[i]) > 19968 && int(pwText[i]) <= 40869)
			{
				for(j = 0; j < _countof(g_TxtToPy); j++)
				{
					if(g_TxtToPy[j].Find(pwText[i]) > 0)
					{
						strRw.AppendChar(g_TxtToPy[j][0]);
						break;
					}
				}
			}
		}
	}
	strPY = W2A(strRw);
	return strPY.GetLength();
}

LRESULT CPinyinDlg::OnClickOk(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(TRUE);

	GetChineseSpell(m_word, m_ab);

	DoDataExchange(FALSE);

	return 0;	
}