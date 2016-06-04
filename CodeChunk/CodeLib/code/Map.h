enum ETerrain
{

};
const int MAX_X = 16;
const int MAX_Y = 16;
const int LAYER = 3;

class CMap
{
public:
	CMap();
	~CMap();

protected:

private:
	int m_iX;
	int m_iY;
	ETerrain m_eCollision;
};



class CMapMgr
{
public:
	CMapMgr();
	~CMapMgr();
protected:

private:
	 

	CMap m_Map[LAYER][MAX_X][MAX_Y];
};