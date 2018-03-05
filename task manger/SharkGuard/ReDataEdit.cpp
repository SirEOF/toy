// ReDataEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "ReDataEdit.h"
#include "afxdialogex.h"
#include "ADOCoon.h"

// ReDataEdit 对话框

IMPLEMENT_DYNAMIC(ReDataEdit, CDialogEx)

ReDataEdit::ReDataEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(ReDataEdit::IDD, pParent)
	, v_id(_T(""))
	, v_name(_T(""))
	, v_md5(_T(""))
	, v_time(_T(""))
	, v_path(_T(""))
{

}

ReDataEdit::~ReDataEdit()
{
}

void ReDataEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FideID, v_id);
	DDX_Text(pDX, IDC_EDIT_FileName, v_name);
	DDX_Text(pDX, IDC_EDIT_VirsMd5, v_md5);
	DDX_Text(pDX, IDC_EDIT_CreatTime, v_time);
	DDX_Text(pDX, IDC_EDIT_FilePath, v_path);
}


BEGIN_MESSAGE_MAP(ReDataEdit, CDialogEx)
	ON_BN_CLICKED(IDC_ReSave, &ReDataEdit::OnBnClickedResave)
	ON_BN_CLICKED(IDC_ExitEdit, &ReDataEdit::OnBnClickedExitedit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// ReDataEdit 消息处理程序


BOOL ReDataEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ReDataEdit::OnBnClickedResave()
{
	
		//int type = m_type.GetCurSel();
		UpdateData(true);

		CADOConn adoConn;
		adoConn.OnInitCADOConn();
		CString sql;
	//	sql.Format(L"UPDATE 病毒库 SET 文件名称='%s', MD5=%s, 创建时间='%s', 文件路径='%s', WHERE ID = %s",
	//		v_name, v_md5, v_time, v_path, v_id);
		/*if (m_isUpdate)
		{
			sql.Format(L"UPDATE 病毒库 SET 文件名称='%s', MD5=%s, 创建时间='%s', 文件路径='%s' WHERE 编号 = %s",
				v_name, v_md5, v_time, v_path, v_id);
		}
		else
		{
			
		}*/
		if (m_isUpdate)
		{
			sql.Format(L"UPDATE 病毒库 SET 文件名称='%s', MD5='%s', 创建时间='%s', 文件路径='%s' WHERE ID = %s",
				v_name, v_md5, v_time, v_path, v_id);
		}
		else
		{
			sql.Format(L"INSERT INTO 病毒库 (文件名称, MD5, 创建时间, 文件路径 ) VALUES('%s', '%s', '%s', '%s'); ",
				v_name, v_md5, v_time, v_path);
		}
		//sql.Format(L"INSERT INTO 病毒库 ( 文件名称, MD5, 创建时间, 文件路径 ) VALUES( %s, '%s', '%s', '%s'); ",
		//	/*v_id,*/ v_name, v_md5, v_time, v_path);


		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
		if (m_isUpdate)
		{
			MessageBox(L"更新成功！");
			OnOK();
		}
		else
		{
			MessageBox(L"插入成功！");
		}
}

	


void ReDataEdit::OnBnClickedExitedit()
{
	SendMessage(WM_CLOSE, 0, 0);
}

void ReDataEdit::doUpdate(CString id)
{
	m_isUpdate = TRUE;
	
	v_id = id;
}

void ReDataEdit::OnDropFiles(HDROP hDropInfo)
{
	DragQueryFile(hDropInfo, NULL, Path, MAX_PATH);;
	TCHAR*path;
	path = Path;
	CFileFind  Finder;
	CTime  TempTime;
	//CString  Filename;
	//设置获取信息结构体
	WIN32_FIND_DATA  stcFData = { 0 };
	//只需要获取一个文件的信息,所以不需要使用循环
	BOOL bWorking = Finder.FindFile(path);
	if (bWorking)
	{
		bWorking = Finder.FindNextFile();
		// 获取文件创建时间
		if (Finder.GetCreationTime(TempTime))
		{
			v_time = TempTime.Format(_T("%c"));
		}
	
		//获取文件名称
		v_name = Finder.GetFileTitle();
		v_path = Path;
		//SetDlgItemText(IDC_EDIT_FilePath, Path);
	}

	CStringA Temp;
	Temp.Format("%s", path);
	char  cPath[MAX_PATH];
	TcharToChar(path, cPath);
	memcpy(cPath, MD5->md5FileValue(cPath), MAX_PATH);
	v_md5 = cPath;
	UpdateData(FALSE);
	CDialogEx::OnDropFiles(hDropInfo);
}

void ReDataEdit::TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
