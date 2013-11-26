#pragma once

namespace hect
{

///
/// A GPU shader program.
class Shader :
    public RendererObject
{
public:

    ///
    /// A shared reference to a shader.
    typedef std::shared_ptr<Shader> Ref;

    ///
    /// Constructs a shader without any modules or uniforms.
    Shader();

    ///
    /// Constructs a shader given its modules and uniforms.
    ///
    /// \param modules The modules.
    /// \param uniforms The uniforms.
    Shader(const ShaderModule::RefArray& modules, const Uniform::Array& uniforms);

    ///
    /// Destroys the shader if it is uploaded.
    ~Shader();

    ///
    /// Returns the modules.
    const ShaderModule::RefArray& modules() const;

    ///
    /// Returns the uniforms.
    Uniform::Array& uniforms();

    ///
    /// Returns the uniforms.
    const Uniform::Array& uniforms() const;

    ///
    /// Returns the uniform with the given name.
    ///
    /// \param name The name of the uniform.
    ///
    /// \throws Error If no uniform with the given name exists.
    const Uniform& uniformWithName(const std::string& name) const;

private:
    ShaderModule::RefArray _modules;
    Uniform::Array _uniforms;
};

}