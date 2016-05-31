
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
����״̬ϵͳ�е�ʹ��

����Ϸ�����У�����ͨ����һ��32λ������������32λ�����������洢��ɫ��״̬(��������Ҫ��Ϊ�˽�Լ�洢�ռ䣬ͬʱҲ��С����ͬ����Ϣ����size)����ν��״̬�����Ǵ����Ϥ��Buff����DeBuff��
enum ROLE_STATUS
{
STATUS_NORMAL = 0, // ����
STATUS_DIE = 1, // ����״̬
STATUS_GOD , // �޵�
STATUS_DISAPPEARING , // ��ʧ��״̬
STATUS_DEF_ADJUST , // �����������/����
STATUS_MDEF_ADJUST , // ħ����������/����
STATUS_ATK_CRI_ADJUST , // ͬʱ�����������ͱ�����
STATUS_MAXHP_ADJUST , // HP���޵���
STATUS_MAXMP_ADJUST , // MP��������/����
//����
�������ֻ��д32������Ϊ���Ǽ�������32λ�������洢״̬��
};

״̬���ݶ�����ˣ�������������ôʹ�����ǡ�
���ȣ� ��ɫ���ߣ���Ҫ����һ������״̬��Ӧ������������
DWORD dwRoleStatus = STATUS_GOD;
ͬʱ����ɫʹ����һ����Ʒ�������Ʒ��Ч��ʱ��HP��MP��������һ��ʱ�䡣���Ҫ���ӵ�����ҵ�HP��MP���޵�״̬��Ӧ��������
DWORD dwRoleStatus |= (STATUS_MAXHP_ADJUST+STATUS_MAXMP_ADJUST);
������|=������=��������Ϊ�������֮ǰ���ӵ��޵б���״̬�������û����㡣
�ý�ɫ�ܵ�������һ��߹���Ĺ���������Ҫ�жϱ������������ɫ���ܱ���״̬״̬���ڲ��ڡ�ִ�������߼�
if( dwRoleStatus & STATUS_GOD ) // �ж�λ�Ƿ�Ϊ1
{
// �ܱ���״̬�����ܱ�����
}

����������ɫ�޵б���ʱ������ˣ�����Ҫ����޵�״̬��ִ�����²���
dwRoleStatus &= ~STATUS_GOD;
�����õ���ȡ���ļ��㡣~STATUS_GOD�Ľ���ǵڶ�λΪ0�⣬������Ϊ1��Ȼ���dwRoleStatus����λ����㡣
STATUS_GOD ���� 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010;
~STATUS_GOD ���� 1111 1111 1111 1111 1111 1111 1111 1111 1111 1101;
��˺�dwRoleStatus����֮��dwRoleStatus���˵ڶ�λ�����λ�������������ˡ��ڶ�λ������ʲôֵ�����ᱻ����Ϊ0,�����ӾͰ�STATUS_GOD���״̬������ˡ�ͬ������Ҫ������״̬��ʱ���Ȱ�Ҫ�����״̬�����㵽һ����ȡ����Ȼ���dwRoleStatus��λ�롣��ͬʱ������״̬��
*/