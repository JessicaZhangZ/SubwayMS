#ifndef __SUBWAY_CARD_H__
#define __SUBWAY_CARD_H__
#include "subwayError.h"
#include "../subwayGlobal/subwayGlobalDef.h"
#include <queue>
using namespace std;



//�������ϵͳ��100�ŵ�����
#define MAX_CARD_NUM 100

//������ֵ
#define MAX_BALANCE 999

//dongguanli
#define CARDNUM 100

//����������
typedef enum
{
    EN_CARD_TYPE_SINGLE = 0,
    EN_CARD_TYPE_ELDER,
    EN_CARD_TYPE_NOMAL,
    EN_CARD_TYPE_BUTT
}EN_CARD_TYPE;


 
struct HISTORY {
	ST_SUBWAY_TIME inTime;
	ST_SUBWAY_TIME outTime;
	string inStation;
	string outStation;
	int pay;

	HISTORY(ST_SUBWAY_TIME inT, ST_SUBWAY_TIME outT, string inS, string outS, int p) :
		inTime(inT), outTime(outT), inStation(inS), outStation(outS), pay(p) {}
};



class CARD {
public:
	CARD() {}
	CARD(unsigned int n, EN_CARD_TYPE t, int b = 0) : num(n), type(t), balance(b) {}
	~CARD()
	{
		HISTORY *h;
		while (!q_history.empty())
		{
			h = q_history.front();
			q_history.pop();
			delete h;
		}
	}


	void setBalance(int b)
	{
		balance = b;
	}
	int getBalance()
	{
		return balance;
	}
	void updateHistory(HISTORY *record)
	{
		q_history.push(record);
	}
	unsigned int getNum()
	{
		return num;
	}
	EN_CARD_TYPE getType()
	{
		return type;
	}

private:
	unsigned int num;
	EN_CARD_TYPE type;
	int balance;
	queue<HISTORY*> q_history;

};
/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo();

/*
@ ���������俨�źͿ���Ϣ
@ ��Σ�enCard,������; charge: ��ֵ
@ ����: cardNo, ����Ŀ���
@ ����ֵ: EN_RETURN_SUCC������ɹ�; EN_RETURN_CARD_OVERLOW, ����ʧ��;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge);


/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge);

/*
@ ��ȡ����Ϣ
@ ��Σ�cardNo,����; 
@ ����: balance: ���
        enCard:  ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard);

/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����;
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance);

/*
@ ���ݿ������ַ���, ʶ������
@ ��Σ�cardType,      �������ַ���; 
@ ����: enCard,        ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INPUT_INVALID_CARDTYPE, ʧ��;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard);

/*
@ ɾ������Ϣ
@ ��Σ�cardNo,����; 
@ ����: ��
@ ����ֵ: 0���ɹ�; -1, ʧ��;
*/
int DeleteCard(unsigned int cardNo);

/*
@ ��ȡ�������ַ���
@ ��Σ�enCard,������; 
@ ����: ��
@ ����ֵ: �������ַ���������"��ͨ��";
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard);

void InitCardQueue(queue<unsigned int> &cardNumQueue);

EN_RETURN_CODE GetAssignedCardNum(unsigned int &cardNo);

#endif