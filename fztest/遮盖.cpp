
//����33;
class CBaseA
{
public:
	void set(double x){};
	void set(int x){};
};

class CDerived :public CBaseA
{
public:
	using CBaseA::set;//�ƹ�ͬ�����麯�����ڸ�;
	void set(int x)//��������������������������ͬ���������������н����ɼ������ڸǣ����������麯��;
	{CBaseA::set(x);};//ת���������ƹ��ڸ�;
};

void used()
{
	
	CDerived de;
	de.set(2);
	de.set(3.3);
}
//int main()
//{
//
//}
//����������ƻ��ڸǻ����е�ͬ������;
/*

*/