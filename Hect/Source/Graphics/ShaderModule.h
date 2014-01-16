#pragma once

namespace hect
{

///
/// A shader module type.
enum class ShaderModuleType
{

    ///
    /// A vertex program module.
    Vertex,

    ///
    /// A pixel program module.
    Pixel,

    ///
    /// A geometry program module.
    Geometry
};

///
/// A shader module.
class ShaderModule :
    public RendererObject
{
public:

    ///
    /// Constructs an empty shader module.
    ShaderModule();

    ///
    /// Constructs a shader module given its type and source.
    ///
    /// \param name The name.
    /// \param type The type.
    /// \param source The source.
    ShaderModule(const std::string& name, ShaderModuleType type, const std::string& source);

    ///
    /// Destroys the shader if it is uploaded.
    ~ShaderModule();

    ///
    /// Returns the name.
    const std::string& name() const;

    ///
    /// Returns the type.
    ShaderModuleType type() const;

    /// Returns the source.
    const std::string& source() const;

private:
    std::string _name;
    ShaderModuleType _type;
    std::string _source;
};

}