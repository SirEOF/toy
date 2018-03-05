#pragma once


// CMD5

//MD5摘要值结构体
typedef struct MD5VAL_STRUCT
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
} MD5VAL;

#ifndef __MD5_INCLUDED__
#define __MD5_INCLUDED__

class CMD5 : public CWnd
{
	DECLARE_DYNAMIC(CMD5)

public:
	CMD5();
	virtual ~CMD5();
	//计算字符串的MD5值(若不指定长度则由函数计算)
	MD5VAL md5(char * str, unsigned int size = 0);

	//MD5文件摘要
	MD5VAL md5File(FILE * fpin);

	//直接计算文件MD5
	char * md5FileValue(char * fname);

	//字符串md5加密
	void md5Str(char * input, char * output);
protected:
	DECLARE_MESSAGE_MAP()
};
#endif


