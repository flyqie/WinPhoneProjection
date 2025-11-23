#pragma once

#include "WP81ProjectionCommon.h"

class CWP81ProjectionClient
{
private:
	LPWSTR lpstrUsbVid = NULL;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hEvent = NULL;
	HANDLE hWrite = NULL;
	WINUSB_INTERFACE_HANDLE hUsb = NULL;
	PVOID pBufOfData = NULL;
	DWORD dwBufferSize = 0;
	BOOL bIoPending = FALSE;
	WP_SCRREN_TO_PC_PIPE usbPipe;
	OVERLAPPED ioOverlapped;
	OVERLAPPED ioWrite;
	CRITICAL_SECTION cs;
	DWORD dwPhoneWidth = 0,dwPhoneHeight = 0,dwPhoneStride = 0;
	DWORD send[48];
	DWORD last;
public:
	CWP81ProjectionClient(LPCWSTR lpszUsbVid);
	~CWP81ProjectionClient();
public: //My Methods (Error Query:GetLastError)
	/*
	初始化WP投影仪(手机会出现是否允许投影对话框)
	参数：
		dwMaxBufferSize 最大读数据缓冲区大小
	*/
	virtual BOOL Initialize(DWORD dwMaxBufferSize = WP_SCREEN_TO_PC_ALIGN512_MAX_SIZE);

	virtual void Reset();
	/*
	读取当前的屏幕图像（图像为16bit的BMP数据）
	参数：
		dwBufferSize 缓冲区大小
		pBuffer 数据将被写到这个缓冲区
		pWidth 图像高度
		pHeight 图像宽度
		pdwBits 图像色深
		pOrientation 屏幕方向
	*/
	virtual BOOL ReadImageAsync();
	/*
	等待异步IO读取完成
	参数：
		dwTimeout 超时时间，默认无限等待
	*/
	virtual BOOL WaitReadImageComplete(PBYTE* ppBuffer,PUINT32 pWidth,PUINT32 pHeight,PDWORD pdwBits, PDWORD pdwStride,PUINT pOrientation,DWORD dwTimeout = INFINITE,BOOL bFastCall = FALSE);

	virtual BOOL SendTouchEvent(UINT uMsg, WPARAM wParam, LPARAM lPos, LPARAM lSize, UINT Orientation);
};