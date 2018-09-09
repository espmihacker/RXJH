//基址管理单元

#define Base_GameWndHandle 0x0117F328	//游戏主窗口句柄'

#define Base_RolePropetry 0x02BD38B8	//人物对象基址'
#define Base_EquipList 0x2DF8498		//装备列表基址'
#define Base_BackpackList 0x02DF849C	//背包对象基址'
#define Base_DepotList 0x02E019EC		//仓库列表基址
#define Base_NearObjList 0x04236DD8		//怪物列表基址'
#define Base_ActionList	0x02DF8E18		//玩家动作数组'
#define Base_RoleObj 0x2E20A84			//玩家对象基址'
#define Base_AllListObj 0x02E20A88		//所有对象数组'
#define Base_SkillList 0x2DFA024		//技能列表基址'
#define	Base_SelectGoodAndSkill 0x011b08e8	//选中物品和技能'

#define Base_DropSkillArg 0x02DF9FC8		//放置技能call参数'
#define Base_F1_F10Arg 0x11B08F8			//快捷栏参数' +280
#define Base_PracticeSkillArg1 0x2BD3964	//修炼技能参数1'

//不用更新
#define Base_PracticeSkillArg2 Base_RoleObj	//修炼技能参数2，就是玩家角色基址
#define Base_F1_F10List Base_DropSkillArg	//快捷栏数组基址

//CALL
#define BaseCall_UserGoodsForIndex 0x00817fb0	//物品使用CALL'
#define BaseCall_ActionUse 0x006F7800  			//动作Call'
#define BaseCall_ActionUseEax 0x011B08F8		//动作CallEax' (*(DWORD*))((*(DWORD*)(0x10cfcf) + 0x27c))
#define BaseCall_DropSkill 0x008291B0			//放置技能call'
#define BaseCall_F1_F10Call 0x007068F0			//快捷键CALL'
#define BaseCall_PracticeSkill 0x00543760		//修炼技能CALL'
#define BaseCall_MoveGoods 0x008291B0			//移动物品CALL

//OFFSET
#define Offset_ObjType		0x8			//对象类型偏移
#define Offset_SelectIndex 0x1a4c		//玩家选中怪物偏移
#define Offset_RoleCurrentX 0x1c48		//玩家当前坐标X偏移 //1a50
#define Offset_RoleCurrentY 0x1c50		//玩家当前坐标Y偏移 //1a58
