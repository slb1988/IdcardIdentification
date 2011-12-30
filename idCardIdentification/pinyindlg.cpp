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

LRESULT CPinyinDlg::GetChineseSpell2(CString strText, CString& strPY)
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

	}
	char a, b;
	CString result;

	int word_num = strText.GetLength();
	strPY.Empty();

	for (int i = 0; i < word_num; ++i)
	{
		char cstr[8];
		memset(cstr, 0, 8);
		CString temp;
		USES_CONVERSION;
		temp = strText.GetAt(i);
		strcpy_s(cstr, 8, W2A(temp.LockBuffer()));
		temp.UnlockBuffer();
		a = cstr[0] - 160;
		b = cstr[1] - 160;

		int num = a*100+b;

		if (num >= 1601 && num <= 1636)
			strPY += L"A";
		else if (num >= 1637 && num <= 1832)
			strPY += L"B";
		else if (num >= 1833 && num <= 2077)
			strPY += L"C";
		else if (num >= 2078 && num <= 2273)
			strPY += L"D";
		else if (num >= 2274 && num <= 2301)
			strPY += L"E";
		else if (num >= 2302 && num <= 2432)
			strPY += L"F";
		else if (num >= 2433 && num <= 2593)
			strPY += L"G";
		else if (num >= 2594 && num <= 2786)
			strPY += L"H";
//		strPY += L"I";
		else if (num >= 2787 && num <= 3105)
			strPY += L"J";
		else if (num >= 3106 && num <= 3211)
			strPY += L"K";
		else if (num >= 3212 && num <= 3471)
			strPY += L"L";
		else if (num >= 3472 && num <= 3634)
			strPY += L"M";
		else if (num >= 3635 && num <= 3721)
			strPY += L"N";
		else if (num >= 3722 && num <= 3729)
			strPY += L"O";
		else if (num >= 3730 && num <= 3857)
			strPY += L"P";
		else if (num >= 3858 && num <= 4026)
			strPY += L"Q";
		else if (num >= 4027 && num <= 4085)
			strPY += L"R";
		else if (num >= 4086 && num <= 4389)
			strPY += L"S";
		else if (num >= 4390 && num <= 4557)
			strPY += L"T";
// 		else if (num >= 4684 && num <= 4924)
// 			strPY += L"U";
// 		else if (num >= 4925 && num <= 5248)
// 			strPY += L"V";
		else if (num >= 4558 && num <= 4683)
			strPY += L"W";
		else if (num >= 4684 && num <= 4924)
			strPY += L"X";
		else if (num >= 4925 && num <= 5248)
			strPY += L"Y";
		else if (num >= 5249 && num <= 5589)
			strPY += L"Z";
		else
			strPY += L" ";
	}
	return 0;
}

LRESULT CPinyinDlg::OnClickOk(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(TRUE);

	GetChineseSpell2(m_word, m_ab);

	DoDataExchange(FALSE);

	return 0;	
}