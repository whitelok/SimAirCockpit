aa// FlightInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightInfo.h"


// CFlightInfo

CFlightInfo::CFlightInfo()
{
    this->m_ubegin[0]=0xa5;
	this->m_ubegin[1]=0x5a;
	this->m_usize=0x12;
	this->m_ucommand=0xf0;
	this->m_uwing=1500;
	this->m_ulift=1500;
	this->m_umph=1050;
	this->m_udirection=1500;;
	this->m_uCH5=1500;
	this->m_uCH6=1500;
	this->m_uCH7=1500;
	this->m_uflag=this->OnChange();
	this->m_uend=0xaa;
	this->OnSendNum();

}

CFlightInfo::~CFlightInfo()
{
}


// CFlightInfo 成员函数

UINT CFlightInfo::OnChange(void)
{
	UINT temp=this->m_usize+this->m_ucommand+this->m_uwing/256+this->m_ulift/256+this->m_udirection/256+this->m_umph/256+this->m_uCH5/256+this->m_uCH6/256+this->m_uCH7/256+this->m_uwing%256+this->m_ulift%256+this->m_udirection%256+this->m_umph%256+this->m_uCH5%256+this->m_uCH6%256+this->m_uCH7%256;
    temp=temp%256;
	return temp;
}

void CFlightInfo::OnTran(UINT m_uint, unsigned char *m_uchar)
{
	m_uchar[0]=(uchar)((m_uint>>8)&0xff);
	m_uchar[1]=(uchar)(m_uint&0xff);
}

void CFlightInfo::OnSendNum(void)
{
	this->m_cbegin[0]=(uchar)this->m_ubegin[0];
	this->m_cbegin[1]=(uchar)this->m_ubegin[1];
	this->m_csize=(uchar)this->m_usize;
	this->m_ccommand=(uchar)this->m_ucommand;
	this->OnTran(this->m_uwing,this->m_cwing);
	this->OnTran(this->m_ulift,this->m_clift);
	this->OnTran(this->m_umph,this->m_cmph);
	this->OnTran(this->m_udirection,this->m_cdirection);
	this->OnTran(this->m_uCH5,this->m_cCH5);
	this->OnTran(this->m_uCH6,this->m_cCH6);
	this->OnTran(this->m_uCH7,this->m_cCH7);
	this->m_cflag=(uchar)this->m_uflag;
	this->m_cend=(uchar)this->m_uend;
}
