#pragma once

#include <atomic>
#include <bitset>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <vector>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <cstdint>

#ifdef _MSC_VER
#define HECT_WINDOWS
#ifdef _DEBUG
#define HECT_DEBUG
#endif
#endif

namespace hect
{

///
/// An approximation of Pi.
const double pi = 3.14159265358979323846;

}

#include "Core/Format.h"
#include "Core/Logging.h"
#include "Core/Error.h"
#include "Core/Uncopyable.h"
#include "Core/Any.h"
#include "Core/Memory.h"
#include "Core/DataValue.h"
#include "Core/TimeSpan.h"
#include "Core/TaskPool.h"

#include "Math/Angle.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4.h"
#include "Math/Box.h"
#include "Math/AxisAlignedBox.h"
#include "Math/Plane.h"
#include "Math/Frustum.h"

#include "IO/Path.h"
#include "IO/ReadStream.h"
#include "IO/WriteStream.h"
#include "IO/FileReadStream.h"
#include "IO/FileWriteStream.h"
#include "IO/MemoryReadStream.h"
#include "IO/MemoryWriteStream.h"
#include "IO/Storage.h"
#include "IO/JsonParser.h"
#include "IO/JsonFormat.h"

#include "Asset/AssetLoader.h"
#include "Asset/AssetEntry.h"
#include "Asset/AssetHandle.h"
#include "Asset/AssetCache.h"

#include "Graphics/VertexAttribute.h"
#include "Graphics/VertexLayout.h"
#include "Graphics/GpuObject.h"
#include "Graphics/RenderMode.h"
#include "Graphics/Image.h"
#include "Graphics/ImagePngFormat.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureJsonFormat.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/ShaderModule.h"
#include "Graphics/UniformValue.h"
#include "Graphics/Uniform.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderJsonFormat.h"
#include "Graphics/PassUniformValue.h"
#include "Graphics/Pass.h"
#include "Graphics/Technique.h"
#include "Graphics/Material.h"
#include "Graphics/MaterialJsonFormat.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshBuilder.h"
#include "Graphics/MeshJsonFormat.h"
#include "Graphics/Screen.h"
#include "Graphics/Gpu.h"

#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include "Input/InputAxis.h"
#include "Input/Input.h"

#include "Noise/Random.h"

#include "Core/Engine.h"

#include "Network/IpAddress.h"
#include "Network/Packet.h"
#include "Network/Peer.h"
#include "Network/Socket.h"

#include "Entity/EntityComponent.h"
#include "Entity/EntityAttributes.h"
#include "Entity/Entity.h"
#include "Entity/EntitySystem.h"
#include "Entity/Scene.h"

#include "Entity/Components/Camera.h"
#include "Entity/Components/Transform.h"
#include "Entity/Components/Renderable.h"
#include "Entity/Components/Geometry.h"
#include "Entity/Components/RigidBody.h"

#include "Entity/Systems/CameraSystem.h"
#include "Entity/Systems/RenderingSystem.h"
#include "Entity/Systems/DebugRenderingSystem.h"
#include "Entity/Systems/PhysicsSystem.h"

#include "Core/State.h"
