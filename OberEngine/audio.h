/*

OberEngine Decompilation
Original Game: Purble Place

*/

#ifndef _AUDIO_H_
#define _AUDIO_H_

class Audio
{
public:
  bool Initialize();
  IDirectSound8* GetDS();
  void Cleanup();

  IDirectSound8* m_pDirectSound;
};

extern Audio* g_pAudio;

#endif // _AUDIO_H_
