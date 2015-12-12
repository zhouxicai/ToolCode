

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


//示例2-3：生命游戏函数，根据当前代的状态计算下一代的状态;
void ComputeNextGen (/* Grid curr, Grid next ,*/ int N, int M )
{
	int count ;
	for   ( int   i   =   1 ;   i   <=   N ;   i ++ )   
	{
		for   ( int   j   =   1 ;   j   <=   M ;   j ++ )   
		{
			count = 0;
			if( curr [ i - 1 ][ j - 1 ] == ALIVE ) count ++ ;	// 西北方向邻接元胞;
			if( curr [ i - 1 ][ j ]		== ALIVE ) count ++ ;   // 正北方向邻接元胞;
			if( curr [ i - 1 ][ j + 1 ] == ALIVE ) count ++ ;   // 东北方向邻接元胞;
			if( curr [ i ]	  [ j - 1 ]	== ALIVE ) count ++ ;   // 正西方向邻接元胞;
			if( curr [ i ]	  [ j + 1 ]	== ALIVE ) count ++ ;   // 正东方向邻接元胞;
			if( curr [ i + 1 ][ j - 1 ] == ALIVE ) count ++ ;   // 西南方向邻接元胞;
			if( curr [ i + 1 ][ j ]	    == ALIVE ) count ++ ;   // 正南方向邻接元胞;
			if( curr [ i + 1 ][ j + 1 ] == ALIVE ) count ++ ;   // 东南方向邻接元胞;
				
				 if( count <= 1 || count >= 4 )next [ i ] [ j ]   =   DEAD ;
			else if( curr[ i ] [ j ] == ALIVE && ( count == 2 || count == 3 ) )next [ i ] [ j ]   =   ALIVE ;
			else if( curr[ i ] [ j ] == DEAD  && count == 3 )next [ i ] [ j ]   =   ALIVE ;
			else next [ i ] [ j ]   =   DEAD ;
		}
	}
	return ;
}

/*
在示例2 - 3 中给出了在从当前代进化到下一代时对每个元胞状态进行更新的代码。假设;
G r i d 是一个二维数组，可以保存用户自定义的常量值A L I V E 和D E A D 。格网数组行索引;
的取值范围为0 ～N + 1 ，列索引的取值范围为0 ～M + 1 。多出的行和列中的元胞在更新操;
作中将不被计入，它们被认为是元胞格网的边界，在它们中包含的有机体都是死亡的;
（可以将它比作为一面充满毒气的墙，只要吸入就会死亡）。通过增加这些边界元胞，;
就不需要对格网边界做特殊处理。在统计了某个元胞的邻接元胞状态后，就可以根据上;
面给定的规则来确定该元胞在下一代中的状态。与我在前面的示例2 - 2 中没有给出代码的;
多线程版本一样，但读者可以自行根据后面的讨论来尝试实现多线程版本的代码。;
*/