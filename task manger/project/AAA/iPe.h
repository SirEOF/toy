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
	PIMAGE_DOS_HEADER pDosH;	//DOS头
	PIMAGE_NT_HEADERS32 pNtH;	//NT头
	PIMAGE_OPTIONAL_HEADER32 pOptH;//可选头
	PIMAGE_SECTION_HEADER pSecH;//区段头
	PIMAGE_DATA_DIRECTORY pDatD;//数据目录
	PIMAGE_EXPORT_DIRECTORY pExpD;// 导出表数据
public:
	void BeginPeInfo(TCHAR*FileName);//获取文件信息
	void IsPE();//判断是否为PE
	void PeCloseHandle();//关闭文件
	void InputPeInfo(CString& Target, DWORD Fact);//转换内容
	DWORD RvaOffset(DWORD Rva);//计算位置
	DWORD ChangeNumber(CString NeedValue);
	void ReadPe();
};

