//��ַ����Ԫ

#define Base_GameWndHandle 0x0109E728	//��Ϸ�����ھ��

#define Base_RolePropetry 0x02AF2C78	//��������ַ
#define Base_BackpackList 0x02D1762C	//������������
#define Base_NearObjList 0x041538E8		//�����б����
#define Base_ActionList	0x02d17be0		////dc [[02d17be0]+410+4*0]+5c
#define Base_RoleObj 0x02d3d594			//��Ҷ����ַ���Լ���
#define Base_AllListObj 0x02D3D598		//���ж��������ַ
#define Base_SkillList 0x2D18DEC		//�����б��ַ
#define	Base_SelectGoodAndSkill 0x10cfce8	//ѡ����Ʒ�ͼ���
#define Base_DropSkillArg 0x02D18D90		//���ü���call����
#define Base_F1_F10List Base_DropSkillArg	//����������ַ������һ�еķ��ü���call������ͬ
#define Base_F1_F10Arg 0x10cfcf8		//��������� [���������]+27c


//CALL
#define BaseCall_UserGoodsForIndex 0x00804670	//ʹ�ñ���ָ����Ԫ��
#define BaseCall_ActionUse 0x006E8460			//����Call
#define BaseCall_ActionUseEax 0x10cfcf8			//����CallEax (*(DWORD*))((*(DWORD*)(0x10cfcf) + 0x27c))
#define BaseCall_DropSkill 0x00814e50			//���ü���call
#define BaseCall_F1_F10Call 0x006ef590			//��ݼ�CALL

//OFFSET
#define Offset_ObjType		0x8			//��������ƫ��
#define Offset_SelectIndex 0x1a3c		//���ѡ�й���ƫ��
#define Offset_RoleCurrentX 0x1c40		//��ҵ�ǰ����Xƫ��
#define Offset_RoleCurrentY 0x1c48		//��ҵ�ǰ����Yƫ��
