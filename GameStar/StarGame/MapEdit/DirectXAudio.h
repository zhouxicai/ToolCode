#ifndef DirectX_AUDIO_H
#define DirectX_AUDIO_H

//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "Winmm.lib") // error LNK2019: 无法解析的外部符号 LoadMicMidiWav
#pragma comment(lib,"dsound.lib") // error LNK2019: 无法解析的外部符号 _DirectSoundCreate8@12，该符号在函数 "public: int __thiscall cSound::Init
//#include <dmksctrl.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmusicf.h>
#include <dshow.h>


class CDirectXAudio
{
private:
	//MIDI专用
	IDirectMusicLoader8 * pLoader ;
	IDirectMusicPerformance8 * pPerf ;
	IDirectMusicSegment8 * pSeg ;
	//MP3专用
	IGraphBuilder * pGBuilder;
	IMediaControl * pMControl;
	IMediaPosition * pMPosition;
	//MIC专用
	MCI_OPEN_PARMS OpenParms;	
	//WAV专用
	bool mWavState;
	bool mBackPlay;
public:
	//播放MIDE,MAV格式文件
	CDirectXAudio();
	void InitializeAudio();
	void LoaderMIDI_WAV(char* midi_wav);
	void PlayAudio(DWORD play_number);
	void CloseAudio();
	void StopWav();

	//用MIC播放MIDE,MAV格式文件(文件名，类型MIDI=0 WAV=1)
	void LoadMicMidiWav(TCHAR*path_name,short midi_0_wav_1);
	void PlayMicMidiWav();
	void StopMicMidiWav();
	bool GetWavState(){ return mWavState;}
	void SetWavState(bool is_player){ mWavState = is_player;}
	

public://播放MP3格式文件
	void InitializeMP3();
	void PlayMP3();
	void CloseMP3();
};
extern CDirectXAudio oDirectXAudio;

#endif