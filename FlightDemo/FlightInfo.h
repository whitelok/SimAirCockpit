#pragma once

// CFlightInfo ����Ŀ��
#define uchar unsigned char
class CFlightInfo : public CObject
{
public:
	CFlightInfo();
	virtual ~CFlightInfo();
public:
	//�����ֱ�����
	 UINT m_ubegin[2];       //��ʼ
	 UINT m_usize;           //���ݳ���
	 UINT m_ucommand;        //�����ʶ
	 UINT m_uwing;           //����
	 UINT m_ulift;           //����
	 UINT m_umph;            //����
	 UINT m_udirection;      //����
	 UINT m_uCH5;            //ͨ��5
	 UINT m_uCH6;            //ͨ��6
	 UINT m_uCH7;            //ͨ��7
	 UINT m_uflag;           //У����
	 UINT m_uend;            //����
   
	//��ɻ���������
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

