#pragma once

#define DIRECTINP

#define	DIRECTINPUT_VERSION	0x0800

#define NOMINMAX

#include <Windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
#include <cmath>
#include <functional>
#include <algorithm>
#include <stack>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include <filesystem>
#include <dwrite_3.h>
#include <d2d1.h>
#include <process.h>
#include <memory.h>
#include <thread>
#include <mutex>
#include <wrl.h>
#include <fstream>

#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

#include "EngineMath.h"

#include "SharedPointer.h"
#include "Cast.h"
#include "Resource/Renderer/DirectXTex.h"

#ifdef _DEBUG

#pragma comment(lib, "DirectXTex_Debug.lib")

#else

#pragma comment(lib, "DirectXTex.lib")

#endif // _DEBUG

using namespace Microsoft::WRL;

#define	ROOT_PATH "Root"
#define	SHADER_PATH "Shader"
#define	TEXTURE_PATH "Texture"
#define	SOUND_PATH "Sound"
#define	FONT_PATH "Font"
#define	ANIMATION2D_PATH "Animation2D"
#define	SCENE_PATH "Scene"

#define	DECLARE_SINGLE(Type) \
private:\
	static Type* m_Inst;\
public:\
	static Type* GetInst()\
	{\
		if (!m_Inst)\
		{\
			m_Inst = new Type;\
		}\
		return m_Inst;\
	}\
	static void DestroyInst()\
	{\
		if(m_Inst)\
		{\
			delete m_Inst;\
			m_Inst = nullptr;\
		}\
	}\
private:\
	Type();\
	~Type();

#define	DEFINITION_SINGLE(Type) Type* Type::m_Inst = nullptr;

#define	SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr;}

struct Resolution
{
	unsigned int Width;
	unsigned int Height;
};

struct alignas(16) Vertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
};

struct SpriteVertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 UV;
};