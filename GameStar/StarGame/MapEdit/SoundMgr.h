
#ifndef _CSOUND_MGR_H
#define _CSOUND_MGR_H

class CSoundMgr
{
public:
	// Play a sound
	bool PlaySounds(long Num);
	bool StopSounds();
	// Play a music
	bool PlayMusic(long Num);
	bool StopMusic();
private:

};

extern CSoundMgr oSoundMgr;

#endif