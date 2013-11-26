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

void RenderingSystem::renderAll(Camera& camera, Renderer& renderer, RenderTarget& target)
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
        _renderMeshTask(task, camera, renderer, target);
    }
}

void RenderingSystem::_renderMeshTask(const MeshTask& task, Camera& camera, Renderer& renderer, const RenderTarget& target)
{
    Mesh& mesh = *task.mesh;
    const Pass& pass = *task.pass;
    const Transform& transform = *task.transform;

    // Prepare the pass
    pass.prepare(renderer);

    // Buid the model matrix
    Matrix4<> model;
    transform.buildMatrix(model);

    // Set uniforms with bindings
    Shader& shader = *pass.shader();
    for (const Uniform& uniform : shader.uniforms())
    {
        if (uniform.hasBinding())
        {
            UniformBinding binding = uniform.binding();

            switch (binding)
            {
            case UniformBinding::RenderTargetSize:
                renderer.setUniform(uniform, Vector2<float>((float)target.width(), (float)target.height()));
                break;
            case UniformBinding::CameraPosition:
                renderer.setUniform(uniform, (Vector3<float>)camera.position());
                break;
            case UniformBinding::CameraUp:
                renderer.setUniform(uniform, (Vector3<float>)camera.up());
                break;
            case UniformBinding::ViewMatrix:
                renderer.setUniform(uniform, (Matrix4<float>)camera.viewMatrix());
                break;
            case UniformBinding::ProjectionMatrix:
                renderer.setUniform(uniform, (Matrix4<float>)camera.projectionMatrix());
                break;
            case UniformBinding::ViewProjectionMatrix:
                renderer.setUniform(uniform, (Matrix4<float>)(camera.projectionMatrix() * camera.viewMatrix()));
                break;
            case UniformBinding::ModelMatrix:
                renderer.setUniform(uniform, (Matrix4<float>)model);
                break;
            case UniformBinding::ModelViewMatrix:
                renderer.setUniform(uniform, (Matrix4<float>)(camera.viewMatrix() * model));
                break;
            case UniformBinding::ModelViewProjectionMatrix:
                renderer.setUniform(uniform, (Matrix4<float>)(camera.projectionMatrix() * (camera.viewMatrix() * model)));
                break;
            }
        }
    }

    // Bind and draw the mesh
    renderer.bindMesh(mesh);
    renderer.draw();
}