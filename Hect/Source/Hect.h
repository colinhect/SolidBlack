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

// Some template tricks in ComponentSerializer causes this warning
#pragma warning(disable:4505)

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
#include "Core/TimeSpan.h"
#include "Core/Timer.h"
#include "Core/TaskPool.h"

#include "Math/Angle.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4.h"
#include "Math/Box.h"
#include "Math/Sphere.h"
#include "Math/AxisAlignedBox.h"
#include "Math/Plane.h"
#include "Math/Frustum.h"

#include "Core/DataValue.h"

#include "IO/Path.h"
#include "IO/ReadStream.h"
#include "IO/WriteStream.h"
#include "IO/FileReadStream.h"
#include "IO/FileWriteStream.h"
#include "IO/MemoryReadStream.h"
#include "IO/MemoryWriteStream.h"
#include "IO/FileSystem.h"
#include "Asset/AssetLoader.h"
#include "Asset/AssetEntry.h"
#include "Asset/AssetHandle.h"
#include "Asset/AssetCache.h"

#include "Core/DataValueJsonFormat.h"

#include "Graphics/VertexAttribute.h"
#include "Graphics/VertexLayout.h"
#include "Graphics/RendererObject.h"
#include "Graphics/RenderMode.h"
#include "Graphics/Image.h"
#include "Graphics/ImagePngFormat.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureDataFormat.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/ShaderModule.h"
#include "Graphics/UniformValue.h"
#include "Graphics/Uniform.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderDataFormat.h"
#include "Graphics/PassUniformValue.h"
#include "Graphics/Pass.h"
#include "Graphics/Technique.h"
#include "Graphics/Material.h"
#include "Graphics/MaterialDataFormat.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshWriter.h"
#include "Graphics/MeshDataFormat.h"
#include "Graphics/VideoMode.h"
#include "Graphics/VideoModeDataFormat.h"
#include "Graphics/Window.h"
#include "Graphics/Renderer.h"

#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include "Input/InputAxis.h"
#include "Input/InputAxisDataFormat.h"
#include "Input/InputSystem.h"

#include "Noise/Random.h"

#include "Network/IpAddress.h"
#include "Network/Packet.h"
#include "Network/Peer.h"
#include "Network/Socket.h"

#include "Entity/Component.h"
#include "Entity/EntityData.h"
#include "Entity/Entity.h"
#include "Entity/System.h"
#include "Entity/ComponentReader.h"
#include "Entity/ComponentWriter.h"
#include "Entity/ComponentSerializer.h"
#include "Entity/EntitySerializer.h"
#include "Entity/Scene.h"

#include "Entity/Components/Camera.h"
#include "Entity/Components/Transform.h"
#include "Entity/Components/Geometry.h"
#include "Entity/Components/RigidBody.h"
#include "Entity/Components/AmbientLight.h"
#include "Entity/Components/DirectionalLight.h"

#include "Entity/Systems/CameraSystem.h"
#include "Entity/Systems/PhysicsSystem.h"

#include "Core/State.h"
#include "Core/StateFlow.h"