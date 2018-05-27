
static const int MAX_SNOW_COUNT = 1000;
const int SNOW_SIZE= 6;
class CSnow
{
public:
	CSnow():x(0),y(0){};

	void SetPosition(int _x,int _y){ x=_x;y=_y;}
	//雪花当前坐标;
	int GetX(){ return x;};
	int GetY(){ return y;}
	void SetX(int x_){ x = x_;};
	void SetY(int y_){ y = y_;};
	void AddY(){ y++;};
	void AddX(){ x++;};
	void DelX(){ x--;};
	int GetSize(){ return size;}
	void SetSize(int size_){ size = size_;};
private:
	int x,y,size;
};

class CSnowMgr
{
public:
	CSnowMgr();
	CSnow mSnow[MAX_SNOW_COUNT];
	void Init();
	void Snowing(int count);
private:
};

extern CSnowMgr oSnowMgr;