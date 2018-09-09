#include <Windows.h>

#ifndef __STRUCT_GAME_H__
#define __STRUCT_GAME_H__

typedef unsigned __int64 QWORD;

extern void DbgPrintfMine(char* pszFormat,...);

HWND getGameWndHandle();//��ȡ��Ϸ�����ھ��

DWORD play2PointDistance(float x1, float y1, float x2, float y2);

//��Ϸ���ݽṹ�Լ�ƫ�ƹ���
typedef struct TROLE_PROPERTY{ //�������Խṹ
	//+0		������
	char *szpRoleName;
	//+34		�ȼ�(1�ֽ�)
	DWORD ndLevel;
	//+35		תְ(1�ֽ�)
	DWORD ndLevelְҵ;
	//+36		����(char*)
	char *szp����;
	//+80		HP
	DWORD ndHp;
	//+84		MP
	DWORD ndMp;
	//+88		��ŭֵ
	DWORD ndAngry;
	//+8C		HP����
	DWORD ndMaxHp;
	//+90		MP����
	DWORD ndMaxMp;
	//+94		��ŭֵ����
	DWORD naMaxAngry;
	//+98		8byte,��ǰ����ֵ
	QWORD nqExp;
	//+A0		8byte,�����ܾ���
	QWORD nqExpNextRequire;
	//+A8		(10)
	//+AC		����
	DWORD ndLiLian;
	//+B0		��
	DWORD nd��;
	//+B4		��
	DWORD nd��;
	//+B8		��
	DWORD nd��;
	//+BC		��
	DWORD nd��;
	//+C8		������
	DWORD nd������;
	//+CC		������
	DWORD nd������;
	//+D0		������
	DWORD nd������;
	//+D4		�ر���
	DWORD nd�ر���;
	//+E4		���
	QWORD nqMoney;
	//+EC		(word)����
	WORD nw����;
	//+EE		(word)��������
	WORD nwMax����;
	//+F0		��������
	DWORD ndPoint����;
	//+F4		��һ����
	DWORD ndQiGongPoint[32];
	//+F8		�ڶ�����

	TROLE_PROPERTY* getData();//��ʼ������
	char* GetRoleName();//��ȡ��ɫ����
	DWORD GetRoleLevel();//��ȡ��ɫ�ȼ�
}_TROLE_PROPERTY;

typedef struct TBACK_PACK_OBJ{//������Ʒ����
	//+5C	//��Ʒ����
	char* szpGoodName;
	//+F1	//��Ʒ����
	char* szpGoodDesc;
	//+C44	//��Ʒ����
	DWORD ndGoodNum;
}_TBACK_PACK_OBJ;

//�����ṹ
#define nBackPackSize 36
typedef struct TBACK_PACK_LIST_OBJ{//��������

	enum EquipType{
		ndClothes,
		ndHandguardL,ndHandguardR,
		ndArm,
		ndShoe,
		ndShell,
		ndNecklace,
		ndEarringL,ndEarringR,
		ndRingL,ndRingR
	};

	TBACK_PACK_OBJ mtGoodList[nBackPackSize];

	TBACK_PACK_LIST_OBJ* getData();
	int useGoodByIndex(DWORD ndIndex);//�����±�ʹ�ñ�����Ʒ
	int getGoodIndexByName(char* szpGoodName);//������Ʒ����ѯ��������Ʒ�±�
	BOOL useGoodByIndex(char* szpGoodName);//������Ʒ��ʹ�ñ�����Ʒ
	DWORD TBACK_PACK_LIST_OBJ::selectGoods(DWORD ndIndex);//ѡ�б����е�ĳһ��
	BOOL TBACK_PACK_LIST_OBJ::moveGoodToDepot(DWORD ndIndex = 1);//�ƶ�ѡ�е���Ʒ���ֿ�
	BOOL TBACK_PACK_LIST_OBJ::moveGoodToEquip(DWORD ndIndex = 1);//�ƶ���Ʒ��װ��������װ��
	BOOL TBACK_PACK_LIST_OBJ::moveGoodToEquipHandguardL(int niType, char* szpEquipName);//��������
}_TBACK_PACK_LIST_OBJ;

//����ṹ
typedef struct TMONSTER_OBJ{
	//0x0C���ж���������±�
	DWORD ndIndexByAllObj;
	//+5f4	//Ѫ��
	DWORD ndHp;
	//+5f8	//�ȼ�
	DWORD ndLevel;
	//+3c0	//���� 1-��0-����
	DWORD isDead;
	//+360	//����
	char* szpName;
	//+1060	//����1
	float flCurX;
	//+1068	//����2
	float flCurY;
	DWORD ndDistance;//�������
}_TMONSTER_OBJ;

