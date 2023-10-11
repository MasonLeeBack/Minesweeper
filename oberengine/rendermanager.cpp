/*

OberEngine Decompilation

File name:
  rendermanager.cpp

*/

#include "stdafx.h"
#include "rendermanager.h"
#include "textrenderer.h"
#include "userinterface.h"
#include "engine.h"

#include "xmlmanager.h"
#include <logger.h>

Material* RenderManager::GetMaterial(int index)
{
  int aIndex = index;

  if (index == 0)
    aIndex = 1;

  return m_Materials[aIndex];
}

int RenderManager::CreateCachedBackBuffer()
{
  return 0;
}

HMONITOR RenderManager::GetAdapterMonitor()
{
  return m_Monitor;
}

void RenderManager::GetMaxTextureSize(int* width, int* height)
{
  *width = m_MaxTextureWidth;
  *height = m_MaxTextureHeight;
}

bool RenderManager::Is16Bit()
{
  return m_InitializeOptions->m_RenderDepth == 16;
}

BOOL RenderManager::IsRGBRast()
{
  D3DCAPS9 caps;
  m_Direct3D->GetDeviceCaps(&caps);

  return caps.DeviceType == D3DDEVTYPE_SW;
}

void RenderManager::MarkDeviceForRecreate()
{
  LOG(2, L"Forcing a device recreate on next render");
  m_bForceRecreate = true;
}

void RenderManager::MarkSceneDirty()
{
  m_bSceneDirty = true;
  m_bRenderScene = true;
}

void RenderManager::ReleaseDefaultResources()
{
  g_pTextRenderer->PrepReset();

  if (m_MaterialAlpha1) {
    m_MaterialAlpha1->PrepReset();
  }

  if (m_MaterialAlpha2) {
    m_MaterialAlpha2->PrepReset();
  }

  if (m_MateralAdditive) {
    m_MateralAdditive->PrepReset();
  }

  if (m_RenderTarget) {
    m_RenderTarget->Release();
    m_RenderTarget = 0;
  }

  if (m_RenderTarget2) {
    m_RenderTarget2->Release();
    m_RenderTarget2 = 0;
  }

  if (m_CachedBackBuffer) {
    m_CachedBackBuffer->Release();
    m_CachedBackBuffer = 0;
  }
}

void RenderManager::ReleaseAllResources()
{
  ReleaseDefaultResources();
  g_pResourceManager->ReleaseDeviceDependentResources();

  if (m_MaterialAlpha1) {
    delete m_MaterialAlpha1;
  }

  if (m_MaterialAlpha2) {
    delete m_MaterialAlpha2;
  }

  if (m_MateralAdditive) {
    delete m_MateralAdditive;
  }

  if (m_OffscreenTarget) {
    m_OffscreenTarget->Release();
    m_OffscreenTarget = 0;
  }

  if (m_Direct3D) {
    m_Direct3D->Release();
    m_Direct3D = 0;
  }
}

void RenderManager::SetBack(const wchar_t* xmlFileName)
{
  XmlNode* xmlFile;

  if (m_BackgroundSprite)
    m_BackgroundSprite->DeleteSelf();

  if (xmlFile) {
    m_BackgroundSprite = NodeBase::Create(xmlFileName, 0);

    if (m_BackgroundSprite) {
      m_BackgroundSprite->SetVisible(false);
      m_BackgroundSprite->field_44 = 0;

      xmlFile = g_pXmlManager->GetXml(xmlFileName);

      if (xmlFile) {

      }

    }
    else {
      LOG(2, L"Couldn't create the background sprite");
    }

  }
  else {
    m_BackgroundSprite = NULL;
  }
}

void RenderManager::SetBackground(bool bClearCustom, unsigned int color)
{
  m_bClearCustom = bClearCustom;
  m_BackgroundColor = color;
}

void RenderManager::SetEngineState(EngineState state)
{
  LOG(2, L"SetState: %d", state);
  m_EngineState = state;
  m_bSceneDirty = true;
  m_bRenderScene = true;
}

void RenderManager::SwitchToCurrentMonitor()
{
  SetEngineState(SWITCHTOCURRENTMONITOR);
}

void RenderManager::Update(float fDeltaTime)
{
  m_BaseNode->Update(fDeltaTime);
}

bool RenderManager::RecreateDefaultResources()
{
  return false;
}

void RenderManager::RegisterTopLevelNode(NodeBase* node)
{
  m_Nodes.Add(node);
  m_bClearCustom = true;
}

