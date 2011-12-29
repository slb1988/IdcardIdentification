// convertchinesegbdlg.cpp : implementation of the CConvertGBDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "convertchinesegbdlg.h"

LRESULT CConvertGBDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CConvertGBDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CConvertGBDlg::OnClickOk(WORD , WORD wID, HWND , BOOL& )
{
	DoDataExchange(TRUE);

	if ( !m_word.IsEmpty() )
		m_code = GetGBFromCString(m_word);
	else if ( !m_code.IsEmpty() )
		m_word = GetStringFromGB(m_code);
	else
		AtlMessageBox(NULL, L"请输入汉字或区位码！");

	DoDataExchange(FALSE);	

	return 0;
}

//汉字转化为区间码
CString CConvertGBDlg::GetGBFromCString(CString str)		
{
	char a, b;
	CString result;

	int word_num = str.GetLength();

	for (int i = 0; i < word_num; ++i)
	{
		char num[8];
		memset(num, 0, 8);
		CString temp;
		USES_CONVERSION;
		temp = str.GetAt(i);
		strcpy_s(num, 8, W2A(temp.LockBuffer()));
		temp.UnlockBuffer();
		a = num[0] - 160;
		b = num[1] - 160;

		temp.Format(L"%d%d", a, b);

		result += temp;
		result += L" ";
	}
	return result;
}

//区间码转化为汉字
CString CConvertGBDlg::GetStringFromGB(CString num_Str)			
{
	CString strResult;
	int word_num = num_Str.GetLength() / 4;

	for (int i = 0; i < word_num; ++i)
	{
		CString m_Num = num_Str.Mid(i*4, 4);
		char a[2];
		CString temp;
		temp = m_Num.Left(2);
		char num[8];
		memset(num, 0, 8);
		USES_CONVERSION;
		strcpy_s(num, 8, W2A(temp.LockBuffer()));
		temp.UnlockBuffer();
		a[0] = atoi(num) + 160;
		temp = m_Num.Right(2);
		strcpy_s(num, 8, W2A(temp.LockBuffer()));
		temp.UnlockBuffer();
		a[1] = atoi(num) + 160;

		temp = a;

		strResult += temp.Left(1);
	}

	return strResult;
}
