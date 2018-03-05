// ReDataEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SharkGuard.h"
#include "ReDataEdit.h"
#include "afxdialogex.h"
#include "ADOCoon.h"

// ReDataEdit �Ի���

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


// ReDataEdit ��Ϣ�������


BOOL ReDataEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ReDataEdit::OnBnClickedResave()
{
	
		//int type = m_type.GetCurSel();
		UpdateData(true);

		CADOConn adoConn;
		adoConn.OnInitCADOConn();
		CString sql;
	//	sql.Format(L"UPDATE ������ SET �ļ�����='%s', MD5=%s, ����ʱ��='%s', �ļ�·��='%s', WHERE ID = %s",
	//		v_name, v_md5, v_time, v_path, v_id);
		/*if (m_isUpdate)
		{
			sql.Format(L"UPDATE ������ SET �ļ�����='%s', MD5=%s, ����ʱ��='%s', �ļ�·��='%s' WHERE ��� = %s",
				v_name, v_md5, v_time, v_path, v_id);
		}
		else
		{
			
		}*/
		if (m_isUpdate)
		{
			sql.Format(L"UPDATE ������ SET �ļ�����='%s', MD5='%s', ����ʱ��='%s', �ļ�·��='%s' WHERE ID = %s",
				v_name, v_md5, v_time, v_path, v_id);
		}
		else
		{
			sql.Format(L"INSERT INTO ������ (�ļ�����, MD5, ����ʱ��, �ļ�·�� ) VALUES('%s', '%s', '%s', '%s'); ",
				v_name, v_md5, v_time, v_path);
		}
		//sql.Format(L"INSERT INTO ������ ( �ļ�����, MD5, ����ʱ��, �ļ�·�� ) VALUES( %s, '%s', '%s', '%s'); ",
		//	/*v_id,*/ v_name, v_md5, v_time, v_path);


		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
		if (m_isUpdate)
		{
			MessageBox(L"���³ɹ���");
			OnOK();
		}
		else
		{
			MessageBox(L"����ɹ���");
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
	//���û�ȡ��Ϣ�ṹ��
	WIN32_FIND_DATA  stcFData = { 0 };
	//ֻ��Ҫ��ȡһ���ļ�����Ϣ,���Բ���Ҫʹ��ѭ��
	BOOL bWorking = Finder.FindFile(path);
	if (bWorking)
	{
		bWorking = Finder.FindNextFile();
		// ��ȡ�ļ�����ʱ��
		if (Finder.GetCreationTime(TempTime))
		{
			v_time = TempTime.Format(_T("%c"));
		}
	
		//��ȡ�ļ�����
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
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
