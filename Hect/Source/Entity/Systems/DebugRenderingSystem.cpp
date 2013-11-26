#include "Hect.h"

using namespace hect;

DebugRenderingSystem::DebugRenderingSystem()
{
    requireComponent<Renderable>();

    _buildBoxMesh();
    _buildBoxShader();
}

void DebugRenderingSystem::renderWireframeBox(const Vector3<>& position, const Vector3<>& scale, const Vector4<>& color)
{
    BoxTask task;
    task.position = position;
    task.scale = scale;
    task.color = color;
    _boxTasks.push_back(task);
}

void DebugRenderingSystem::renderAll(Camera& camera, Renderer& renderer)
{
    _boxTasks.clear();

    // Enqueue tasks from all visible renderables
    for (Entity& entity : entities())
    {
        Renderable& renderable = entity.component<Renderable>();
        renderable.renderDebug(camera, *this);
    }

    // Render box tasks
    for (const BoxTask& task : _boxTasks)
    {
        _renderBoxTask(task, camera, renderer);
    }
}

void DebugRenderingSystem::_renderBoxTask(const BoxTask& task, Camera& camera, Renderer& renderer)
{
    // Bind the shader
    renderer.bindShader(*_boxShader);

    // Build the transform
    Transform transform;
    transform.translate(task.position);
    transform.scale(task.scale);

    // Buid the model matrix
    Matrix4<> model;
    transform.buildMatrix(model);

    // Set the model-view-projection uniform
    Matrix4<float> modelViewProjection = camera.projectionMatrix() * (camera.viewMatrix() * model);
    renderer.setUniform(_boxShader->uniforms()[0], modelViewProjection);
    renderer.setUniform(_boxShader->uniforms()[1], (Vector4<float>)task.color);

    // Bind the render mode
    RenderMode mode;
    mode.enableState(RenderState::Blend);
    mode.disableState(RenderState::DepthTest);
    mode.setBlendFactors(BlendFactor::SourceAlpha, BlendFactor::OneMinusSourceAlpha);
    renderer.bindMode(mode);

    // Bind and draw the mesh
    renderer.bindMesh(*_boxMesh);
    renderer.draw();
}

void DebugRenderingSystem::_buildBoxMesh()
{
    VertexAttribute::Array attributes;
    attributes.push_back(VertexAttribute(VertexAttributeSemantic::Position, VertexAttributeType::Float, 3));

    _boxMesh.reset(new Mesh(VertexLayout(attributes), PrimitiveType::Lines, IndexType::UnsignedByte));

    // Create vertex data for a wireframe box
    float rawVertexData[] =
    {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };
    Mesh::VertexData vertexData(sizeof(float) * 24);
    std::memcpy(&vertexData[0], rawVertexData, vertexData.size());
    _boxMesh->setVertexData(vertexData);

    // Create index data for a wireframe box
    uint8_t rawIndexData[] =
    {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };
    Mesh::IndexData indexData(24);
    std::memcpy(&indexData[0], rawIndexData, indexData.size());
    _boxMesh->setIndexData(indexData);
}

void DebugRenderingSystem::_buildBoxShader()
{
    const char* vertexSource =
        "#version 330\n"
        "uniform mat4 modelViewProjection;\n"
        "uniform vec4 color;\n"
        "out vec4 lineColor;\n"
        "layout(location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = modelViewProjection * vec4(position, 1.0);\n"
        "    lineColor = color;\n"
        "}\n";

    const char* pixelSource =
        "#version 330\n"
        "in vec4 lineColor;\n"
        "out vec4 outputColor;\n"
        "void main()\n"
        "{\n"
        "    outputColor = lineColor;\n"
        "}\n";

    ShaderModule::RefArray modules;
    modules.push_back(ShaderModule::Ref(new ShaderModule(ShaderModuleType::Vertex, vertexSource)));
    modules.push_back(ShaderModule::Ref(new ShaderModule(ShaderModuleType::Pixel, pixelSource)));

    Uniform::Array uniforms;
    uniforms.push_back(Uniform("modelViewProjection", UniformBinding::ModelViewProjectionMatrix));
    uniforms.push_back(Uniform("color", UniformType::Vector3));

    _boxShader.reset(new Shader(modules, uniforms));
}
