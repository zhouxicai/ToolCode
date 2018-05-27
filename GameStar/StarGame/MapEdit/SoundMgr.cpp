#include "SoundMgr.h"
#include "Core_Global.h"
#include "Core_Sound.h"
CSoundMgr oSoundMgr;

// Sound device and channels
cSound          m_Sound;
cSoundChannel   m_SoundChannel;
cMusicChannel   m_MusicChannel;
cSoundData      m_SoundData;

bool CSoundMgr::PlaySounds(long Num)
{
	if(Num >=0 && Num < NUM_SOUNDS) {
		m_SoundData.Free();

		if(m_SoundData.LoadWAV(g_SoundFilenames[Num]) == TRUE)
			m_SoundChannel.Play(&m_SoundData);

		return true;
	}

	return false;
}

bool CSoundMgr::StopSounds()
{
	m_SoundChannel.Stop();
	m_SoundChannel.Free();

	return true;
}

bool CSoundMgr::PlayMusic(long Num)
{
	// Don't bother changing song if same already playing
	if(g_CurrentMusic == Num)
		return true;

	// Stop and free current song
	m_MusicChannel.Stop();
	m_MusicChannel.Free();

	// Fade music out, giving DirectMusic enough time to finish up last song (or else new song doesn't
	// play correctly.  The 700 is based on play volume of music, so adjust ahead.
	DWORD Timer = timeGetTime() + 700;
	while(timeGetTime() < Timer) {
		DWORD Level = (Timer - timeGetTime()) / 10;
		m_MusicChannel.SetVolume(Level);
	}

	// Load and play new song
	m_MusicChannel.Load(g_MusicFilenames[Num]);
	m_MusicChannel.Play(70,0);

	// Remember new song #
	g_CurrentMusic = Num;

	return true;
}

bool CSoundMgr::StopMusic()
{
	// Stop and free music, marking current song as none
	m_MusicChannel.Stop();
	m_MusicChannel.Free();
	g_CurrentMusic = -1;

	return true;
}

