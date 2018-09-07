#include "BaseGame.h"
#include "StructGame.h"
#include <Windows.h>
#include <stdio.h>//strcat_s
#include <math.h>
#include "TypeObj.h"

TROLE_PROPERTY g_tRoleProperty;
TACTION_LIST_OBJ g_tActionListObj;		//动作结构列表对象
TBACK_PACK_LIST_OBJ g_tBackPackListObj;	//背包结构列表对象
TMONSTER_LIST_OBJ g_tMonsterListObj;	//怪物结构列表对象
TROLE_OBJ g_tRoleObj;					//玩家结构对象
TSKILL_LIST_OBJ g_tSkillList;			//技能数组
TF1_F10_LIST_OBJ g_tF1_F10List;			//快捷栏数组

void DbgPrintfMine(char* pszFormat,...);

void DbgPrintfMine(char* pszFormat,...){
#ifdef _DEBUG
	char szBufFormat[0x1000];
	char szBufFormat_Game[0x100F]="GameData:";

	va_list argList;
	va_start(argList, pszFormat);

	//int i = va_arg(argList, int);
	//char* s = va_arg(argList, char*);
	vsprintf_s(szBufFormat, pszFormat, argList);
	//printf("%d,%s", i, s);
	//printf(szBufFormat);
	strcat_s(szBufFormat_Game, szBufFormat);
	OutputDebugStringA(szBufFormat_Game);

	va_end(argList);
#endif
}

//--------------------------------------角色相关代码--------------------------------------------------
TROLE_PROPERTY* TROLE_PROPERTY::getData(){
	try
	{
		szpRoleName = (char*)Base_RolePropetry;
		ndLevel = *(BYTE*)(Base_RolePropetry + 0x34);
		ndLevel职业 = *(BYTE*)(Base_RolePropetry + 0x35);
		szp名声 = (char*)(Base_RolePropetry + 0x36);
		ndHp = *(DWORD*)(Base_RolePropetry + 0x80);
		ndMp = *(DWORD*)(Base_RolePropetry + 0x84);
		ndAngry = *(DWORD*)(Base_RolePropetry + 0x88);
		ndMaxHp = *(DWORD*)(Base_RolePropetry + 0x8c);
		ndMaxMp = *(DWORD*)(Base_RolePropetry + 0x90);
		naMaxAngry = *(DWORD*)(Base_RolePropetry + 0x94);
		nqExp = *(QWORD*)(Base_RolePropetry + 0x98);
		nqExpNextRequire = *(QWORD*)(Base_RolePropetry + 0xa0);
		ndLiLian = *(DWORD*)(Base_RolePropetry + 0xac);
		nd心 = *(DWORD*)(Base_RolePropetry + 0xb0);
		nd气 = *(DWORD*)(Base_RolePropetry + 0xb4);
		nd体 = *(DWORD*)(Base_RolePropetry + 0xb8);
		nd魄 = *(DWORD*)(Base_RolePropetry + 0xbc);
		nd攻击力 = *(DWORD*)(Base_RolePropetry + 0xc8);
		nd防御力 = *(DWORD*)(Base_RolePropetry + 0xcc);
		nd命中率 = *(DWORD*)(Base_RolePropetry + 0xd0);
		nd回避率 = *(DWORD*)(Base_RolePropetry + 0xd4);
		nqMoney = *(QWORD*)(Base_RolePropetry + 0xe4);
		nw负重 = *(WORD*)(Base_RolePropetry + 0xec);
		nwMax负重 = *(WORD*)(Base_RolePropetry + 0xee);
		ndPoint气功 = *(BYTE*)(Base_RolePropetry + 0xf0);
		for(int i = 0; i < 32; i++){
			ndQiGongPoint[i] = *(BYTE*)(Base_RolePropetry + 0xf4 + 4 * i);
		}
	}
	catch (...)
	{
		DbgPrintfMine("读取人物信息异常");
		return FALSE;
	}

	return this;
}

