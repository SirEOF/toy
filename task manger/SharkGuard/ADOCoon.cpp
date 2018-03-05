#include "stdafx.h"
#include "ADOCoon.h"


CADOConn::CADOConn()
{
}


CADOConn::~CADOConn()
{
}

void CADOConn::OnInitCADOConn()
{
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		// m_pConnection->Open("Microsoft.Ace.Oledb.12.0;Data Source=ManageDB.accdb", "", "", adModeUnknown);///连接数据库
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=ManageDB.mdb", "", "", adModeUnknown);///连接数据库
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		ExitConnect();
	}
}

BOOL CADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
		if (m_pConnection == NULL)
			OnInitCADOConn();
		m_pConnection->Execute(bstrSQL, NULL, adCmdText);
		return true;
	}
	catch (_com_error e)
	{
		if (m_hParent)
		{
			CString errormessage;
			errormessage.Format("Sql执行失败!\r\n错误信息:" + e.Description());
			AfxMessageBox(errormessage);///显示错误信息
			ExitConnect();
		}
		return false;
	}
}

void CADOConn::ExitConnect()
{
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
}

_RecordsetPtr& CADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if (m_pConnection == NULL)
			OnInitCADOConn();
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		ExitConnect();
	}
	return m_pRecordset;
}