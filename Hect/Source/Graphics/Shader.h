#pragma once

namespace hect
{

///
/// A GPU shader program.
class Shader :
    public GpuObject
{
public:

    ///
    /// A shared reference to a shader.
    typedef std::shared_ptr<Shader> Ref;

    ///
    /// Constructs a shader without any modules or parameter values.
    Shader();

    ///
    /// Constructs a shader given its modules and parameter.
    ///
    /// \param modules The modules.
    /// \param params The parameters.
    Shader(const ShaderModule::RefArray& modules, const ShaderParam::Array& params);

    ///
    /// Destroys the shader if it is uploaded.
    ~Shader();

    ///
    /// Returns the modules.
    const ShaderModule::RefArray& modules() const;

    ///
    /// Returns the parameters.
    ShaderParam::Array& params();

    ///
    /// Returns the parameters.
    const ShaderParam::Array& params() const;

    ///
    /// Returns the parameter with the given name.
    ///
    /// \param name The name of the parameter.
    ///
    /// \throws Error If no parameter with the given name exists.
    const ShaderParam& paramWithName(const std::string& name) const;

private:
    ShaderModule::RefArray _modules;
    ShaderParam::Array _params;
};

}