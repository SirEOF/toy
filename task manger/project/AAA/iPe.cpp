#include "stdafx.h"
#include "iPe.h"


AllPE::AllPE(void)
{
}


AllPE::~AllPE(void)
{
}

UINT UWM_REFTHREADINFO = RegisterWindowMessage(TEXT("BeginPeInfo")); // ע��鿴�߳��Զ�����Ϣ
//��ȡ�ļ���Ϣ
void AllPE::BeginPeInfo(TCHAR*FileName)
{
	PeFile = FileName;
	hFile = CreateFile(PeFile,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		SECURITY_IMPERSONATION,
		NULL);
	/*if (hFile == INVALID_HANDLE_VALUE)
		return;
		*/
	DWORD SizeFile = GetFileSize(hFile, NULL);//�ļ���С
	DWORD WUYONG = 0;
	Buf = new char[SizeFile];
	//���ļ���ȡ���ڴ���
	ReadFile(hFile, Buf, SizeFile, &WUYONG, NULL);
	IsPE();
}
//�ж��Ƿ�ΪPE
void AllPE::IsPE()
{

	pDosH = (PIMAGE_DOS_HEADER)Buf;
	if (pDosH->e_magic != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(0, L"��������ЧPE�ļ���", 0, 0);
		return;
	}
	//NTͷ
	pNtH = (PIMAGE_NT_HEADERS)(Buf + pDosH->e_lfanew);
	//����ͷ
	pSecH = IMAGE_FIRST_SECTION(pNtH);
	//��ѡͷ
	pOptH = &(pNtH->OptionalHeader);
	//��ȡĿ¼
	pDatD = (pOptH->DataDirectory);
	//PEDLG.OnDropPE();
}

//���̶���PE
void AllPE::ReadPe()
{
	pDosH = (PIMAGE_DOS_HEADER)Buf;
	if (pDosH->e_magic != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(0, L"��������ЧPE�ļ���", 0, 0);
		return;
	}
	//NTͷ
	pNtH = (PIMAGE_NT_HEADERS)(Buf + pDosH->e_lfanew);
	//����ͷ
	pSecH = IMAGE_FIRST_SECTION(pNtH);
	//��ѡͷ
	pOptH = &(pNtH->OptionalHeader);
	//��ȡĿ¼
	pDatD = (pOptH->DataDirectory);
	//PEDLG.ProToPE();
}

//�ر��ļ�
void AllPE::PeCloseHandle()
{
	CloseHandle(hFile);
}
//ת����Ϣ
void AllPE::InputPeInfo(CString& Target, DWORD Fact)
{
	CString Info;
	Info.Format(L"%08X", Fact);
	Target = Info;

}
DWORD AllPE::ChangeNumber(CString NeedValue)
{
	CStringA PeValue(NeedValue);
	char *p = PeValue.GetBuffer();	//ת��Ϊchar* ����
	return strtoul(p, 0, 16);		//ת��Ϊʮ��������
}


DWORD AllPE::RvaOffset(DWORD Rva)
{
	PIMAGE_SECTION_HEADER pSECH = IMAGE_FIRST_SECTION(pNtH);
	DWORD Num = pNtH->FileHeader.NumberOfSections;
	if (Rva < pSECH[0].PointerToRawData)
	{
		return Rva;
	}
	for (DWORD i = 0; i < Num; i++)
	{
		if (
			(Rva >= pSECH[i].VirtualAddress) &&
			(Rva <= pSECH[i].VirtualAddress + pSECH[i].Misc.VirtualSize)//�Ƿ��ڵ�ǰ�����ε�λ�ã���ֹ��ȥ��������
			)
		{
			return (Rva - pSECH[i].VirtualAddress + pSECH[i].PointerToRawData);//��������ַ-�����������ͷ��ַ+ԭ�ļ����ε�ַ=ԭ�ļ�����ƫ��
		}
	}
	return TRUE;
}



