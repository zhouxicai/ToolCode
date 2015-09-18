

const int ALIVE = 10;
const int DEAD = 110;

//struct Grid
//{
//	int one ;
//	int two ;
//};
//Grid gd[]=
//{
//	{1,2},
//	{1,3},
//}
//int Grid [11][5]; 
int curr[12][12];
int next[12][12];


//ʾ��2-3��������Ϸ���������ݵ�ǰ����״̬������һ����״̬;
void ComputeNextGen (/* Grid curr, Grid next ,*/ int N, int M )
{
	int count ;
	for   ( int   i   =   1 ;   i   <=   N ;   i ++ )   
	{
		for   ( int   j   =   1 ;   j   <=   M ;   j ++ )   
		{
			count = 0;
			if( curr [ i - 1 ][ j - 1 ] == ALIVE ) count ++ ;	// ���������ڽ�Ԫ��;
			if( curr [ i - 1 ][ j ]		== ALIVE ) count ++ ;   // ���������ڽ�Ԫ��;
			if( curr [ i - 1 ][ j + 1 ] == ALIVE ) count ++ ;   // ���������ڽ�Ԫ��;
			if( curr [ i ]	  [ j - 1 ]	== ALIVE ) count ++ ;   // ���������ڽ�Ԫ��;
			if( curr [ i ]	  [ j + 1 ]	== ALIVE ) count ++ ;   // ���������ڽ�Ԫ��;
			if( curr [ i + 1 ][ j - 1 ] == ALIVE ) count ++ ;   // ���Ϸ����ڽ�Ԫ��;
			if( curr [ i + 1 ][ j ]	    == ALIVE ) count ++ ;   // ���Ϸ����ڽ�Ԫ��;
			if( curr [ i + 1 ][ j + 1 ] == ALIVE ) count ++ ;   // ���Ϸ����ڽ�Ԫ��;
				
				 if( count <= 1 || count >= 4 )next [ i ] [ j ]   =   DEAD ;
			else if( curr[ i ] [ j ] == ALIVE && ( count == 2 || count == 3 ) )next [ i ] [ j ]   =   ALIVE ;
			else if( curr[ i ] [ j ] == DEAD  && count == 3 )next [ i ] [ j ]   =   ALIVE ;
			else next [ i ] [ j ]   =   DEAD ;
		}
	}
	return ;
}

/*
��ʾ��2 - 3 �и������ڴӵ�ǰ����������һ��ʱ��ÿ��Ԫ��״̬���и��µĴ��롣����;
G r i d ��һ����ά���飬���Ա����û��Զ���ĳ���ֵA L I V E ��D E A D ����������������;
��ȡֵ��ΧΪ0 ��N + 1 ����������ȡֵ��ΧΪ0 ��M + 1 ��������к����е�Ԫ���ڸ��²�;
���н��������룬���Ǳ���Ϊ��Ԫ�������ı߽磬�������а������л��嶼��������;
�����Խ�������Ϊһ�����������ǽ��ֻҪ����ͻ���������ͨ��������Щ�߽�Ԫ����;
�Ͳ���Ҫ�Ը����߽������⴦����ͳ����ĳ��Ԫ�����ڽ�Ԫ��״̬�󣬾Ϳ��Ը�����;
������Ĺ�����ȷ����Ԫ������һ���е�״̬��������ǰ���ʾ��2 - 2 ��û�и��������;
���̰߳汾һ���������߿������и��ݺ��������������ʵ�ֶ��̰߳汾�Ĵ��롣;
*/