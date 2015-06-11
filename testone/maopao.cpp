	int dwGuideInfo[10];
	int iTemp=0;
	for(int i=1;i<nMax;i++) 
	{
		for(int j=nMax-1;j>=i;j--)
		{
			if(dwGuideInfo[j] > dwGuideInfo[j-1])
			{
				iTemp = dwGuideInfo[j-1]; 
				dwGuideInfo[j-1] = dwGuideInfo[j];
				dwGuideInfo[j] = iTemp; 
			}
		}
	}