/*

OberEngine Decompilation
Original Game: Purble Place

*/

#include "rendermanager.h"

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
    // These *were* doubles but that's not right
    m_RenderScaleX = 1.0f;
    m_RenderScaleY = 1.0f;
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
  RenderInitializeOptions* op = new RenderInitializeOptions;
  if (op)
  {

  }
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
