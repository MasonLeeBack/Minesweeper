/*

OberEngine Decompilation

File name:
  audio.h

*/

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <array.h>
#include "resourcesound.h"

// size: 0x28 (40)
class Audio
{
public:
  Audio();
  ~Audio();

  bool Initialize();
  IDirectSound8* GetDS();
  void Cleanup();

  void RegisterMusic(ResourceSound* sound);
  int GetEffectBufferVolume(unsigned int volume);

  int m_UnknownVolumePercentage; // 0x0
  int m_BufferVolumePercentage; // 0x4
  int m_EffectVolumePercentage; // 0x8
  IDirectSound8* m_pDirectSound; // 0xC
  DWORD m_CooperativeLevel; // 0x10
  int m_Unknown; // 0x14
  Array<ResourceSound*> m_pAudioArray; // 0x18
};

extern Audio* g_pAudio;

#endif // _AUDIO_H_
