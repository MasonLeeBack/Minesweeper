/*

OberEngine Decompilation

File name:
  gameaudio.h

*/

#ifndef _GAMEAUDIO_H_
#define _GAMEAUDIO_H_

namespace GameAudio {
  typedef struct {

  } SoundEffect;

  typedef struct {

  } MusicStream;

  bool ForceLoadResource(unsigned int resID, bool bResetTimer);
  void LoadGameAudio(class XmlNode* xmlFile, bool a2);

  bool Pin(unsigned int resID);
  void Unpin(unsigned int resID);

  bool PlaySoundProto(unsigned int resID, bool a2, unsigned int* a3);

  void StopAllSounds();
  void StopSound(unsigned int resID, unsigned int a2);

  void SetSoundVolume(unsigned int resID, int volume, unsigned int a3);
  void SetMusicVolume(unsigned int resID, int volume);
}

#endif // _GAMEAUDIO_H_
