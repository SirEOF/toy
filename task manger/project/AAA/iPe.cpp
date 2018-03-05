#include "stdafx.h"
#include "iPe.h"


AllPE::AllPE(void)
{
}


AllPE::~AllPE(void)
{
}

UINT UWM_REFTHREADINFO = RegisterWindowMessage(TEXT("BeginPeInfo")); // 注册查看线程自定义消息
//获取文件信息
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
	DWORD SizeFile = GetFileSize(hFile, NULL);//文件大小
	DWORD WUYONG = 0;
	Buf = new char[SizeFile];
	//将文件读取到内存中
	ReadFile(hFile, Buf, SizeFile, &WUYONG, NULL);
	IsPE();
}
//判断是否为PE
void AllPE::IsPE()
{

	pDosH = (PIMAGE_DOS_HEADER)Buf;
	if (pDosH->e_magic != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(0, L"请拖入有效PE文件！", 0, 0);
		return;
	}
	//NT头
	pNtH = (PIMAGE_NT_HEADERS)(Buf + pDosH->e_lfanew);
	//区段头
	pSecH = IMAGE_FIRST_SECTION(pNtH);
	//可选头
	pOptH = &(pNtH->OptionalHeader);
	//获取目录
	pDatD = (pOptH->DataDirectory);
	//PEDLG.OnDropPE();
}

//进程读进PE
void AllPE::ReadPe()
{
	pDosH = (PIMAGE_DOS_HEADER)Buf;
	if (pDosH->e_magic != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(0, L"请拖入有效PE文件！", 0, 0);
		return;
	}
	//NT头
	pNtH = (PIMAGE_NT_HEADERS)(Buf + pDosH->e_lfanew);
	//区段头
	pSecH = IMAGE_FIRST_SECTION(pNtH);
	//可选头
	pOptH = &(pNtH->OptionalHeader);
	//获取目录
	pDatD = (pOptH->DataDirectory);
	//PEDLG.ProToPE();
}

//关闭文件
void AllPE::PeCloseHandle()
{
	CloseHandle(hFile);
}
//转换信息
void AllPE::InputPeInfo(CString& Target, DWORD Fact)
{
	CString Info;
	Info.Format(L"%08X", Fact);
	Target = Info;

}
DWORD AllPE::ChangeNumber(CString NeedValue)
{
	CStringA PeValue(NeedValue);
	char *p = PeValue.GetBuffer();	//转换为char* 类型
	return strtoul(p, 0, 16);		//转换为十进制数字
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
			(Rva <= pSECH[i].VirtualAddress + pSECH[i].Misc.VirtualSize)//是否在当前项区段的位置，防止蹿去其他区段
			)
		{
			return (Rva - pSECH[i].VirtualAddress + pSECH[i].PointerToRawData);//相对虚拟地址-相对虚拟区段头地址+原文件区段地址=原文件区段偏移
		}
	}
	return TRUE;
}



