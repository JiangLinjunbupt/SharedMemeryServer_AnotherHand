//�����ڴ�Ľ���һ��Ҫ�� ������Ա���������visual studio������У�������
#include "GloveData.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
using namespace std;

#define BUF_SIZE 1024
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");    //ָ��ͬһ�鹲���ڴ������


int main()
{

	//ע������������
	HANDLE hMapFile;
	LPCTSTR pBuf;


	//�����ڴ湲������
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szName);                 // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"),
			GetLastError());
		return 1;
	}

	//���ڴ�ӳ�䵽�ý���
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);

		return 1;
	}
	//��main��ʼ�����ǻ�ȡ��Ϊ"Global\\MyFileMappingObject"�Ĺ����ڴ��ָ��

	//���´��룬B��ͣд�����ڴ�pBuf

	GloveData glovedata;

	float *Transdata = new float[26];
	while (1)
	{
		glovedata.GetGloveData();
		for (int i = 0;i < 26;i++)
		{
			Transdata[i] = glovedata.HandinfParams[i];
		}
		memcpy((PVOID)pBuf, Transdata, sizeof(float) * 26);
		Sleep(10);
	}

	return 0;
}
