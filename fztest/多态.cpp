#include <iostream>
//Effective c++ study;
class CBase
{
public://���������к�����(�ö���)����;
	virtual void Object()=0{std::cout<<"pure virtual function Can have function body!"<<std::endl;};//���麯����ֻ�̳нӿ�;
	virtual void ImpureVirtual(){std::cout<<"base class:ImpureVirtual!"<<std::endl;};	//�麯�����̳нӿں�һ��ȱʡʵ��;
	void BaseSomething(){std::cout<<"base class:BaseSomething!"<<std::endl;};			//���麯��,�̳нӿں�һ��ǿ��ʵ��;
	
	void UsePrivateVirtual(CBase & obj)
	{//����35���麯���ӿ�(NVI)�ַ�������37-����P183;
		//dosomething,��������������������ǰ����;
		obj.private_virtual();//����ÿͻ�ֱ�ӵ����麯������û���κκð취��������������;
		//dosomething�����Խ������������º���;
	}
private://ֻ���ڱ����е���;
	virtual void private_virtual(){std::cout<<"CBase:private_virtual!"<<std::endl;};//NVI�ַ�,������������¶�����;
protected://�������������е��ã��������������;

};

class CDerivedX :public CBase
{
public:
	virtual void Object(){std::cout<<"CDerivedX!"<<std::endl; CBase::Object();/*���Ե��ô��麯���Ķ���*/};
	void Something(){std::cout<<"CDerivedX:something!"<<std::endl;};
private:
	virtual void private_virtual(){std::cout<<"CDerivedX:private_virtual!"<<std::endl;};
protected:

};
void obj(CBase & obj)
{	//��̬�󶨣���̬���ö�Ӧ����;
	obj.Object();
}
#if 0
int main()
{	
	CDerivedX ca;
	//��̬���÷�;
	obj(ca);
	//�����Լ����к���;
	ca.Something();
	//���û������к���;
	ca.BaseSomething();
	//NVI�ַ������û���ķ��麯������ӵ��ñ����麯��;
	ca.UsePrivateVirtual(ca);
	system("pause");
}
#endif
/*
1.�����಻��ʵ����;
2.���麯��Ҳ�����к�����,�������ƻ�������̳�����;
3.�����Ա�����Ǹ����麯������ζ�����������������������в�ͬ����Ϊ;
4.���麯������������ǲ����ԣ�Ӧ�ñ����������������¶���;

5.�麯������������������ѡ���Ƿ���д;
6.���麯����ǿ��Ҫ�������������д;
7.���麯������ǿ�Ƽ̳е��������У����Ǳ�ͬ����������;
8.�����ظ�����̳ж������麯���Ĳ���,��Ϊ�����Ǿ�̬�󶨵ģ����麯���Ƕ�̬�󶨵ģ����Բ�ƥ��;
 */