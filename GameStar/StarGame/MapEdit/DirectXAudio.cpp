#include <windows.h>
#include "DirectXAudio.h"

CDirectXAudio oDirectXAudio;
CDirectXAudio::CDirectXAudio():mWavState(false),mBackPlay(false)
{
	IDirectMusicLoader8 * pLoader = NULL;
	IDirectMusicPerformance8 * pPerf = NULL;
	IDirectMusicSegment8 * pSeg = NULL;
	InitializeAudio();
	LoaderMIDI_WAV("audios\\rain03.wav");
};
void CDirectXAudio::InitializeAudio()
{
	CoInitialize(NULL);
	CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,IID_IDirectMusicLoader8,(void**)&pLoader);
	CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,IID_IDirectMusicPerformance8,(void**)&pPerf);
	CoCreateInstance(CLSID_DirectMusicSegment,NULL,CLSCTX_INPROC,IID_IDirectMusicSegment8,(void**)&pSeg);
	pPerf->InitAudio(NULL,NULL,GetForegroundWindow(),DMUS_APATH_SHARED_STEREOPLUSREVERB,64,DMUS_AUDIOF_ALL,NULL);
}
void CDirectXAudio::LoaderMIDI_WAV(char* midi_wav)
{ 
	CHAR strSoundPath[MAX_PATH];//�����ļ�·��
	GetCurrentDirectoryA(MAX_PATH,strSoundPath);//�õ���������·��
	strcat_s(strSoundPath,"\audios");//����·���µ���Ŀ¼
	
	WCHAR wstrSoundPath[MAX_PATH];//�洢UNICODE��ʽ��·����ת���ɿ��ַ�;
	MultiByteToWideChar(CP_ACP,0,strSoundPath,-1,wstrSoundPath,MAX_PATH);//ת��
	pLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,wstrSoundPath,FALSE);

	WCHAR wstrFileName[MAX_PATH]=L"tore2";//�洢UNICODE��ʽ���ļ���
	MultiByteToWideChar(CP_ACP,0,midi_wav,-1,wstrFileName,MAX_PATH);//Ҫ���ŵ��ļ�
	pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,IID_IDirectMusicSegment8,wstrFileName,(LPVOID*)&pSeg);
	
	//DMUS_OBJECTDESC dmod;
	//// Get the object
	//ZeroMemory(&dmod, sizeof(DMUS_OBJECTDESC));
	//dmod.dwSize = sizeof(DMUS_OBJECTDESC);
	//dmod.guidClass = CLSID_DirectMusicSegment;
	//dmod.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME | DMUS_OBJ_FULLPATH;
	//mbstowcs(dmod.wszFileName, midi_wav, MAX_PATH);
	//pLoader->GetObject(&dmod, IID_IDirectMusicSegment8, (LPVOID*)&pSeg);
	//if(strstr(midi_wav, ".mid") != NULL) {
	//	pSeg->SetParam(GUID_StandardMIDIFile, 0xFFFFFFFF, 0, 0, NULL);
	//}
	//
}
void CDirectXAudio::PlayAudio(DWORD play_number)
{
	pSeg->Download(pPerf);//copy data to pPerf
	pSeg->SetRepeats(play_number);//��������Ҫ���ŵĴ���DMUS_SEG_REPEAT_INFINITE���޴�
	pPerf->PlaySegmentEx(pSeg,NULL,NULL,0,0,NULL,NULL,NULL);
}
void CDirectXAudio::CloseAudio()
{
//	pPerf->CloseDown();
	if (!pSeg || !pPerf)
	{
		return;
	}
	pSeg->Unload(pPerf);
	pLoader->ReleaseObjectByUnknown(pSeg);
	pSeg->Release();
	pPerf->Release();
	CoUninitialize();//ֹͣʹ��COM
}
void CDirectXAudio::StopWav()
{
	pPerf->Stop(pSeg,NULL,NULL,NULL);
}

#if 1
//��MIC����MIDE,MAV��ʽ�ļ�
void CDirectXAudio::LoadMicMidiWav(TCHAR*path_name,short midi_0_wav_1)
{	
	//mid-MCI_DEVTYPE_SEQUENCER //wav-MCI_DEVTYPE_WAVEFORM_AUDIO
	if(midi_0_wav_1==0) OpenParms.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_SEQUENCER;
	else if(midi_0_wav_1==1) OpenParms.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
	OpenParms.lpstrElementName = path_name;

	OpenParms.wDeviceID = 0;
	mciSendCommand( NULL, MCI_OPEN,  MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID 
				    | MCI_OPEN_ELEMENT, (DWORD)(LPVOID) &OpenParms );
}

void CDirectXAudio::PlayMicMidiWav()
{
	if (mBackPlay)
		return;
	mBackPlay = true;
	MCI_PLAY_PARMS PlayParms;
	PlayParms.dwFrom = 0;
	mciSendCommand (OpenParms.wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID)&PlayParms);
}
void CDirectXAudio::StopMicMidiWav()
{
	mciSendCommandW(OpenParms.wDeviceID,MCI_STOP,NULL,NULL);
	mBackPlay = false;
}
#endif

//MP3 moudle
void CDirectXAudio::InitializeMP3()
{
	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC,IID_IGraphBuilder,(void**)&pGBuilder);
	pGBuilder->QueryInterface(IID_IMediaControl,(void**)&pMControl);
	pGBuilder->QueryInterface(IID_IMediaPosition,(void**)&pMPosition);
	char strSoundPath[MAX_PATH];
	TCHAR wstrSoundPath[MAX_PATH]=L"summer.mp3";
	GetCurrentDirectoryW(MAX_PATH,(LPWSTR)strSoundPath);
	strcat_s(strSoundPath,"/audios/" );
	MultiByteToWideChar(CP_ACP,0,strSoundPath,-1,wstrSoundPath,MAX_PATH);//ת��
	pGBuilder->RenderFile(wstrSoundPath,NULL);
	
}
void CDirectXAudio::PlayMP3()
{	
	pMPosition->put_CurrentPosition(0);
	pMControl->Run();
}
void CDirectXAudio::CloseMP3()
{
	pMControl->Stop();
	CoUninitialize();//ֹͣʹ��COM
}