char* TROLE_PROPERTY::GetRoleName(){
	return getData()->szpRoleName;
}

DWORD TROLE_PROPERTY::GetRoleLevel(){
	return getData()->ndLevel;;
}

//------------------------------------背包相关代码--------------------------------------------------

TBACK_PACK_LIST_OBJ* TBACK_PACK_LIST_OBJ::getData(){
	try
	{
		DWORD ndBase = *(DWORD*)Base_BackpackList;
		DWORD ndFirstGoodBase = ndBase + 0x434;
		DWORD ndObj = NULL;
		for(int i = 0; i < nBackPackSize; i++) {
			ndObj = *(DWORD*)(ndFirstGoodBase + 4 * i);//取出第i格对象的地址
			if(ndObj == NULL){
				this->mtGoodList[i].ndGoodNum = 0;
				this->mtGoodList[i].szpGoodName = NULL;
				this->mtGoodList[i].szpGoodDesc = NULL;
				continue;
			}
			this->mtGoodList[i].szpGoodName = (char*)(ndObj + 0x05c);//取出物品名称
			this->mtGoodList[i].szpGoodDesc = (char*)(ndObj + 0x0f1);//取出物品描述
			this->mtGoodList[i].ndGoodNum = *(DWORD*)(ndObj + 0xc44);//取出物品数量
		}
	}
	catch (...)
	{
		DbgPrintfMine("读取背包信息异常");
		return FALSE;
	}
	return this;
}

// 使用背包物品，根据下标
// ndIndex是背包的下标 0..35
int TBACK_PACK_LIST_OBJ::useGoodByIndex(DWORD ndIndex){
	try
	{
		_asm {
				mov eax,ndIndex
				push eax
				push 1
				push 0
				mov ecx,Base_BackpackList
				mov ecx,[ecx]
				mov eax,BaseCall_UserGoodsForIndex
			call eax
		}
		return TRUE;
	}
	catch (...)
	{
		DbgPrintfMine("useGoodForIndex(DWORD ndIndex)出错");
		return FALSE;
	}
}

int  scomp(char *str1,const char *str2)
{
	int i=0;
	char c1,c2;
	do
	{
		c1=(str1[i]>='A'&& str1[i]<='Z')?str1[i]+32:str1[i];//这里使用技巧，指导所有的小写字母都比大些字母的ASEII码大32
		c2=(str2[i]>='A'&& str2[i]<='Z')?str2[i]+32:str2[i];
		i++;
	}while(c1==c2  && c1!='\0' && c2!='\0');//如果没有不相等或者循环玩结束

	if(c1>c2)
	{
		return 1;
	}
	else if(c1>c2)
	{
		return -1;
	}
	else return 0;
}

int m_strcmp(char*p1,char*p2)
{
	while(p1!=NULL && p2 != NULL)
	{
		while(*p1 == *p2 && *p1 != '\0' && *p2 != '\0') 
		{
			p1++;
			p2++;
		}
		return *p1 - *p2;
	}
	return 0;
}

// 根据物品名查询并返回物品下标
int TBACK_PACK_LIST_OBJ::getGoodIndexByName(char* szpGoodName){
	//初始化结构
	this->getData();
	//遍历背包
	int i;
	for (i = 0; i < nBackPackSize; i++)
	{
		//比较背包物品名字
		if(this->mtGoodList[i].szpGoodName != NULL && m_strcmp(szpGoodName, this->mtGoodList[i].szpGoodName) == 0){
			return i;
		}
	}
	return -1;
}

//根据物品名使用背包物品
BOOL TBACK_PACK_LIST_OBJ::useGoodByIndex(char* szpGoodName){
	DWORD ndIndex = getGoodIndexByName(szpGoodName);
	if(ndIndex == -1){
		return FALSE;
	}
	useGoodByIndex(ndIndex);

	return TRUE;
}

