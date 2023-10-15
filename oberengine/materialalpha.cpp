/*

OberEngine Decompilation

File name:
  materialalpha.cpp

*/

#include "stdafx.h"
#include "materialalpha.h"

#include "hresult.h"
#include "rendermanager.h"
#include "materialstructs.h"

#include <logger.h>

MaterialAlpha::MaterialAlpha()
{
  m_pVertexBuffer = NULL;
  m_pIndexBuffer = NULL;
  m_VertexSize = 1000;
}

MaterialAlpha::~MaterialAlpha()
{
  if (m_pVertexBuffer) {
    m_pVertexBuffer->Release();
    m_pVertexBuffer = NULL;
  }

  if (m_pIndexBuffer) {
    m_pIndexBuffer->Release();
    m_pIndexBuffer = NULL;
  }
}

bool MaterialAlpha::Initialize()
{
  return false;
}

void MaterialAlpha::PrepReset()
{
  if (m_pVertexBuffer) {
    m_pVertexBuffer->Release();
    m_pVertexBuffer = NULL;
  }
}

HRESULT MaterialAlpha::OnDeviceLost()
{
  HRESULT hr;

  hr = g_pRenderManager->m_Direct3D->CreateVertexBuffer(
    112 * m_VertexSize,
    D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
    MaterialBasicVertex::FVF,
    D3DPOOL_DEFAULT,
    &m_pVertexBuffer,
    nullptr
  );

  if (FAILED(hr)) {
    LPCWSTR s_hr = GetHResult(hr);
    LOG(2, L"Unable to recreate the vertex buffer: %x(%s)", hr, s_hr);
  }

  return hr;
}