bool RenderManager::SetResolution(unsigned int width, unsigned int height)
{
  // This has MEMORY[0x8C] == g_pRenderManager, not sure why
  // 0x8C may mean the engine state?
  if (!g_pRenderManager)
    return true;

  if (m_bHighDPI) {
    // These *were* assigned as doubles but that's not right
    m_RenderScaleX = 1.0f;
    m_RenderScaleY = 1.0f;
  }
  else {

  }

  m_BaseNode->SetSize(width, height);

  ReleaseDefaultResources();

  if (!Reset()) {
    LOG(2, L"Failed to set the backbuffer res.");
    return false;
  }

  if (!RecreateDefaultResources()) {
    LOG(2, L"SetResolution() -- failure in RecreateDefaultResources()");
    return false;
  }

  // Mark scene as dirty
  m_bSceneDirty = true;
  m_bRenderScene = true;

  return true;
}

bool RenderManager::FlushDefaultTextures()
{
  LOG(2u, L"FlushDefaultTextures()");
  ReleaseDefaultResources();
  return RecreateDefaultResources();
}

bool RenderManager::Reset()
{
  return false;
}

void RenderManager::SaveBackBuffer()
{
  IDirect3DSurface9* surface;
  IDirect3DSurface9* renderTarget;


  if (m_bSceneDirty && m_CachedBackBuffer) {
    LOG(2, L"Saved the back buffer for cached presentation");
    m_bSceneDirty = true;
    m_bRenderScene = true;

    m_Direct3D->GetRenderTarget(0, &renderTarget);
    m_CachedBackBuffer->GetSurfaceLevel(0, &surface);
    m_Direct3D->SetRenderTarget(0, surface);

    Render(false);

    m_Direct3D->SetRenderTarget(0, renderTarget);

    renderTarget->Release();
    surface->Release();

    if (field_0) {
      LOG(2, L"DeviceLost in SaveBackBuffer");
    }
    else {
      m_bSceneDirty = 0;
    }
  }
}

void RenderManager::UnregisterTopLevelNode(NodeBase* node)
{
  m_Nodes.FindRemove(node);
}

bool RenderManager::Initialize(const RenderInitializeOptions* options)
{
  RenderInitializeOptions* op = new RenderInitializeOptions{};
  m_InitializeOptions = op;
  memcpy(op, options, sizeof(RenderInitializeOptions));

  LOG(2u, L"Initializing the text renderer");

  TextRenderer* tr = new TextRenderer();
  g_pTextRenderer = tr;

  if (!RecreateAllResources(0) && m_EngineState != OUTOFVIDEOMEMORY) {
    LOG(2u, L"RecreateAllResources() failed");
    return false;
  }

  if (!g_pTextRenderer->Initialize()) {
    LOG(2u, L"Couldn't create Text Renderer");
    return false;
  }

  m_BaseNode = NodeBase::CreateFromType(L"Base", 0, 1);

  LOG(2u, L"Initializing the user interface.");

  UserInterface* ui = new UserInterface();
  g_pUserInterface = ui;

  ui->SetLayoutResolution(
    m_InitializeOptions->m_RenderWidth / (g_bDoubleDPI + 1),
    m_InitializeOptions->m_RenderHeight / (g_bDoubleDPI + 1));

  ui->SetLayoutOffsetRect(
    0,
    0,
    m_InitializeOptions->m_RenderWidth / (g_bDoubleDPI + 1),
    m_InitializeOptions->m_RenderHeight / (g_bDoubleDPI + 1));

  m_BaseNode->SetAccessible(true, 0x3Bu);

  m_BaseNode->SetSize(
    m_InitializeOptions->m_RenderWidth / (g_bDoubleDPI + 1),
    m_InitializeOptions->m_RenderHeight / (g_bDoubleDPI + 1));

  m_Direct3D->Clear(0, 0, 1, 0, 1.0, 0);

  XmlNode* xmlFile = g_pXmlManager->GetXml(L"engine.xml");
  if (xmlFile) {
    g_bLogFillRate = xmlFile->GetXmlInt(L"/LogFillRate", -1) > 0;
    m_bForceFilter = xmlFile->GetXmlInt(L"/ForceFilter", -1) > 0;
  }

  int* engineState = &m_EngineState;
  if (!*engineState)
    *engineState = UNK_4096;

  SetDPIFromWindowSize();

  return true;
}

void RenderManager::CreateCorrectMaterials()
{
  m_MaterialAlpha1 = new MaterialAlpha();
  m_MaterialAlpha2 = new MaterialAlpha();
  CheckAllocation(m_MaterialAlpha2);
  m_MateralAdditive = new MaterialAdditive();
  CheckAllocation(m_MateralAdditive);
}

void RenderManager::SetDeviceLost()
{
  SetEngineState(DEVICELOST);
  m_bDeviceLost = true;
}

void RenderManager::SetOutOfVideoMemory()
{
  SetEngineState(OUTOFVIDEOMEMORY);
  m_bDeviceLost = true;
}
