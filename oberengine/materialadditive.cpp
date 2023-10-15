/*

OberEngine Decompilation

File name:
  materialadditive.cpp

*/

#include "stdafx.h"
#include "materialadditive.h"

#include "hresult.h"
#include "rendermanager.h"
#include "materialstructs.h"

#include <logger.h>

MaterialAdditive::MaterialAdditive()
{
  m_pVertexBuffer = NULL;
  m_pIndexBuffer = NULL;
  m_VertexSize = 1000;
}

MaterialAdditive::~MaterialAdditive()
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

bool MaterialAdditive::Initialize()
{
  return false;
}

void MaterialAdditive::PrepReset()
{
  if (m_pVertexBuffer) {
    m_pVertexBuffer->Release();
    m_pVertexBuffer = NULL;
  }
}

HRESULT MaterialAdditive::OnDeviceLost()
{
  HRESULT hr;

  hr = g_pRenderManager->m_Direct3D->CreateVertexBuffer(
    112 * m_VertexSize,
    D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
    AddVertex::FVF,
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
