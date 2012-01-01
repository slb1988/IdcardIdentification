// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"
#include "pinyindlg.h"
#include "convertchinesegbdlg.h"

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	//以下为新添代码
	m_editIdcard = m_birthDate = m_sex = m_address = m_idcard = L"";

	DoDataExchange(FALSE);

	// Add your code
	if(LRunSql::InitConnectPtr()==false)		//初始化COM环境，进行数据库连接
		return false;


	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//	if (LRunSql::m_database != NULL)
	{
		LRunSql::Close();		//断开数据库连接
	}

	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	Clear();

	DoDataExchange(TRUE);
	if (m_editIdcard.GetLength() == 18 )
	{
		if ( iso7064(m_editIdcard) == false)
		{
			GetDlgItem(IDC_STATIC_INFO).SetWindowText(L"不是有效的身份证号码！");
			return 1;
		}

		//查询性别
		if (m_editIdcard.GetAt(16) % 2 == 1)
			m_sex = L"男";
		else 
			m_sex = L"女";

		//出生日期
		m_birthDate.Format(L"%s年%s月%s日", m_editIdcard.Mid(6, 4), m_editIdcard.Mid(10, 2), m_editIdcard.Mid(12, 2));

		//查询区域
		CString ch = m_editIdcard.Mid(0, 6);
		sql.Format(L"select * from City where sz_code='%s'", m_editIdcard.Mid(0, 6));
		if (m_runsql.CheckSQLResult(sql))
		{
			LPCTSTR str = (LPCTSTR)(_bstr_t)m_runsql.m_recordset->GetCollect("id");
			m_address.Format(L"%s %s", (LPCTSTR)(_bstr_t)m_runsql.m_recordset->GetCollect("state"),
				(LPCTSTR)(_bstr_t)m_runsql.m_recordset->GetCollect("city"));
		}

		m_idcard = m_editIdcard;
	}
	else if ( m_editIdcard.GetLength() == 15)
	{   
		//查询性别
		if (m_editIdcard.GetAt(14) % 2 == 1)
			m_sex = L"男";
		else 
			m_sex = L"女";

		//出生日期
		m_birthDate.Format(L"19%s年%s月%s日", m_editIdcard.Mid(6, 2), m_editIdcard.Mid(8, 2), m_editIdcard.Mid(10, 2));

		//查询区域
		CString ch = m_editIdcard.Mid(0, 6);
		sql.Format(L"select * from City where sz_code='%s'", m_editIdcard.Mid(0, 6));
		if (m_runsql.CheckSQLResult(sql))
		{
			LPCTSTR str = (LPCTSTR)(_bstr_t)m_runsql.m_recordset->GetCollect("id");
			m_address.Format(L"%s %s", (LPCTSTR)(_bstr_t)m_runsql.m_recordset->GetCollect("state"),
				(LPCTSTR)(_bstr_t)m_runsql.m_recordset->GetCollect("city"));
		}

		iso7064_15To18(m_editIdcard, m_idcard);
	}
	else
	{

		GetDlgItem(IDC_STATIC_INFO).SetWindowText(L"请输入15位或18位身份证号码！");
		//AtlMessageBox(m_hWnd, L"请输入18位身份证号");
		return 1;
	}


	DoDataExchange(FALSE);

	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnBnClickedAppPysx(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码

	CPinyinDlg dlg;

	dlg.DoModal();

	return 0;
}

LRESULT CMainDlg::OnBnClickedAppConvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码
	CConvertGBDlg dlg;
	dlg.DoModal();

	return 0;
}
