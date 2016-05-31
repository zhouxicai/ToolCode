
#include <iostream>
#include <stdio.h>
using namespace std;
#if 0
enum ETYPE
{
	TP1 =1,
	TP2 =2,
	TP3 =4,
	TP4 =8,
};
int g_State=0;

void add_state(ETYPE type)
{
	g_State |= type;
}

void del_state(ETYPE type)
{
	g_State  &= ~type;
}

void del_all_state()
{
	g_State  &= ~TP1 &~TP2 &~TP3 &~TP4;
}

bool get_state(ETYPE type)
{
	int t = g_State & type;

	if(t)
		return true;
	else
		return false;
}


int main()
{
 	add_state(TP1);
 	cout<<g_State<<endl;
 	add_state(TP2);
 	cout<<g_State<<endl;
 	add_state(TP3);
 	cout<<g_State<<endl;
 	add_state(TP4);
 	cout<<g_State<<endl;
 
 	cout<<endl;

	if( get_state(TP1) )
		cout<<"TP1"<<endl;
	if( get_state(TP2) ) 
		cout<<"TP2"<<endl;
	if( get_state(TP3) )
		cout<<"TP3"<<endl;
	if( get_state(TP4) ) 
		cout<<"TP4"<<endl;
	//del_all_state();

	cout<<endl;

	del_state(TP1);
	if( get_state(TP1) )
		cout<<"1TP1"<<endl;
	if( get_state(TP2) ) 
		cout<<"1TP2"<<endl;
	if( get_state(TP3) )
		cout<<"1TP3"<<endl;
	if( get_state(TP4) ) 
		cout<<"1TP4"<<endl;

	cout<<endl;

	del_state(TP2);
	if( get_state(TP1) )
		cout<<"2TP1"<<endl;
	if( get_state(TP2) ) 
		cout<<"2TP2"<<endl;
	if( get_state(TP3) )
		cout<<"2TP3"<<endl;
	if( get_state(TP4) ) 
		cout<<"2TP4"<<endl;

	cout<<endl;

	del_state(TP3);
	if( get_state(TP1) )
		cout<<"3TP1"<<endl;
	if( get_state(TP2) ) 
		cout<<"3TP2"<<endl;
	if( get_state(TP3) )
		cout<<"3TP3"<<endl;
	if( get_state(TP4) ) 
		cout<<"3TP4"<<endl;

	cout<<endl;

	del_state(TP4); 
	if( get_state(TP1) )
		cout<<"4TP1"<<endl;
	if( get_state(TP2) ) 
		cout<<"4TP2"<<endl;
	if( get_state(TP3) )
		cout<<"4TP3"<<endl;
	if( get_state(TP4) ) 
		cout<<"4TP4"<<endl;

	system("pause");
	return 0;
}
#endif

/*
二、状态系统中的使用

在游戏开发中，我们通常用一个32位（假设这里用32位）的整数来存储角色的状态(这样做主要是为了节约存储空间，同时也减小网络同步消息包的size)。所谓的状态，就是大家熟悉的Buff或者DeBuff。
enum ROLE_STATUS
{
STATUS_NORMAL = 0, // 正常
STATUS_DIE = 1, // 死亡状态
STATUS_GOD , // 无敌
STATUS_DISAPPEARING , // 消失中状态
STATUS_DEF_ADJUST , // 物理防御提升/降低
STATUS_MDEF_ADJUST , // 魔法防御提升/降低
STATUS_ATK_CRI_ADJUST , // 同时提升物理攻击和爆击率
STATUS_MAXHP_ADJUST , // HP上限调整
STATUS_MAXMP_ADJUST , // MP上限提升/降低
//……
这里最多只能写32个，因为我们假设是用32位数据来存储状态。
};

状态数据定义好了，现在来看看怎么使用他们。
首先， 角色上线，我要给他一个保护状态，应该这样操作。
DWORD dwRoleStatus = STATUS_GOD;
同时，角色使用了一个物品，这个物品的效果时，HP和MP上限增加一段时间。因此要附加调整玩家的HP和MP上限的状态，应该这样。
DWORD dwRoleStatus |= (STATUS_MAXHP_ADJUST+STATUS_MAXMP_ADJUST);
这里是|=而不是=操作，因为不能清掉之前附加的无敌保护状态。所以用或运算。
该角色受到其他玩家或者怪物的攻击，我们要判断被攻击的这个角色的受保护状态状态还在不在。执行如下逻辑
if( dwRoleStatus & STATUS_GOD ) // 判断位是否为1
{
// 受保护状态，不能被攻击
}

接下来，角色无敌保护时间过期了，我们要清除无敌状态，执行如下操作
dwRoleStatus &= ~STATUS_GOD;
这里用到了取反的计算。~STATUS_GOD的结果是第二位为0外，其他都为1。然后和dwRoleStatus做按位与计算。
STATUS_GOD 等于 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010;
~STATUS_GOD 等于 1111 1111 1111 1111 1111 1111 1111 1111 1111 1101;
因此和dwRoleStatus相与之后，dwRoleStatus除了第二位以外的位，都保留下来了。第二位不管是什么值，都会被设置为0,这样子就把STATUS_GOD这个状态清除掉了。同理我们要清除多个状态的时候，先把要清楚的状态或运算到一起。再取反，然后和dwRoleStatus按位与。起到同时清除多个状态。
*/