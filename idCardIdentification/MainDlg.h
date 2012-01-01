// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlmisc.h>
#include <atlddx.h>
#include "myfunction.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler,
		public CWinDataExchange<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(ID_APP_PYSX, BN_CLICKED, OnBnClickedAppPysx)
		COMMAND_HANDLER(ID_APP_CONVERT, BN_CLICKED, OnBnClickedAppConvert)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CMainDlg)
		DDX_TEXT(IDC_EDIT_IDCARD, m_editIdcard)
		DDX_TEXT(IDC_SEX, m_sex)
		DDX_TEXT(IDC_BIRTHDATE, m_birthDate)
		DDX_TEXT(IDC_ADDRESS, m_address)
		DDX_TEXT(IDC_IDCARD, m_idcard)
	END_DDX_MAP();

	ATL::CString m_editIdcard;
	ATL::CString m_sex;
	ATL::CString m_birthDate;
	ATL::CString m_address;
	ATL::CString m_idcard;


	LRunSql m_runsql;
	ATL::CString sql;

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	bool iso7064(CString vString)
	{
		long result = 0;
		int wi[] = {1, 2, 4, 8, 5, 10, 9, 7, 3, 6 };
		char hash_map[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
		int i_size = vString.GetLength();
		bool bModify = '?' == vString.Right(1);
		int i_size1 = bModify ? i_size : i_size+1;


		int sigma, i1, w1;
		sigma = i1 = w1 = 0;
		for (int i = 1; i < i_size; ++i)
		{
			i1 = (vString.GetAt(i-1)-48)*1;
// 			if (i1 < 0 || i1 > 9)
// 				break;
			w1 = wi[(i_size-i)%10];
			sigma += (i1 * w1) % 11;
		}

		int ch2 = vString.GetAt(i_size-1);
		if (hash_map[sigma % 11] == ch2)
			return true;
		else
			return false;
// 		if (bModify)
// 		{
// 			//设置的临时变量，无用！
// 			//vString.SetAt(i_size-1, hash_map[sigma % 11]);
// 			return 1;
// 		}
// 		else
// 			return hash_map[sigma % 11];
	}

	bool iso7064_15To18(CString vSrc, CString& vDst)
	{
		vDst = vSrc.Mid(0, 6);
		vDst += L"19";
		vDst += vSrc.Right(9);
		vDst += L"?";

		long result = 0;
		int wi[] = {1, 2, 4, 8, 5, 10, 9, 7, 3, 6 };
		char hash_map[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
		bool bModify = L"?" == vDst.Right(1);

		int sigma, i1, w1;
		sigma = i1 = w1 = 0;
		for (int i = 1; i < 18; ++i)
		{
			i1 = (vDst.GetAt(i-1)-48)*1;
			w1 = wi[(18-i)%10];
			sigma += (i1 * w1) % 11;
		}

		if (bModify)
		{
			//设置的临时变量，无用！
			vDst.SetAt(17, hash_map[sigma % 11]);
			return 0;
		}
		else
			return 1;
	}

	//获得汉字字符串的拼音
	CString GetSpell(CString str)
	{
		CString strResult;
//		int high, low ;

		int length = str.GetLength();

		CString ssss;

// 		for (int i = 0; i < length; ++i)
// 		{
// 			CString temp = str.GetAt(i);
// 			
// 			high = atoi(str.GetAt(i)) && 1111111100000000 + 160;
// 			low = atoi(str.GetAt(i)) && 11111111 + 160;
// 			ssss.Format(L"%d%d", high, low);
// 		}

		return strResult;
	}

	void Clear()
	{
		GetDlgItem(IDC_SEX).SetWindowText(L"");
		GetDlgItem(IDC_BIRTHDATE).SetWindowText(L"");
		GetDlgItem(IDC_ADDRESS).SetWindowText(L"");
		GetDlgItem(IDC_IDCARD).SetWindowText(L"");
		GetDlgItem(IDC_STATIC_INFO).SetWindowText(L"");
	}

	void CloseDialog(int nVal);
	LRESULT OnBnClickedAppPysx(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedAppConvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
