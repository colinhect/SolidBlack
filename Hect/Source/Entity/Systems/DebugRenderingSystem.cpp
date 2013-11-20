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

void DebugRenderingSystem::renderAll(Camera& camera, Gpu& gpu)
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
        _renderBoxTask(task, camera, gpu);
    }
}

void DebugRenderingSystem::_renderBoxTask(const BoxTask& task, Camera& camera, Gpu& gpu)
{
    // Bind the shader
    gpu.bindShader(*_boxShader);

    // Build the transform
    Transform transform;
    transform.translate(task.position);
    transform.scale(task.scale);

    // Buid the model matrix
    Matrix4<> model;
    transform.buildMatrix(model);

    // Set the model-view-projection parameter
    Matrix4<float> modelViewProjection = camera.projectionMatrix() * (camera.viewMatrix() * model);
    gpu.setShaderParameter(_boxShader->parameters()[0], modelViewProjection);
    gpu.setShaderParameter(_boxShader->parameters()[1], (Vector4<float>)task.color);

    // Bind the render mode
    RenderMode mode;
    mode.enableState(RenderMode::Blend);
    mode.disableState(RenderMode::DepthTest);
    mode.setBlendFactors(RenderMode::SourceAlpha, RenderMode::OneMinusSourceAlpha);
    gpu.bindMode(mode);

    // Bind and draw the mesh
    gpu.bindMesh(*_boxMesh);
    gpu.draw();
}

void DebugRenderingSystem::_buildBoxMesh()
{
    VertexAttribute::Array attributes;
    attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float, 3));

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
    modules.push_back(ShaderModule::Ref(new ShaderModule(ShaderModule::Vertex, vertexSource)));
    modules.push_back(ShaderModule::Ref(new ShaderModule(ShaderModule::Pixel, pixelSource)));

    Shader::Parameter::Array parameters;
    parameters.push_back(Shader::Parameter("modelViewProjection", Shader::Parameter::ModelViewProjectionMatrix));
    parameters.push_back(Shader::Parameter("color", Shader::Value::Vector3));

    _boxShader.reset(new Shader(modules, parameters));
}
