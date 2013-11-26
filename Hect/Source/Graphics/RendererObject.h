#pragma once

namespace hect
{

class Renderer;

///
/// Data which provides a handle to the API-specific data.
struct RendererObjectData
{
    virtual ~RendererObjectData() { }
};

///
/// An object which can be uploaded to the GPU.
class RendererObject
{
    friend class Renderer;
public:
    RendererObject();
    virtual ~RendererObject();

    ///
    /// Returns whether the object is uploaded to the GPU.
    bool isUploaded() const;

protected:

    ///
    /// Returns the renderer that the object is uploaded to.
    Renderer* renderer() const;

private:
    mutable bool _uploaded;
    mutable RendererObjectData* _data;
    mutable Renderer* _renderer;
};

}