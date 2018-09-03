//基址管理单元

#define Base_GameWndHandle 0x0109E728	//游戏主窗口句柄

#define Base_RolePropetry 0x02AF2C78	//人物对象基址
#define Base_BackpackList 0x02D1762C	//背包对象基址
#define Base_NearObjList 0x041538E8		//怪物列表对象
#define Base_ActionList	0x02d17be0		////dc [[02d17be0]+410+4*0]+5c
#define Base_RoleObj 0x2D3D594			//玩家对象基址《自己》
#define Base_AllListObj 0x02D3D598		//所有对象数组基址
#define Base_SkillList 0x2D18DEC		//技能列表基址
#define	Base_SelectGoodAndSkill 0x10cfce8	//选中物品和技能
#define Base_DropSkillArg 0x02D18D90		//放置技能call参数
#define Base_F1_F10Arg 0x10cfcf8			//快捷栏参数 [快捷栏参数]+27c
#define Base_PracticeSkillArg1 0x2AF2D24	//修炼技能参数1
#define Base_PracticeSkillArg2 Base_RoleObj	//修炼技能参数2，就是玩家角色基址
#define Base_F1_F10List Base_DropSkillArg	//快捷栏数组基址，和上一行的放置技能call参数相同

//CALL
#define BaseCall_UserGoodsForIndex 0x00804670	//使用背包指定单元格
#define BaseCall_ActionUse 0x006E8460			//动作Call
#define BaseCall_ActionUseEax 0x10cfcf8			//动作CallEax (*(DWORD*))((*(DWORD*)(0x10cfcf) + 0x27c))
#define BaseCall_DropSkill 0x00814e50			//放置技能call
#define BaseCall_F1_F10Call 0x006ef590			//快捷键CALL
#define BaseCall_PracticeSkill 0x0053CB00		//修炼技能CALL

//OFFSET
#define Offset_ObjType		0x8			//对象类型偏移
#define Offset_SelectIndex 0x1a3c		//玩家选中怪物偏移
#define Offset_RoleCurrentX 0x1c40		//玩家当前坐标X偏移
#define Offset_RoleCurrentY 0x1c48		//玩家当前坐标Y偏移
