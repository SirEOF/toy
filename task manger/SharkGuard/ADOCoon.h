#pragma once

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace\
	rename("EOF", "adoEOF")rename("BOF", "adoBOF")
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CADOConn
{
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
public:
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	CADOConn();
	virtual ~CADOConn();
	void OnInitCADOConn();
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	void ExitConnect();
	HWND m_hParent;
};
