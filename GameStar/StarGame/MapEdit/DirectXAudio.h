#ifndef DirectX_AUDIO_H
#define DirectX_AUDIO_H

//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "Winmm.lib") // error LNK2019: �޷��������ⲿ���� LoadMicMidiWav
#pragma comment(lib,"dsound.lib") // error LNK2019: �޷��������ⲿ���� _DirectSoundCreate8@12���÷����ں��� "public: int __thiscall cSound::Init
//#include <dmksctrl.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmusicf.h>
#include <dshow.h>


class CDirectXAudio
{
private:
	//MIDIר��
	IDirectMusicLoader8 * pLoader ;
	IDirectMusicPerformance8 * pPerf ;
	IDirectMusicSegment8 * pSeg ;
	//MP3ר��
	IGraphBuilder * pGBuilder;
	IMediaControl * pMControl;
	IMediaPosition * pMPosition;
	//MICר��
	MCI_OPEN_PARMS OpenParms;	
	//WAVר��
	bool mWavState;
	bool mBackPlay;
public:
	//����MIDE,MAV��ʽ�ļ�
	CDirectXAudio();
	void InitializeAudio();
	void LoaderMIDI_WAV(char* midi_wav);
	void PlayAudio(DWORD play_number);
	void CloseAudio();
	void StopWav();

	//��MIC����MIDE,MAV��ʽ�ļ�(�ļ���������MIDI=0 WAV=1)
	void LoadMicMidiWav(TCHAR*path_name,short midi_0_wav_1);
	void PlayMicMidiWav();
	void StopMicMidiWav();
	bool GetWavState(){ return mWavState;}
	void SetWavState(bool is_player){ mWavState = is_player;}
	

public://����MP3��ʽ�ļ�
	void InitializeMP3();
	void PlayMP3();
	void CloseMP3();
};
extern CDirectXAudio oDirectXAudio;

#endif