DWORD TBACK_PACK_LIST_OBJ::selectGoods(DWORD ndIndex){//选中背包中的某一格
	try
	{
		DWORD ndObj = NULL;
		__asm{
			mov ebx,ndIndex
			mov edi,dword ptr ds:[Base_BackpackList]//背包/仓库基址
			MOV     EAX,DWORD PTR DS:[EDI+EBX*4+0x410]
			mov		ndObj,eax			//取出对象
			MOV     ECX,DWORD PTR DS:[Base_SelectGoodAndSkill]
			MOV     DWORD PTR DS:[ECX+0x228],EAX
			MOV     EDX,DWORD PTR DS:[Base_SelectGoodAndSkill]
			MOV     BYTE PTR DS:[EDX+0x230],1
			MOV     EAX,DWORD PTR DS:[Base_SelectGoodAndSkill]
			MOV     ECX,DWORD PTR DS:[EAX+0x228]
			MOV     DX,WORD PTR DS:[EDI+0x1608]
		}
		return ndObj;
	}
	catch (...)
	{
		DbgPrintfMine("TBACK_PACK_LIST_OBJ::selectGoods(DWORD ndIndex) 错误");
		return NULL;
	}
}
BOOL TBACK_PACK_LIST_OBJ::moveGoodToDepot(DWORD ndIndex){//移动选中的物品到仓库
	try
	{
		__asm{
			mov edi,dword ptr ds:[Base_DepotList]
			mov edx,dword ptr ds:[edi+0x1608]
			mov eax,dword ptr ds:[edi+0x1c10]
			mov ecx,ndIndex
			push ndIndex
				push edx
				push eax
				mov ecx,edi
				mov eax,BaseCall_MoveGoods
				call eax
		}
		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
	
}

//--------------------------------------怪物相关代码--------------------------------------------------

TMONSTER_LIST_OBJ* TMONSTER_LIST_OBJ::getData(){
	__try
	{
		//+5f4	//血量
		//+5f8	//等级
		//+354	//存在 1-存活；0-死亡
		//+360	//名字
		//+1060	//坐标1
		//+1068	//坐标2
		DWORD ndObj = NULL;
		memset(this, 0, sizeof(TMONSTER_LIST_OBJ));
		int i = 0;//怪物数组下标
		for (int j = 0; j < 100; j++){//附近对象数组下标
			ndObj = *(DWORD*)(Base_NearObjList + 4 * j);
			if(ndObj == NULL || *(DWORD*)(ndObj + Offset_ObjType) != TYPE_MONSTER){
				continue;
			}
			tMonsterList[i].szpName = (char*)(ndObj + 0x360);
			tMonsterList[i].ndHp = *(DWORD*)(ndObj + 0x5f4);
			tMonsterList[i].isDead = *(DWORD*)(ndObj + 0x3c0);
			tMonsterList[i].ndLevel = *(DWORD*)(ndObj + 0x5f8);
			tMonsterList[i].flCurX = *(float*)(ndObj + 0x1060);
			tMonsterList[i].flCurY = *(float*)(ndObj + 0x1068);
			tMonsterList[i].ndIndexByAllObj = *(DWORD*)(ndObj + 0xc);//对象数组下标
			tMonsterList[i].ndDistance = play2PointDistance(
				g_tRoleObj.getData()->flCurX,
				g_tRoleObj.getData()->flCurY,
				tMonsterList[i].flCurX,
				tMonsterList[i].flCurY);
			i++;
		}
	}
	_except(1)
	{
		DbgPrintfMine("TMONSTER_LIST_OBJ::getData() 错误");
		return FALSE;
	}

	return this;
}

BOOL TMONSTER_LIST_OBJ::dbgPrintMsg(){
	this->getData();
	for(int i = 0; i < 20; i++){
		if(tMonsterList[i].ndLevel == NULL) {
			continue;
		}
		DbgPrintfMine("ID=%d %s[%d]:等级=%d，(%f,%f),距离：%d | %d \r\n", 
			tMonsterList[i].ndIndexByAllObj,
			tMonsterList[i].szpName,
			tMonsterList[i].ndHp,
			tMonsterList[i].ndLevel,
			tMonsterList[i].flCurX,
			tMonsterList[i].flCurY,
			tMonsterList[i].ndDistance,
			tMonsterList[i].isDead);
	}
	
	return TRUE;
}

//+0c//总的对象数组下标
//+08//分类编号
//+4c//动作分类ID，动作CALL使用CALL参数
//+5c//名字偏移
TACTION_LIST_OBJ* TACTION_LIST_OBJ::getData(){
	try
	{
		DWORD ndFirstObj = 0;
		DWORD ndObj = NULL;

		ndFirstObj = *(DWORD*)(Base_ActionList) + 0x434;
		for(int i = 0; i < 12; i++){
			ndObj = *(DWORD*)(ndFirstObj + 4 * i);
			tList[i].szpName = (char*)(ndObj + 0x5c);
			tList[i].ndActionId = *(DWORD*)(ndObj + 0x4c);
		}
	}
	catch (...)
	{
		DbgPrintfMine("TACTION_LIST_OBJ::getData() 异常");
		return FALSE;
	}

	return this;
}

BOOL TACTION_LIST_OBJ::dbgPrintMsg(){
	for(int i = 0; i < 12; i++){
		DbgPrintfMine("%s[%d] ID = %d",tList[i].szpName, i, tList[i].ndActionId);
	}

	return TRUE;
}

BOOL TACTION_LIST_OBJ::UseAction(DWORD ndIndex){
	try
	{
		DWORD ndEax = BaseCall_ActionUseEax;
		DWORD ndArg1 = getData()->tList[ndIndex].ndActionId;
		__asm
		{
			mov edx,ndArg1
			mov eax,ndEax
			mov ecx,[eax+0x27c]
			push edx
			mov eax,BaseCall_ActionUse
			call eax
		}
	}
	catch (...)
	{
		DbgPrintfMine("UseAction(DWORD ndIndex) 错误");
		return FALSE;
	}

	return TRUE;
}

BOOL TACTION_LIST_OBJ::UseAction(char* szpIndexName){
	this->getData();//初始化动作序列
	for(int i = 0; i < 12; i++){
		if(strcmp(tList[i].szpName,szpIndexName) == 0){
			UseAction(i);

			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------选怪相关代码--------------------------------------------------

TROLE_OBJ* TROLE_OBJ::getData(){
	try
	{
		DWORD ndRoleObj = NULL;
		ndRoleObj = *(DWORD*)Base_RoleObj;
		ndSelectIndex = *(DWORD*)(ndRoleObj + Offset_SelectIndex);
		flCurX = *(float*)(ndRoleObj + Offset_RoleCurrentX);
		flCurY = *(float*)(ndRoleObj + Offset_RoleCurrentY);

		return this;
	}
	catch (...)
	{
		DbgPrintfMine("TROLE_OBJ::getData() 错误");
		return FALSE;
	}
}

//选择对象
BOOL TROLE_OBJ::selectObj(DWORD ndIndexByObj){
	try
	{
		__asm
		{
			//取消选择对象的下标
			mov edi,DWORD PTR DS:[Base_RoleObj]
			MOV EAX,DWORD PTR DS:[EDI+Offset_SelectIndex]
			cmp eax,0xFFFF	//相等则跳
			jz NEXTLABLE
			//获取选中对象
			MOV ECX,DWORD PTR DS:[EAX*4+Base_AllListObj]
			MOV EDX,DWORD PTR DS:[ECX]
			MOV EAX,DWORD PTR DS:[EDX+4]
			push 0
			push 0
			push 0x450
			call eax
		}
NEXTLABLE:
		DWORD ndRoleObj = NULL;
		ndRoleObj = *(DWORD*)Base_RoleObj;
		*(DWORD*)(ndRoleObj + Offset_SelectIndex) = ndIndexByObj;
		//显示选中状态
		__asm
		{
			//获取选中对象
			mov eax,ndIndexByObj
			MOV ECX,DWORD PTR DS:[EAX*4+Base_AllListObj]
			MOV EDX,DWORD PTR DS:[ECX]
			MOV EAX,DWORD PTR DS:[EDX+4]
			push 0
			push 1
			push 0x450
			call eax
		}
	}
	catch (...)
	{
		DbgPrintfMine("TROLE_OBJ::selectObj(DWORD ndIndexByObj) 错误");
		return FALSE;
	}

	return TRUE;
}

//选择最近的怪物
BOOL TROLE_OBJ::selectMonsterByNear(){
	DWORD ndIndex = 0xFFFF;
	DWORD ndDistance = 0xFFFF;
	//遍历整个怪物列表（对象列表）
	for(int i = 0; i < 100; i++){
		//if(g_tMonsterListObj.getData()->tMonsterList[i].ndIndexByAllObj == 0){
		//	continue;
		//}
		//if(g_tMonsterListObj.getData()->tMonsterList[i].ndDistance < ndDistance){
		//	ndDistance = g_tMonsterListObj.getData()->tMonsterList[i].ndDistance;
		//	ndIndex = g_tMonsterListObj.getData()->tMonsterList[i].ndIndexByAllObj;
		//}
		TMONSTER_OBJ obj = g_tMonsterListObj.getData()->tMonsterList[i];
		if(obj.ndIndexByAllObj != 0 && obj.ndDistance < ndDistance && obj.ndLevel == 8){
			ndDistance = obj.ndDistance;
			ndIndex = obj.ndIndexByAllObj;//最近距离的怪物ID
			
		}
	}
	//判断距离
	//选择怪物 selectObj
	selectObj(ndIndex);
	return TRUE;
}

//返回选择对象的类型
DWORD TROLE_OBJ::getSelectObjType(){
	try{
		DWORD ndCurrentSelecctType = NULL;
		DWORD ndCurrentSelecctId = NULL;
		DWORD ndCurrentSelectObj = NULL;
		if(g_tRoleObj.getData()->ndSelectIndex == 0xFFFF){
			return NULL;
		}
		//根据当前选中的ID，取得选中的类型
		ndCurrentSelecctId = g_tRoleObj.getData()->ndSelectIndex;
		ndCurrentSelectObj = *(DWORD*)(Base_AllListObj + 4 * ndCurrentSelecctId);
		ndCurrentSelecctType = *(DWORD*)(ndCurrentSelectObj + Offset_ObjType);

		return ndCurrentSelecctType;

	}catch(...){
		DbgPrintfMine("TROLE_OBJ::getSelectObjType() 错误");
		return FALSE;
	}
}

//自动打怪
BOOL TROLE_OBJ::autoAttackMonster(){
	//选怪
	if(getSelectObjType() != TYPE_MONSTER){
		selectMonsterByNear();
	}
	//攻击
	g_tActionListObj.getData()->UseAction("攻击");

	return TRUE;
}

BOOL TROLE_OBJ::autoAttackMonsterBySkill(char* szpSkillName){
	//选怪
	if(getSelectObjType() != TYPE_MONSTER){
		selectMonsterByNear();
	}
/*
	//放置技能
	BOOL isDroped = g_tSkillList.getData()->dropSkillF1F10(szpSkillName);
	//使用技能攻击
	if(isDroped){
		g_tF1_F10List.getData()->useSkillByName(szpSkillName);//技能攻击
	}else{
		g_tActionListObj.getData()->UseAction("攻击");;//普通攻击
	}
*/
	g_tF1_F10List.getData()->useSkillByName(szpSkillName);//技能攻击

	return TRUE;
}

BOOL TROLE_OBJ::findWay(int niX, int niY){
	try{
		__asm{
			sub esp,34
			mov eax,esp
			mov ecx,niX
			mov dword ptr ss:[eax+0],ecx//X
			fild dword ptr ss:[eax+0]
			fstp dword ptr ss:[eax+0]
			mov dword ptr ss:[eax+4],0//Z
			mov ecx,niY
			mov dword ptr ss:[eax+8],ecx//Y
			fild dword ptr ss:[eax+8]
			fstp dword ptr ss:[eax+8]
			mov dword ptr ss:[eax+0x0c],0
			mov dword ptr ss:[eax+0x10],0
			mov dword ptr ss:[eax+0x14],0
			mov dword ptr ss:[eax+0x18],0xFFFF
			mov dword ptr ss:[eax+0x1c],1//以下的值无关紧要
			mov dword ptr ss:[eax+0x20],1
			mov dword ptr ss:[eax+0x24],0
			mov dword ptr ss:[eax+0x28],0
			mov dword ptr ss:[eax+0x2c],0
			mov dword ptr ss:[eax+0x30],0
			push 54
			push eax
			push 0x3ef
			MOV     ECX,DWORD PTR DS:[Base_RoleObj]
			MOV     EDX,DWORD PTR DS:[ECX]
			MOV     EDX,DWORD PTR DS:[EDX+4]
			CALL    EDX
			add esp,34
		}

		return TRUE;
	}catch(...){
		DbgPrintfMine("TROLE_OBJ::findWay(int niX, int niY) 错误");
		return FALSE;
	}
}

//--------------------------------------技能列表代码--------------------------------------------------

TSKILL_LIST_OBJ* TSKILL_LIST_OBJ::getData(){
	//			dd [[2D18DEC]+410+4*i]
	//+8		//分类（1b-技能分类<书>	1c-技能对象分类）
	//+0c		//
	//+5c		//对象名字
	//+ac		//所需等级
	//+0b1		//技能所属职业
	//+1f6		//（2字节）是否已学技能（1-已学 0-未学）
	//+268		//所需历练
	try{
		DWORD *ndPSkillList = NULL;
		ndPSkillList = (DWORD*)((*(DWORD*)Base_SkillList) + 0x434);
		memset(this, 0, sizeof(TSKILL_LIST_OBJ));

		for (int i = 0; i < 32; i++){
			if(ndPSkillList[i] != NULL && *(DWORD*)(ndPSkillList[i] + 0x8) != 0x1B){
				tSkillList[i].ndObjBase = ndPSkillList[i];
				tSkillList[i].ndIndexBySkill = i;
				tSkillList[i].ndType = *(DWORD*)(ndPSkillList[i] + 0x8);
				tSkillList[i].ndIndexByAll = *(DWORD*)(ndPSkillList[i] + 0xc);
				tSkillList[i].szpName = (char*)(ndPSkillList[i] + 0x5c);
				tSkillList[i].ndRequireLevel = *(DWORD*)(ndPSkillList[i] + 0xac);
				tSkillList[i].isUseable = *(WORD*)(ndPSkillList[i] + 0x1f6);
				tSkillList[i].ndRequireLiLian = *(DWORD*)(ndPSkillList[i] + 0x268);
			}
		}

		return this;
	}catch(...){
		DbgPrintfMine("TSKILL_LIST_OBJ::getData() 错误");
		return FALSE;
	}
}

BOOL TSKILL_LIST_OBJ::isCanStudy(DWORD ndIndex){
	DWORD ndIsStudy = NULL;//当前技能未学
	DWORD ndCurrentLiLian = NULL;//当前历练值
	DWORD ndCurrentLevel = NULL;//当前等级
	DWORD ndSkillLiLian = NULL;//技能历练需求
	DWORD ndSkillLiLevel = NULL;//技能等级需求
	
	if(g_tSkillList.getData()->tSkillList[ndIndex].ndType == NULL){
		DbgPrintfMine("当前技能为空！");
		return FALSE;
	}

	ndIsStudy = g_tSkillList.getData()->tSkillList[ndIndex].isUseable;
	ndCurrentLiLian = g_tRoleProperty.getData()->ndLiLian;
	ndCurrentLevel = g_tRoleProperty.getData()->ndLevel;
	ndSkillLiLian = g_tSkillList.getData()->tSkillList[ndIndex].ndRequireLiLian;
	ndSkillLiLevel = g_tSkillList.getData()->tSkillList[ndIndex].ndRequireLevel;

	if(ndIsStudy != 1 && ndCurrentLiLian >= ndSkillLiLian && ndCurrentLevel >= ndSkillLiLevel){
		DbgPrintfMine("当前技能可学！");
		return TRUE;
	}
	DbgPrintfMine("当前技能不可学！");
	return FALSE;
}

void TSKILL_LIST_OBJ::dbgPrintMsg(){
	this->getData();
	for(int i = 0; i < 32; i++){
		if(this->tSkillList[i].szpName != NULL) {
			DbgPrintfMine("%s %d %2X %4X 可用否（%d）|等级：%d 历练：%d\r\n",
				this->tSkillList[i].szpName,
				this->tSkillList[i].ndIndexBySkill,
				this->tSkillList[i].ndType,
				this->tSkillList[i].ndIndexByAll,
				this->tSkillList[i].isUseable,
				this->tSkillList[i].ndRequireLevel,
				this->tSkillList[i].ndRequireLiLian
				);
		}
	}
}

BOOL TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName, DWORD ndIndexF1F10){
	try
	{
		DWORD ndObjBase = NULL;
		this->getData(); //初始化数组
		for(int i = 0; i < 32; i++){
			if(tSkillList[i].ndType != NULL && strcmp(szpSkillName, tSkillList[i].szpName) == 0){
				ndObjBase = tSkillList[i].ndObjBase;
				__asm
				{
					mov ecx,Base_SelectGoodAndSkill
					mov ecx,[ecx]
					mov eax,ndObjBase
					mov [ecx+0x228],eax
				}
			}
		}
		if(ndObjBase == NULL){
			return FALSE;
		}
		__asm{
			mov edi,Base_DropSkillArg
			mov edi,[edi]
			mov edx,dword ptr ds:[edi+0x162c]
			mov eax,dword ptr ds:[edi+0x1c58]
			mov ecx,ndIndexF1F10
				push ecx
				push edx
				push eax
				mov ecx,edi
				mov eax,BaseCall_DropSkill
				call eax
		}
		return TRUE;
	}
	catch (...)
	{
		DbgPrintfMine("TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName, DWORD ndIndexF1F10) 错误");
		return FALSE;
	}
}

BOOL TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName){
	//检测技能是否在快捷栏上存在
	int niIndex = g_tF1_F10List.getData()->getIndexByName(szpSkillName);
	if(niIndex >= 0){
		return TRUE;
	}
	//需要找空位置放置技能
	niIndex = g_tF1_F10List.getData()->getEmptyIndex();
	if(niIndex == -1){
		DbgPrintfMine("快捷栏已满！");
		return FALSE;
	}
	BOOL result = dropSkillF1F10(szpSkillName, niIndex);

	return result;
}

//修炼技能
BOOL TSKILL_LIST_OBJ::practiceSkill(DWORD ndIndex){
	try{
		if(!TSKILL_LIST_OBJ::isCanStudy(ndIndex)){//技能无法学习，不满足条件！
			return FALSE;
		}
		DWORD ndObj = *(DWORD*)Base_SkillList + 0x410;
		ndObj = ((DWORD*)ndObj)[ndIndex];//这句较难理解,可拆分如下：
/**************************************************************
		DWORD *ndPObj = (DWORD*)ndObj;
		ndObj = ndPObj[ndIndex];
***************************************************************/
		__asm
		{
			mov edx,ndObj
			mov ecx,dword ptr ds:[Base_PracticeSkillArg1]
			mov eax,dword ptr ds:[edx+0x4c]
				push ecx
				push eax
				sub esp,0x150
				lea ecx,[esp]
				push ecx
				mov ecx,dword ptr ds:[Base_PracticeSkillArg2]
				mov eax,BaseCall_PracticeSkill
				call eax
				add esp,0x150
		}
		return TRUE;
	}catch(...){
		DbgPrintfMine("TSKILL_LIST_OBJ::practiceSkill(DWORD ndIndex) 错误");
		return FALSE;
	}
}

BOOL TSKILL_LIST_OBJ::practiceSkill(char* szpSkillName){
	this->getData(); //初始化数组
	for(int i = 0; i < 32; i++){
		if(tSkillList[i].ndType != NULL && strcmp(szpSkillName, tSkillList[i].szpName) == 0){
			practiceSkill(i);
			return TRUE;
		}
	}
	return FALSE;
}

//------------------------------------快捷键代码--------------------------------------------------

TF1_F10_LIST_OBJ* TF1_F10_LIST_OBJ::getData(){
	try
	{
		memset(this, 0, sizeof(TF1_F10_LIST_OBJ));
		DWORD *baseF1_F10 = (DWORD*)((*(DWORD*)Base_F1_F10List)+0x434);
		for(int i = 0; i < F1F10Size; i++){
			if(baseF1_F10[i] != NULL){
				this->tF1F10List[i].ndType = *(DWORD*)(baseF1_F10[i] + 0x08);
				this->tF1F10List[i].szpSkillName = (char*)(baseF1_F10[i] + 0x5c);
			}
		}

		return this;
	}
	catch (...)
	{
		DbgPrintfMine("TF1_F10_LIST_OBJ::getData() 错误");
		return NULL;
	}
}

//获取技能在快捷栏上的下标，不存在返回-1
int TF1_F10_LIST_OBJ::getIndexByName(char* szpSkillName){
	for(int i = 0; i < F1F10Size; i++){
		if(tF1F10List[i].ndType != NULL && strcmp(tF1F10List[i].szpSkillName, szpSkillName) == 0){
			return i;
			break;//少占CPU时间
		}

	}
	return -1;
}

BOOL TF1_F10_LIST_OBJ::useSkillByIndex(int index){
	try
	{
		__asm
		{
				mov eax,index
				push eax
				mov ecx,Base_F1_F10Arg
				mov ecx,[ecx+0x280]
				mov eax,BaseCall_F1_F10Call
				call eax
		}
		return TRUE;
	}catch(...){
		DbgPrintfMine("TF1_F10_LIST_OBJ::useSkillByIndex(int index) 错误");
		return FALSE;
	}
}

//获取快捷栏上的一个空位下标，没有返回-1
int TF1_F10_LIST_OBJ::getEmptyIndex(void){
	this->getData();
	for(int i = 0; i < F1F10Size; i++){
		if(tF1F10List[i].ndType == NULL){
			return i;
		}
	}
	return -1;
}

BOOL TF1_F10_LIST_OBJ::useSkillByName(char* szpSkillName){
	int niIndex = -1;
	int emptyIndex = -1;
	if(strcmp(szpSkillName, "攻击") == 0){//如果是普通攻击
		g_tActionListObj.UseAction("攻击");
		return TRUE;
	}
	niIndex = getIndexByName(szpSkillName);//根据名字获取在快捷栏上的位置
	if(niIndex == -1){
		/*
		//放置技能到快捷栏
		emptyIndex = getEmptyIndex();
		if(emptyIndex != -1){//技能栏未满
			g_tSkillList.getData()->dropSkillF1F10(szpSkillName, emptyIndex);
		}else{
			DbgPrintfMine("快捷栏已满");
			return FALSE;
		}
		*/
		DbgPrintfMine("技能[%s]未放置", szpSkillName);

		return FALSE;
	}
	useSkillByIndex(niIndex);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//计算两个点之间的距离
DWORD play2PointDistance(float x1, float y1, float x2, float y2){
	DWORD ndDistanse = 0xFFFF;
	float a = abs(y1 - y2);
	float b = abs(x1-x2);
	float c = sqrt(a*a + b*b);

	ndDistanse = (DWORD)c;

	return ndDistanse;
}

HWND getGameWndHandle() {
	try
	{
		HWND hGame = *(HWND*)Base_GameWndHandle;
		return hGame;
	}
	catch (...)
	{
		return NULL;
	}

}