/*

OberEngine Decompilation

File name:
  rendermanager.h

*/

#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_

#include "material.h"
#include "nodesprite.h"

enum MaterialType {
  UNKNOWN_MATERIAL,
  MATERIAL_ALPHA1,
  MATERIAL_ALPHA2,
  MATERIAL_ADDITIVE
};

struct RenderInitializeOptions {
  HWND m_hWnd = NULL;
  int m_RenderWidth = 0;
  int m_RenderHeight = 0;
  int m_RenderDepth = 0;
  int m_Windowed = 0;
};

class RenderManager
{
  enum EngineState {
    OUTOFVIDEOMEMORY = 257,
    SWITCHTOCURRENTMONITOR = 258,
    DEVICELOST = 260,
    INTERNALDRIVERERROR = 272,
    DEVICEREMOVED = 320,
    UNK_4096 = 4096, // Initialized?
  };

public:
  bool field_0; // 0x0
  D3DFORMAT m_Format; // 0x4
  unsigned int m_BackgroundColor; // 0x8
  unsigned int m_MaxTextureWidth; // 0xC
  unsigned int m_MaxTextureHeight; // 0x10
  bool m_bSceneDirty; // 0x14
  IDirect3DTexture9* m_CachedBackBuffer; // 0x18
  int m_BackBufferWidth; // 0x1C
  int m_BackBufferHeight; // 0x20
  bool m_bClearCustom; // 0x24
  HMONITOR m_Monitor; // 0x28
  Material** m_Materials; // 0x2C
  RenderInitializeOptions* m_InitializeOptions; // 0x30
  D3DFORMAT m_BackBufferFormat; // 0x34
  bool field_38; // 0x38
  IDirect3DDevice9* m_Direct3D; // 0x3C
  bool m_bRenderScene; // 0x40
  Material* m_MaterialAlpha1; // 0x44
  Material* m_MaterialAlpha2; // 0x48
  Material* m_MateralAdditive; // 0x4C
  NodeBase* m_BaseNode; // 0x50
  Array<NodeBase*> m_Nodes; // 0x54
  NodeSprite* m_BackgroundSprite; // 0x64
  int m_Anchor; // 0x68
  bool field_6C; // 0x6C
  bool m_bHighDPI; // 0x6D
  bool m_bForceFilter; // 0x6E
  bool m_bForceRecreate; // 0x6F
  float m_RenderScaleX; // 0x70
  float m_RenderScaleY; // 0x74
  int field_78; // 0x78
  IDirect3DSurface9* m_RenderTarget; // 0x7C
  IDirect3DSurface9* m_RenderTarget2; // 0x80
  IDirect3DSurface9* m_OffscreenTarget; // 0x84
  bool field_88; // 0x88
  bool m_bDeviceLost; // 0x89;
  bool field_8A; // 0x8A
  bool field_8B; // 0x8B
  int m_EngineState; // 0x8C

  Material* GetMaterial(int index);
  MaterialType MaterialClassFromPtr(Material* material);
  int CreateCachedBackBuffer();
  HMONITOR GetAdapterMonitor();
  void GetMaxTextureSize(int* width, int* height);
  bool Is16Bit();
  BOOL IsRGBRast(); // check to see if this is actually a 4-bit BOOL
  void MarkDeviceForRecreate();
  void MarkSceneDirty();

  void ReleaseDefaultResources();
  void ReleaseAllResources();

  void SetBack(const wchar_t* xmlFile);
  void SetBackground(bool bClearCustom, unsigned int color);
  void SetEngineState(EngineState state);
  void SwitchToCurrentMonitor();
  void Update(float fDeltaTime);

  bool RecreateDefaultResources();
  void RegisterTopLevelNode(NodeBase* node);

  bool SetResolution(unsigned int width, unsigned int height);
  bool FlushDefaultTextures();
  bool Reset();
  void SaveBackBuffer();
  void UnregisterTopLevelNode(NodeBase* node);
  bool Initialize(const RenderInitializeOptions* options);

  void CreateCorrectMaterials();

  void SetDeviceLost();
  void SetOutOfVideoMemory();
};

extern RenderManager* g_pRenderManager;

#endif // _RENDERMANAGER_H_
