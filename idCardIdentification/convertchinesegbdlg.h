// convertchinesegbdlg.h : interface of the CConvertGBDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlmisc.h>
#include <atlddx.h>

class CConvertGBDlg : public CDialogImpl<CConvertGBDlg>,
	public CWinDataExchange<CConvertGBDlg>
{
public:
	enum { IDD = IDD_DLG_CONVERT };

	BEGIN_MSG_MAP(CConvertGBDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnClickOk)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CConvertGBDlg)
		DDX_TEXT(IDC_EDIT_WORD, m_word)
		DDX_TEXT(IDC_EDIT_CODE, m_code)
	END_DDX_MAP();

	CString m_word;
	CString m_code;

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	CString GetStringFromGB(CString num_Str);    //区间码转化为汉字
	CString GetGBFromCString(CString str);		//汉字转化为区间码

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClickOk(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
