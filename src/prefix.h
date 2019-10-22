#pragma once

#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <DirectXMath.h>
#include <Windows.h>
#include <windowsx.h>

#ifdef _DEBUG
#include <io.h>
#include <fcntl.h>
#endif

#include <chrono>

#include <string>
#include <vector>
#include <functional>

#include <FreeImage.h>

#include "util/Timer.h"
#include "input/Input.h"
#include "graphics/Window.h"
#include "graphics/DirectX/DXContext.h"
#include "graphics/DirectX/DXBuffer.h"
#include "graphics/DirectX/DXTexture.h"
#include "shader/Shader.h"
#include "shader/Material.h"
#include "graphics/Mesh.h"

#include "game/Camera.h"