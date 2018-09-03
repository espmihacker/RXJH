#include "BaseGame.h"
#include "StructGame.h"
#include <Windows.h>
#include <stdio.h>//strcat_s
#include <math.h>
#include "TypeObj.h"

TROLE_PROPERTY g_tRoleProperty;
TACTION_LIST_OBJ g_tActionListObj;		//�����ṹ�б����
TBACK_PACK_LIST_OBJ g_tBackPackListObj;	//�����ṹ�б����
TMONSTER_LIST_OBJ g_tMonsterListObj;	//����ṹ�б����
TROLE_OBJ g_tRoleObj;					//��ҽṹ����
TSKILL_LIST_OBJ g_tSkillList;			//��������
TF1_F10_LIST_OBJ g_tF1_F10List;			//���������

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

//--------------------------------------��ɫ��ش���--------------------------------------------------
TROLE_PROPERTY* TROLE_PROPERTY::getData(){
	try
	{
		szpRoleName = (char*)Base_RolePropetry;
		ndLevel = *(BYTE*)(Base_RolePropetry + 0x34);
		ndLevelְҵ = *(BYTE*)(Base_RolePropetry + 0x35);
		szp���� = (char*)(Base_RolePropetry + 0x36);
		ndHp = *(DWORD*)(Base_RolePropetry + 0x80);
		ndMp = *(DWORD*)(Base_RolePropetry + 0x84);
		ndAngry = *(DWORD*)(Base_RolePropetry + 0x88);
		ndMaxHp = *(DWORD*)(Base_RolePropetry + 0x8c);
		ndMaxMp = *(DWORD*)(Base_RolePropetry + 0x90);
		naMaxAngry = *(DWORD*)(Base_RolePropetry + 0x94);
		nqExp = *(QWORD*)(Base_RolePropetry + 0x98);
		nqExpNextRequire = *(QWORD*)(Base_RolePropetry + 0xa0);
		ndLiLian = *(DWORD*)(Base_RolePropetry + 0xac);
		nd�� = *(DWORD*)(Base_RolePropetry + 0xb0);
		nd�� = *(DWORD*)(Base_RolePropetry + 0xb4);
		nd�� = *(DWORD*)(Base_RolePropetry + 0xb8);
		nd�� = *(DWORD*)(Base_RolePropetry + 0xbc);
		nd������ = *(DWORD*)(Base_RolePropetry + 0xc8);
		nd������ = *(DWORD*)(Base_RolePropetry + 0xcc);
		nd������ = *(DWORD*)(Base_RolePropetry + 0xd0);
		nd�ر��� = *(DWORD*)(Base_RolePropetry + 0xd4);
		nqMoney = *(QWORD*)(Base_RolePropetry + 0xe4);
		nw���� = *(WORD*)(Base_RolePropetry + 0xec);
		nwMax���� = *(WORD*)(Base_RolePropetry + 0xee);
		ndPoint���� = *(BYTE*)(Base_RolePropetry + 0xf0);
		for(int i = 0; i < 32; i++){
			ndQiGongPoint[i] = *(BYTE*)(Base_RolePropetry + 0xf4 + 4 * i);
		}
	}
	catch (...)
	{
		DbgPrintfMine("��ȡ������Ϣ�쳣");
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

//------------------------------------������ش���--------------------------------------------------

TBACK_PACK_LIST_OBJ* TBACK_PACK_LIST_OBJ::getData(){
	try
	{
		DWORD ndBase = *(DWORD*)Base_BackpackList;
		DWORD ndFirstGoodBase = ndBase + 0x410;
		DWORD ndObj = NULL;
		for(int i = 0; i < nBackPackSize; i++) {
			ndObj = *(DWORD*)(ndFirstGoodBase + 4 * i);//ȡ����i�����ĵ�ַ
			if(ndObj == NULL){
				this->mtGoodList[i].ndGoodNum = 0;
				this->mtGoodList[i].szpGoodName = NULL;
				this->mtGoodList[i].szpGoodDesc = NULL;
				continue;
			}
			this->mtGoodList[i].szpGoodName = (char*)(ndObj + 0x05c);//ȡ����Ʒ����
			this->mtGoodList[i].szpGoodDesc = (char*)(ndObj + 0x0f1);//ȡ����Ʒ����
			this->mtGoodList[i].ndGoodNum = *(DWORD*)(ndObj + 0xc44);//ȡ����Ʒ����
		}
	}
	catch (...)
	{
		DbgPrintfMine("��ȡ������Ϣ�쳣");
		return FALSE;
	}
	return this;
}

// ʹ�ñ�����Ʒ�������±�
// ndIndex�Ǳ������±� 0..35
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
		DbgPrintfMine("useGoodForIndex(DWORD ndIndex)����");
		return FALSE;
	}
}

