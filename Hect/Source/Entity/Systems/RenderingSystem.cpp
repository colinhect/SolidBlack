#include "Hect.h"

using namespace hect;

RenderingSystem::RenderingSystem(Renderer& renderer) :
    _renderer(&renderer)
{
    requireComponent<Renderable>();
}

void RenderingSystem::renderMesh(Mesh& mesh, const Pass& pass, const Transform& transform, Camera& camera, const RenderTarget& target)
{
    // Prepare the pass
    pass.prepare(*_renderer);

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
                _renderer->setUniform(uniform, Vector2<float>((float)target.width(), (float)target.height()));
                break;
            case UniformBinding::CameraPosition:
                _renderer->setUniform(uniform, (Vector3<float>)camera.position());
                break;
            case UniformBinding::CameraUp:
                _renderer->setUniform(uniform, (Vector3<float>)camera.up());
                break;
            case UniformBinding::ViewMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)camera.viewMatrix());
                break;
            case UniformBinding::ProjectionMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)camera.projectionMatrix());
                break;
            case UniformBinding::ViewProjectionMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)(camera.projectionMatrix() * camera.viewMatrix()));
                break;
            case UniformBinding::ModelMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)model);
                break;
            case UniformBinding::ModelViewMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)(camera.viewMatrix() * model));
                break;
            case UniformBinding::ModelViewProjectionMatrix:
                _renderer->setUniform(uniform, (Matrix4<float>)(camera.projectionMatrix() * (camera.viewMatrix() * model)));
                break;
            }
        }
    }

    // Bind and draw the mesh
    _renderer->bindMesh(mesh);
    _renderer->draw();
}

Renderer& RenderingSystem::renderer()
{
    return *_renderer;
}
