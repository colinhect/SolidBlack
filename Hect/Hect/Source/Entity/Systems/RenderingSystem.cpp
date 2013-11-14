#include "Hect.h"

using namespace hect;

RenderingSystem::RenderingSystem()
{
    requireComponent<Renderable>();
}

void RenderingSystem::renderMesh(Mesh& mesh, const Material& material, const Transform& transform)
{
    if (!material.techniques().empty())
    {
        const Technique& technique = material.techniques()[0];
        for (const Pass& pass : technique.passes())
        {
            MeshTask task;
            task.mesh = &mesh;
            task.pass = &pass;
            task.transform = &transform;
            _meshTasks.push_back(task);
        }
    }
}

void RenderingSystem::renderAll(Camera& camera, Gpu& gpu, const RenderTarget& target)
{
    _meshTasks.clear();

    // Enqueue tasks from all visible renderables
    for (Entity& entity : entities())
    {
        Renderable& renderable = entity.component<Renderable>();
        renderable.render(camera, *this);
    }

    // Render mesh tasks
    for (const MeshTask& task : _meshTasks)
    {
        _renderMeshTask(task, camera, gpu, target);
    }
}

void RenderingSystem::_renderMeshTask(const MeshTask& task, Camera& camera, Gpu& gpu, const RenderTarget& target)
{
    Mesh& mesh = *task.mesh;
    const Pass& pass = *task.pass;
    const Transform& transform = *task.transform;

    // Prepare the pass
    pass.prepare(gpu);

    // Buid the model matrix
    Matrix4<> model;
    transform.buildMatrix(model);

    // Set bound parameters
    Shader& shader = *pass.shader();
    for (const Shader::Parameter& parameter : shader.parameters())
    {
        if (parameter.hasBinding())
        {
            Shader::Parameter::Binding binding = parameter.binding();

            switch (binding)
            {
            case Shader::Parameter::RenderTargetSize:
                gpu.setShaderParameter(parameter, Vector2<float>((float)target.width(), (float)target.height()));
                break;
            case Shader::Parameter::CameraPosition:
                gpu.setShaderParameter(parameter, (Vector3<float>)camera.position());
                break;
            case Shader::Parameter::CameraUp:
                gpu.setShaderParameter(parameter, (Vector3<float>)camera.up());
                break;
            case Shader::Parameter::ViewMatrix:
                gpu.setShaderParameter(parameter, (Matrix4<float>)camera.viewMatrix());
                break;
            case Shader::Parameter::ProjectionMatrix:
                gpu.setShaderParameter(parameter, (Matrix4<float>)camera.projectionMatrix());
                break;
            case Shader::Parameter::ViewProjectionMatrix:
                gpu.setShaderParameter(parameter, (Matrix4<float>)(camera.projectionMatrix() * camera.viewMatrix()));
                break;
            case Shader::Parameter::ModelMatrix:
                gpu.setShaderParameter(parameter, (Matrix4<float>)model);
                break;
            case Shader::Parameter::ModelViewMatrix:
                gpu.setShaderParameter(parameter, (Matrix4<float>)(camera.viewMatrix() * model));
                break;
            case Shader::Parameter::ModelViewProjectionMatrix:
                gpu.setShaderParameter(parameter, (Matrix4<float>)(camera.projectionMatrix() * (camera.viewMatrix() * model)));
                break;
            }
        }
    }

    // Bind and draw the mesh
    gpu.bindMesh(mesh);
    gpu.draw();
}