int  scomp(char *str1,const char *str2)
{
	int i=0;
	char c1,c2;
	do
	{
		c1=(str1[i]>='A'&& str1[i]<='Z')?str1[i]+32:str1[i];//����ʹ�ü��ɣ�ָ�����е�Сд��ĸ���ȴ�Щ��ĸ��ASEII���32
		c2=(str2[i]>='A'&& str2[i]<='Z')?str2[i]+32:str2[i];
		i++;
	}while(c1==c2  && c1!='\0' && c2!='\0');//���û�в���Ȼ���ѭ�������

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

// ������Ʒ����ѯ��������Ʒ�±�
int TBACK_PACK_LIST_OBJ::getGoodIndexByName(char* szpGoodName){
	//��ʼ���ṹ
	this->getData();
	//��������
	int i;
	for (i = 0; i < nBackPackSize; i++)
	{
		//�Ƚϱ�����Ʒ����
		if(this->mtGoodList[i].szpGoodName != NULL && m_strcmp(szpGoodName, this->mtGoodList[i].szpGoodName) == 0){
			return i;
		}
	}
	return -1;
}

//������Ʒ��ʹ�ñ�����Ʒ
BOOL TBACK_PACK_LIST_OBJ::useGoodByIndex(char* szpGoodName){
	DWORD ndIndex = getGoodIndexByName(szpGoodName);
	if(ndIndex == -1){
		return FALSE;
	}
	useGoodByIndex(ndIndex);

	return TRUE;
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

//--------------------------------------������ش���--------------------------------------------------

TMONSTER_LIST_OBJ* TMONSTER_LIST_OBJ::getData(){
	__try
	{
		//+5f4	//Ѫ��
		//+5f8	//�ȼ�
		//+354	//���� 1-��0-����
		//+360	//����
		//+1060	//����1
		//+1068	//����2
		DWORD ndObj = NULL;
		memset(this, 0, sizeof(TMONSTER_LIST_OBJ));
		int i = 0;//���������±�
		for (int j = 0; j < 100; j++){//�������������±�
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
			tMonsterList[i].ndIndexByAllObj = *(DWORD*)(ndObj + 0xc);//���������±�
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
		DbgPrintfMine("TMONSTER_LIST_OBJ::getData() ����");
		return FALSE;
	}

	return this;
}

BOOL TMONSTER_LIST_OBJ::dbgPrintMsg(){
	for(int i = 0; i < 20; i++){
		if(tMonsterList[i].ndLevel == NULL) {
			continue;
		}
		DbgPrintfMine("ID=%d %s[%d]:�ȼ�=%d��(%f,%f),���룺%d | %d \r\n", 
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

//+0c//�ܵĶ��������±�
//+08//������
//+4c//��������ID������CALLʹ��CALL����
//+5c//����ƫ��
TACTION_LIST_OBJ* TACTION_LIST_OBJ::getData(){
	try
	{
		DWORD ndFirstObj = 0;
		DWORD ndObj = NULL;

		ndFirstObj = *(DWORD*)(Base_ActionList) + 0x410;
		for(int i = 0; i < 12; i++){
			ndObj = *(DWORD*)(ndFirstObj + 4 * i);
			tList[i].szpName = (char*)(ndObj + 0x5c);
			tList[i].ndActionId = *(DWORD*)(ndObj + 0x4c);
		}
	}
	catch (...)
	{
		DbgPrintfMine("TACTION_LIST_OBJ::getData() �쳣");
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
		DbgPrintfMine("UseAction(DWORD ndIndex) ����");
		return FALSE;
	}

	return TRUE;
}

BOOL TACTION_LIST_OBJ::UseAction(char* szpIndexName){
	this->getData();//��ʼ����������
	for(int i = 0; i < 12; i++){
		if(strcmp(tList[i].szpName,szpIndexName) == 0){
			UseAction(i);

			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------ѡ����ش���--------------------------------------------------

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
		DbgPrintfMine("TROLE_OBJ::getData() ����");
		return FALSE;
	}
}

//ѡ�����
BOOL TROLE_OBJ::selectObj(DWORD ndIndexByObj){
	try
	{
		__asm
		{
			//ȡ��ѡ�������±�
			mov edi,DWORD PTR DS:[Base_RoleObj]
			MOV EAX,DWORD PTR DS:[EDI+Offset_SelectIndex]
			cmp eax,0xFFFF	//�������
			jz NEXTLABLE
			//��ȡѡ�ж���
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
		//��ʾѡ��״̬
		__asm
		{
			//��ȡѡ�ж���
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
		DbgPrintfMine("TROLE_OBJ::selectObj(DWORD ndIndexByObj) ����");
		return FALSE;
	}

	return TRUE;
}

//ѡ������Ĺ���
BOOL TROLE_OBJ::selectMonsterByNear(){
	DWORD ndIndex = 0xFFFF;
	DWORD ndDistance = 0xFFFF;
	//�������������б������б�
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
			ndIndex = obj.ndIndexByAllObj;//�������Ĺ���ID
			
		}
	}
	//�жϾ���
	//ѡ����� selectObj
	selectObj(ndIndex);
	return TRUE;
}

//����ѡ����������
DWORD TROLE_OBJ::getSelectObjType(){
	try{
		DWORD ndCurrentSelecctType = NULL;
		DWORD ndCurrentSelecctId = NULL;
		DWORD ndCurrentSelectObj = NULL;
		if(g_tRoleObj.getData()->ndSelectIndex == 0xFFFF){
			return NULL;
		}
		//���ݵ�ǰѡ�е�ID��ȡ��ѡ�е�����
		ndCurrentSelecctId = g_tRoleObj.getData()->ndSelectIndex;
		ndCurrentSelectObj = *(DWORD*)(Base_AllListObj + 4 * ndCurrentSelecctId);
		ndCurrentSelecctType = *(DWORD*)(ndCurrentSelectObj + Offset_ObjType);

		return ndCurrentSelecctType;

	}catch(...){
		DbgPrintfMine("TROLE_OBJ::getSelectObjType() ����");
		return FALSE;
	}
}

//�Զ����
BOOL TROLE_OBJ::autoAttackMonster(){
	//ѡ��
	if(getSelectObjType() != TYPE_MONSTER){
		selectMonsterByNear();
	}
	//����
	g_tActionListObj.getData()->UseAction("����");

	return TRUE;
}

BOOL TROLE_OBJ::autoAttackMonsterBySkill(char* szpSkillName){
	//ѡ��
	if(getSelectObjType() != TYPE_MONSTER){
		selectMonsterByNear();
	}
/*
	//���ü���
	BOOL isDroped = g_tSkillList.getData()->dropSkillF1F10(szpSkillName);
	//ʹ�ü��ܹ���
	if(isDroped){
		g_tF1_F10List.getData()->useSkillByName(szpSkillName);//���ܹ���
	}else{
		g_tActionListObj.getData()->UseAction("����");;//��ͨ����
	}
*/
	g_tF1_F10List.getData()->useSkillByName(szpSkillName);//���ܹ���

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
			mov dword ptr ss:[eax+0x1c],1//���µ�ֵ�޹ؽ�Ҫ
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
		DbgPrintfMine("TROLE_OBJ::findWay(int niX, int niY) ����");
		return FALSE;
	}
}

//--------------------------------------�����б����--------------------------------------------------

TSKILL_LIST_OBJ* TSKILL_LIST_OBJ::getData(){
	//			dd [[2D18DEC]+410+4*i]
	//+8		//���ࣨ1b-���ܷ���<��>	1c-���ܶ�����ࣩ
	//+0c		//
	//+5c		//��������
	//+ac		//����ȼ�
	//+0b1		//��������ְҵ
	//+1f6		//��2�ֽڣ��Ƿ���ѧ���ܣ�1-��ѧ 0-δѧ��
	//+268		//��������
	try{
		DWORD *ndPSkillList = NULL;
		ndPSkillList = (DWORD*)((*(DWORD*)Base_SkillList) + 0x410);
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
		DbgPrintfMine("TSKILL_LIST_OBJ::getData() ����");
		return FALSE;
	}
}

BOOL TSKILL_LIST_OBJ::isCanStudy(DWORD ndIndex){
	DWORD ndIsStudy = NULL;//��ǰ����δѧ
	DWORD ndCurrentLiLian = NULL;//��ǰ����ֵ
	DWORD ndCurrentLevel = NULL;//��ǰ�ȼ�
	DWORD ndSkillLiLian = NULL;//������������
	DWORD ndSkillLiLevel = NULL;//���ܵȼ�����
	
	if(g_tSkillList.getData()->tSkillList[ndIndex].ndType == NULL){
		DbgPrintfMine("��ǰ����Ϊ�գ�");
		return FALSE;
	}

	ndIsStudy = g_tSkillList.getData()->tSkillList[ndIndex].isUseable;
	ndCurrentLiLian = g_tRoleProperty.getData()->ndLiLian;
	ndCurrentLevel = g_tRoleProperty.getData()->ndLevel;
	ndSkillLiLian = g_tSkillList.getData()->tSkillList[ndIndex].ndRequireLiLian;
	ndSkillLiLevel = g_tSkillList.getData()->tSkillList[ndIndex].ndRequireLevel;

	if(ndIsStudy != 1 && ndCurrentLiLian >= ndSkillLiLian && ndCurrentLevel >= ndSkillLiLevel){
		DbgPrintfMine("��ǰ���ܿ�ѧ��");
		return TRUE;
	}
	DbgPrintfMine("��ǰ���ܲ���ѧ��");
	return FALSE;
}

void TSKILL_LIST_OBJ::dbgPrintMsg(){
	this->getData();
	for(int i = 0; i < 32; i++){
		if(this->tSkillList[i].szpName != NULL) {
			DbgPrintfMine("%s %d %2X %4X ���÷�%d��|�ȼ���%d ������%d\r\n",
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
		this->getData(); //��ʼ������
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
			mov edx,dword ptr ds:[edi+0x1608]
			mov eax,dword ptr ds:[edi+0x1c10]
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
		DbgPrintfMine("TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName, DWORD ndIndexF1F10) ����");
		return FALSE;
	}
}

BOOL TSKILL_LIST_OBJ::dropSkillF1F10(char* szpSkillName){
	//��⼼���Ƿ��ڿ�����ϴ���
	int niIndex = g_tF1_F10List.getData()->getIndexByName(szpSkillName);
	if(niIndex >= 0){
		return TRUE;
	}
	//��Ҫ�ҿ�λ�÷��ü���
	niIndex = g_tF1_F10List.getData()->getEmptyIndex();
	if(niIndex == -1){
		DbgPrintfMine("�����������");
		return FALSE;
	}
	BOOL result = dropSkillF1F10(szpSkillName, niIndex);

	return result;
}

//��������
BOOL TSKILL_LIST_OBJ::practiceSkill(DWORD ndIndex){
	try{
		if(!TSKILL_LIST_OBJ::isCanStudy(ndIndex)){//�����޷�ѧϰ��������������
			return FALSE;
		}
		DWORD ndObj = *(DWORD*)Base_SkillList + 0x410;
		ndObj = ((DWORD*)ndObj)[ndIndex];//���Ƚ���,������£�
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
		DbgPrintfMine("TSKILL_LIST_OBJ::practiceSkill(DWORD ndIndex) ����");
		return FALSE;
	}
}

BOOL TSKILL_LIST_OBJ::practiceSkill(char* szpSkillName){
	this->getData(); //��ʼ������
	for(int i = 0; i < 32; i++){
		if(tSkillList[i].ndType != NULL && strcmp(szpSkillName, tSkillList[i].szpName) == 0){
			practiceSkill(i);
			return TRUE;
		}
	}
	return FALSE;
}

//------------------------------------��ݼ�����--------------------------------------------------

TF1_F10_LIST_OBJ* TF1_F10_LIST_OBJ::getData(){
	try
	{
		memset(this, 0, sizeof(TF1_F10_LIST_OBJ));
		DWORD *baseF1_F10 = (DWORD*)((*(DWORD*)Base_F1_F10List)+0x410);
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
		DbgPrintfMine("TF1_F10_LIST_OBJ::getData() ����");
		return NULL;
	}
}

//��ȡ�����ڿ�����ϵ��±꣬�����ڷ���-1
int TF1_F10_LIST_OBJ::getIndexByName(char* szpSkillName){
	for(int i = 0; i < F1F10Size; i++){
		if(tF1F10List[i].ndType != NULL && strcmp(tF1F10List[i].szpSkillName, szpSkillName) == 0){
			return i;
			break;//��ռCPUʱ��
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
				mov ecx,[ecx+0x27c]
				mov eax,BaseCall_F1_F10Call
				call eax
		}
		return TRUE;
	}catch(...){
		DbgPrintfMine("TF1_F10_LIST_OBJ::useSkillByIndex(int index) ����");
		return FALSE;
	}
}

//��ȡ������ϵ�һ����λ�±꣬û�з���-1
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
	if(strcmp(szpSkillName, "����") == 0){//�������ͨ����
		g_tActionListObj.UseAction("����");
		return TRUE;
	}
	niIndex = getIndexByName(szpSkillName);//�������ֻ�ȡ�ڿ�����ϵ�λ��
	if(niIndex == -1){
		/*
		//���ü��ܵ������
		emptyIndex = getEmptyIndex();
		if(emptyIndex != -1){//������δ��
			g_tSkillList.getData()->dropSkillF1F10(szpSkillName, emptyIndex);
		}else{
			DbgPrintfMine("���������");
			return FALSE;
		}
		*/
		DbgPrintfMine("����[%s]δ����", szpSkillName);

		return FALSE;
	}
	useSkillByIndex(niIndex);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//����������֮��ľ���
DWORD play2PointDistance(float x1, float y1, float x2, float y2){
	DWORD ndDistanse = 0xFFFF;
	float a = abs(y1 - y2);
	float b = abs(x1-x2);
	float c = sqrt(a*a + b*b);

	ndDistanse = (DWORD)c;

	return ndDistanse;
}