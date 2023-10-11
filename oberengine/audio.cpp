/*

OberEngine Decompilation

File name:
  audio.cpp

*/

#include "stdafx.h"
#include "audio.h"

#include "window.h"
#include "hresult.h"
#include <logger.h>

Audio::Audio()
{
  m_pDirectSound = NULL;
  m_Unknown = 0;
  m_EffectVolumePercentage = 100;
  m_UnknownVolumePercentage = 100;
  m_BufferVolumePercentage = 100;
  m_CooperativeLevel = DSSCL_PRIORITY;
}

Audio::~Audio()
{
  Cleanup();
}

bool Audio::Initialize()
{
  HRESULT hr;

  if (!LoadLibraryW(L"wmvcore.dll")) {
    LOG(0x1000, L"wmvcore.dll LoadLibrary failed, winerror %d", GetLastError());
    m_pDirectSound = NULL;
    return true;
  }

  hr = DirectSoundCreate8(NULL, &m_pDirectSound, NULL);
  if (FAILED(hr)) {
    LOG(0x1000, L"DirectSoundCreate8 Failed: %x (%s)", hr, GetHResult(hr));
    m_pDirectSound = NULL;
    return true;
  }

  hr = m_pDirectSound->SetCooperativeLevel(g_hWnd, m_CooperativeLevel);
  if (FAILED(hr)) {
    LOG(0x1000, L"SetCoopLevel Failed: %x (%s)", hr, GetHResult(hr));
    m_pDirectSound->Release();
    m_pDirectSound = NULL;
    return true;
  }

  return true;
}

IDirectSound8* Audio::GetDS()
{
  return m_pDirectSound;
}

void Audio::Cleanup()
{
  if (m_pDirectSound) {
    m_pDirectSound->Release();
    m_pDirectSound = NULL;
  }
}

void Audio::RegisterMusic(ResourceSound* sound)
{
  m_pAudioArray.Add(sound);
}

int Audio::GetEffectBufferVolume(unsigned int volume)
{
  double volumePercentage = (double)m_EffectVolumePercentage / 100.0 * ((double)m_BufferVolumePercentage / 100.0) * ((double)volume / 100.0);
  float logValue = -10000.0;

  if (volumePercentage > 0.001) {
    logValue = (float)(log(volumePercentage) * 300.0 / log(2));
  }

  return (int)logValue;
}