typedef struct TMONSTER_LIST_OBJ{
	TMONSTER_OBJ tMonsterList[100];

	TMONSTER_LIST_OBJ* getData();
	BOOL TMONSTER_LIST_OBJ::dbgPrintMsg();
}_TMONSTER_LIST_OBJ;

//���ﶯ��
//��������ṹ
typedef struct TACTION_OBJ{
	char *szpName;
	DWORD ndActionId;
}_TACTION_OBJ;

//������������
typedef struct TACTION_LIST_OBJ{
	TACTION_OBJ tList[12];

	TACTION_LIST_OBJ* getData();
	BOOL TACTION_LIST_OBJ::dbgPrintMsg();
	BOOL UseAction(DWORD ndIndex);
	BOOL UseAction(char* szpIndexName);
}_TACTION_LIST_OBJ;

typedef struct TROLE_OBJ{
	//+000c	//�±꣨LEA     EDX,DWORD PTR DS:[ECX*4+2D3D598]	; ��ҡ�����������...��
	//+0018	//����
	//+1a3c	//ѡ�����
	//+33c4	//ѡ��״̬
	DWORD ndSelectIndex;
	float flCurX;
	float flCurY;

	TROLE_OBJ* TROLE_OBJ::getData();
	BOOL TROLE_OBJ::selectObj(DWORD ndIndexByObj);
	BOOL TROLE_OBJ::selectMonsterByNear();//ѡ������Ĺ���
	BOOL TROLE_OBJ::autoAttackMonster();//�Զ����
	BOOL TROLE_OBJ::autoAttackMonsterBySkill(char* szpSkillName);//ʹ�ü����Զ����
	DWORD TROLE_OBJ::getSelectObjType();//����ѡ������� obj+0x8=0x2E
	BOOL TROLE_OBJ::findWay(int niX, int niY);//�Զ�Ѱ·
}_TROLE_OBJ;

typedef struct  TSKILL_OBJ{
	DWORD ndIndexBySkill;
	//+8		//���ࣨ1b-���ܷ���<��>	1c-���ܶ�����ࣩ
	DWORD ndType;
	//+0c		//
	DWORD ndIndexByAll;
	//+5c		//��������
	char* szpName;
	//+ac		//����ȼ�
	DWORD ndRequireLevel;
	//+0b1	//��������ְҵ
	//+1f6	//��2�ֽڣ��Ƿ���ѧ���ܣ�1-��ѧ 0-δѧ��
	BOOL isUseable;
	//+268	//��������
	DWORD ndRequireLiLian;
	DWORD ndObjBase;//�����ַ
}_TSKILL_OBJ;

typedef struct TSKILL_LIST_OBJ{
	TSKILL_OBJ tSkillList[32];

	TSKILL_LIST_OBJ* TSKILL_LIST_OBJ::getData();
	void TSKILL_LIST_OBJ::dbgPrintMsg();
	BOOL TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName, DWORD ndIndexF1F10);
	BOOL TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName);
	BOOL TSKILL_LIST_OBJ::practiceSkill(DWORD ndIndex);//��������
	BOOL TSKILL_LIST_OBJ::practiceSkill(char* szpSkillName);//��������
	BOOL TSKILL_LIST_OBJ::isCanStudy(DWORD ndIndex);//�����Ƿ��ѧ
}_TSKILL_LIST_OBJ;

#define F1F10Size 10
typedef struct TF1_F10_OBJ{
	//+8		//���ͣ�1E��
	DWORD ndType;
	//+5c		//��������
	char* szpSkillName;

}_TF1_F10_OBJ;

typedef struct TF1_F10_LIST_OBJ{
	TF1_F10_OBJ tF1F10List[F1F10Size];

	TF1_F10_LIST_OBJ* TF1_F10_LIST_OBJ::getData();
	int TF1_F10_LIST_OBJ::getIndexByName(char* szpSkillName);
	BOOL TF1_F10_LIST_OBJ::useSkillByIndex(int index);
	int TF1_F10_LIST_OBJ::getEmptyIndex(void);
	BOOL TF1_F10_LIST_OBJ::useSkillByName(char* szpSkillName);
}_TF1_F10_LIST_OBJ;

#endif
