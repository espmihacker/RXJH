//��ַ����Ԫ

#define Base_GameWndHandle 0x0117F328	//��Ϸ�����ھ��'

#define Base_RolePropetry 0x02BD38B8	//��������ַ'
#define Base_EquipList 0x2DF8498		//װ���б��ַ'
#define Base_BackpackList 0x02DF849C	//���������ַ'
#define Base_DepotList 0x02E019EC		//�ֿ��б��ַ
#define Base_NearObjList 0x04236DD8		//�����б��ַ'
#define Base_ActionList	0x02DF8E18		//��Ҷ�������'
#define Base_RoleObj 0x2E20A84			//��Ҷ����ַ'
#define Base_AllListObj 0x02E20A88		//���ж�������'
#define Base_SkillList 0x2DFA024		//�����б��ַ'
#define	Base_SelectGoodAndSkill 0x011b08e8	//ѡ����Ʒ�ͼ���'

#define Base_DropSkillArg 0x02DF9FC8		//���ü���call����'
#define Base_F1_F10Arg 0x11B08F8			//���������' +280
#define Base_PracticeSkillArg1 0x2BD3964	//�������ܲ���1'

//���ø���
#define Base_PracticeSkillArg2 Base_RoleObj	//�������ܲ���2��������ҽ�ɫ��ַ
#define Base_F1_F10List Base_DropSkillArg	//����������ַ

//CALL
#define BaseCall_UserGoodsForIndex 0x00817fb0	//��Ʒʹ��CALL'
#define BaseCall_ActionUse 0x006F7800  			//����Call'
#define BaseCall_ActionUseEax 0x011B08F8		//����CallEax' (*(DWORD*))((*(DWORD*)(0x10cfcf) + 0x27c))
#define BaseCall_DropSkill 0x008291B0			//���ü���call'
#define BaseCall_F1_F10Call 0x007068F0			//��ݼ�CALL'
#define BaseCall_PracticeSkill 0x00543760		//��������CALL'
#define BaseCall_MoveGoods 0x008291B0			//�ƶ���ƷCALL

//OFFSET
#define Offset_ObjType		0x8			//��������ƫ��
#define Offset_SelectIndex 0x1a4c		//���ѡ�й���ƫ��
#define Offset_RoleCurrentX 0x1c48		//��ҵ�ǰ����Xƫ�� //1a50
#define Offset_RoleCurrentY 0x1c50		//��ҵ�ǰ����Yƫ�� //1a58
