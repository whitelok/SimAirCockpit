#pragma once

// CFlightInfo 命令目标
#define uchar unsigned char
class CFlightInfo : public CObject
{
public:
	CFlightInfo();
	virtual ~CFlightInfo();
public:
	//接受手柄数据
	 UINT m_ubegin[2];       //开始
	 UINT m_usize;           //数据长度
	 UINT m_ucommand;        //命令标识
	 UINT m_uwing;           //副翼
	 UINT m_ulift;           //升降
	 UINT m_umph;            //油门
	 UINT m_udirection;      //方向
	 UINT m_uCH5;            //通道5
	 UINT m_uCH6;            //通道6
	 UINT m_uCH7;            //通道7
	 UINT m_uflag;           //校验码
	 UINT m_uend;            //结束
   
	//向飞机发送数据
	uchar m_cbegin[2];
    uchar m_csize;
	uchar m_ccommand;
	uchar m_cwing[2];
	uchar m_clift[2];
	uchar m_cmph[2];
	uchar m_cdirection[2];
	uchar m_cCH5[2];
	uchar m_cCH6[2];
	uchar m_cCH7[2];
	uchar m_cflag;
	uchar m_cend;

public:
	UINT OnChange(void);
	void OnTran(UINT m_uint, unsigned char *m_uchar);
	void OnSendNum(void);
};

