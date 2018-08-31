#include <Windows.h>

#ifndef __STRUCT_GAME_H__
#define __STRUCT_GAME_H__

typedef unsigned __int64 QWORD;

extern void DbgPrintfMine(char* pszFormat,...);

HWND getGameWndHandle();//获取游戏主窗口句柄

DWORD play2PointDistance(float x1, float y1, float x2, float y2);

//游戏数据结构以及偏移管理
typedef struct TROLE_PROPERTY{ //人物属性结构
	//+0		人物名
	char *szpRoleName;
	//+34		等级(1字节)
	DWORD ndLevel;
	//+35		转职(1字节)
	DWORD ndLevel职业;
	//+36		名声(char*)
	char *szp名声;
	//+80		HP
	DWORD ndHp;
	//+84		MP
	DWORD ndMp;
	//+88		愤怒值
	DWORD ndAngry;
	//+8C		HP上限
	DWORD ndMaxHp;
	//+90		MP上限
	DWORD ndMaxMp;
	//+94		愤怒值上限
	DWORD naMaxAngry;
	//+98		8byte,当前经验值
	QWORD nqExp;
	//+A0		8byte,升级总经验
	QWORD nqExpNextRequire;
	//+A8		(10)
	//+AC		可能是历练
	//+B0		心
	DWORD nd心;
	//+B4		气
	DWORD nd气;
	//+B8		体
	DWORD nd体;
	//+BC		魂
	DWORD nd魄;
	//+C8		攻击力
	DWORD nd攻击力;
	//+CC		防御力
	DWORD nd防御力;
	//+D0		命中率
	DWORD nd命中率;
	//+D4		回避率
	DWORD nd回避率;
	//+E4		金币
	QWORD nqMoney;
	//+EC		(word)负重
	WORD nw负重;
	//+EE		(word)负重上限
	WORD nwMax负重;
	//+F0		气功点数
	DWORD ndPoint气功;
	//+F4		第一气功
	DWORD ndQiGongPoint[32];
	//+F8		第二气功

	TROLE_PROPERTY* getData();//初始化数据
	char* GetRoleName();//获取角色名字
	DWORD GetRoleLevel();//获取角色等级
}_TROLE_PROPERTY;

typedef struct TBACK_PACK_OBJ{//背包物品对象
	//+5C	//物品名称
	char* szpGoodName;
	//+F1	//物品描述
	char* szpGoodDesc;
	//+C44	//物品数量
	DWORD ndGoodNum;
}_TBACK_PACK_OBJ;

//背包结构
#define nBackPackSize 36
typedef struct TBACK_PACK_LIST_OBJ{//背包对象
	TBACK_PACK_OBJ mtGoodList[nBackPackSize];

	TBACK_PACK_LIST_OBJ* getData();
	int useGoodByIndex(DWORD ndIndex);//根据下标使用背包物品
	int getGoodIndexByName(char* szpGoodName);//根据物品名查询并返回物品下标
	BOOL useGoodByIndex(char* szpGoodName);//根据物品名使用背包物品
}_TBACK_PACK_LIST_OBJ;

//怪物结构
typedef struct TMONSTER_OBJ{
	//0x0C所有对象数组的下标
	DWORD ndIndexByAllObj;
	//+5f4	//血量
	DWORD ndHp;
	//+5f8	//等级
	DWORD ndLevel;
	//+3c0	//存在 1-存活；0-死亡
	DWORD isDead;
	//+360	//名字
	char* szpName;
	//+1060	//坐标1
	float flCurX;
	//+1068	//坐标2
	float flCurY;
	DWORD ndDistance;//距离玩家
}_TMONSTER_OBJ;

typedef struct TMONSTER_LIST_OBJ{
	TMONSTER_OBJ tMonsterList[100];

	TMONSTER_LIST_OBJ* getData();
	BOOL TMONSTER_LIST_OBJ::dbgPrintMsg();
}_TMONSTER_LIST_OBJ;

//人物动作
//动作对象结构
typedef struct TACTION_OBJ{
	char *szpName;
	DWORD ndActionId;
}_TACTION_OBJ;

//动作对象数组
typedef struct TACTION_LIST_OBJ{
	TACTION_OBJ tList[12];

	TACTION_LIST_OBJ* getData();
	BOOL TACTION_LIST_OBJ::dbgPrintMsg();
	BOOL UseAction(DWORD ndIndex);
	BOOL UseAction(char* szpIndexName);
}_TACTION_LIST_OBJ;

typedef struct TROLE_OBJ{
	//+000c	//下标（LEA     EDX,DWORD PTR DS:[ECX*4+2D3D598]	; 玩家、动作、怪物...）
	//+0018	//名字
	//+1a3c	//选择怪物
	//+33c4	//选中状态
	DWORD ndSelectIndex;
	float flCurX;
	float flCurY;

	TROLE_OBJ* TROLE_OBJ::getData();
	BOOL TROLE_OBJ::selectObj(DWORD ndIndexByObj);
	BOOL TROLE_OBJ::selectMonsterByNear();//选择最近的怪物
	BOOL TROLE_OBJ::AutoAttackMonster();//自动打怪
	DWORD TROLE_OBJ::getSelectObjType();//返回选择的类型 obj+0x8=0x2E
}_TROLE_OBJ;


typedef struct  TSKILL_OBJ{
	DWORD ndIndexBySkill;
	//+8		//分类（1b-技能分类<书>	1c-技能对象分类）
	DWORD ndType;
	//+0c		//
	DWORD ndIndexByAll;
	//+5c		//对象名字
	char* szpName;
	//+0b1	//技能所属职业
	//+1f6	//（2字节）是否已学技能（1-已学 0-未学）
	BOOL isUseable;

	DWORD ndObjBase;//对象基址
}_TSKILL_OBJ;

typedef struct TSKILL_LIST_OBJ{
	TSKILL_OBJ tSkillList[32];

	TSKILL_LIST_OBJ* TSKILL_LIST_OBJ::getData();
	void TSKILL_LIST_OBJ::dbgPrintMsg();
	BOOL TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName, DWORD ndIndexF1F10);
}_TSKILL_LIST_OBJ;

#define F1F10Size 10
typedef struct TF1_F10_OBJ{
	//+8		//类型（1E）
	DWORD ndType;
	//+5c		//技能名字
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
