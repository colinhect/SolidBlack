#pragma once

namespace hect
{

///
/// Provides functionality for saving/loading meshes to/from the internal
/// bianry mesh format.
class MeshBinaryFormat
{
public:

    ///
    /// The number identifying a file in this format.
    static const uint32_t Signature;
    
    ///
    /// Loads a mesh from a stream.
    ///
    /// \param mesh The mesh to load to.
    /// \param stream The stream to read from.
    static void load(Mesh& mesh, const std::string& name, ReadStream& stream);

    ///
    /// Saves a mesh to stream.
    ///
    /// \param mesh The mesh to save.
    /// \param stream The stream to write to.
    static void save(const Mesh& mesh, WriteStream& stream);

};

}