#pragma once
class AllPE
{
public:
	AllPE(void);
	~AllPE(void);
public:
	HANDLE hFile;
	LPCTSTR PeFile;
	char*Buf;
	PIMAGE_DOS_HEADER pDosH;	//DOSͷ
	PIMAGE_NT_HEADERS32 pNtH;	//NTͷ
	PIMAGE_OPTIONAL_HEADER32 pOptH;//��ѡͷ
	PIMAGE_SECTION_HEADER pSecH;//����ͷ
	PIMAGE_DATA_DIRECTORY pDatD;//����Ŀ¼
	PIMAGE_EXPORT_DIRECTORY pExpD;// ����������
public:
	void BeginPeInfo(TCHAR*FileName);//��ȡ�ļ���Ϣ
	void IsPE();//�ж��Ƿ�ΪPE
	void PeCloseHandle();//�ر��ļ�
	void InputPeInfo(CString& Target, DWORD Fact);//ת������
	DWORD RvaOffset(DWORD Rva);//����λ��
	DWORD ChangeNumber(CString NeedValue);
	void ReadPe();
};

