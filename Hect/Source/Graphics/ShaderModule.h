#pragma once

namespace hect
{

///
/// A shader module.
class ShaderModule :
    public GpuObject
{
public:

    ///
    /// A shared reference to a shader module.
    typedef std::shared_ptr<ShaderModule> Ref;

    ///
    /// An array of shared shader module references.
    typedef std::vector<ShaderModule::Ref> RefArray;

    ///
    /// A shader module type.
    enum Type
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
    /// Constructs an empty shader module.
    ShaderModule();

    ///
    /// Constructs a shader module given its type and source.
    ///
    /// \param type The type.
    /// \param source The source.
    ShaderModule(Type type, const std::string& source);

    ///
    /// Destroys the shader if it is uploaded.
    ~ShaderModule();

    ///
    /// Returns the type.
    Type type() const;

    /// Returns the source.
    const std::string& source() const;

private:
    Type _type;
    std::string _source;
};

}