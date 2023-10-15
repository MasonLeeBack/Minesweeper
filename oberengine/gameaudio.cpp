/*

OberEngine Decompilation

File name:
  gameaudio.cpp

*/

#include "stdafx.h"
#include "gameaudio.h"
#include "audio.h"
#include "engine.h"
#include "resourcemanager.h"

Array<GameAudio::SoundEffect*> aSoundEffects;
Array<GameAudio::MusicStream*> aMusicStreams;

bool GameAudio::ForceLoadResource(unsigned int resID, bool bResetTimer)
{
  if (!Pin(resID)) {
    return false;
  }

  Unpin(resID);

  if (bResetTimer)
    Engine_ResetTimer();

  return true;
}

bool GameAudio::Pin(unsigned int resID)
{
  unsigned int** effect;

  if (resID < aSoundEffects.count) {
    effect = (unsigned int**)aSoundEffects.data[resID];
    if (*effect)
      return g_pResourceManager->PinResource(**effect);
  }

  return false;
}

void GameAudio::Unpin(unsigned int resID)
{
  unsigned int** effect;

  if (resID < aSoundEffects.count) {
    effect = (unsigned int**)aSoundEffects.data[resID];
    if (*effect)
      g_pResourceManager->UnpinResource(**effect);
  }
}

bool GameAudio::PlaySoundProto(unsigned int resID, bool a2, unsigned int* a3)
{
  if (aSoundEffects.count > resID) {
    return g_pAudio->StartEffect(aSoundEffects.data[resID], a2, a3);
  }

  return false;
}

void GameAudio::StopAllSounds()
{
  for (unsigned int i = 0; i < aSoundEffects.count; ++i) {
    StopSound(i, 0);
  }
}

void GameAudio::StopSound(unsigned int resID, unsigned int a2)
{
  if (aSoundEffects.count > resID) {
    g_pAudio->StopSound(aSoundEffects.data[resID], a2);
  }
}

void GameAudio::SetSoundVolume(unsigned int resID, int volume, unsigned int a3)
{
  unsigned int effect; 

  if (aSoundEffects.count > resID) {
    effect = (unsigned int)aSoundEffects.data[resID];
    if (effect) {
      ResourceSound* soundResource = (ResourceSound*)g_pResourceManager->GetResource(effect, 1);
      if (!soundResource)
        SharedDialogs::FatalDialog::Show(0);

      soundResource->SetVolume(volume, a3);
    }
  }
}

void GameAudio::SetMusicVolume(unsigned int resID, int volume)
{
  unsigned int effect;
  
  if (aMusicStreams.count > resID) {
    effect = (unsigned int)aMusicStreams.data[resID];
    if (effect) {
      ResourceSound* soundResource = (ResourceSound*)g_pResourceManager->GetResource(effect, 1);
      if (soundResource) {
        soundResource->SetVolume(volume, 0);
      }
    }
  }
}
