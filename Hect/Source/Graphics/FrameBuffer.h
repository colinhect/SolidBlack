#pragma once

namespace hect
{

///
/// A buffer on the GPU that can be rendered to.
class FrameBuffer :
    public RenderTarget,
    public RendererObject
{
public:

    ///
    /// Constructs a frame buffer of a given size with an optional depth
    /// component.
    ///
    /// \param targets The texture targets.
    /// \param depthComponent True if the frame buffer will have a depth
    /// component; false otherwise.
    FrameBuffer(const Texture::Array& targets, bool depthComponent = true);

    ///
    /// Constructs a copy of the another frame buffer.
    ///
    /// \param frameBuffer The frame buffer to copy.
    FrameBuffer(const FrameBuffer& frameBuffer);

    ///
    /// Destroys the frame buffer if it is uploaded.
    ~FrameBuffer();

    ///
    /// \copydoc RenderTarget::bind()
    void bind(Renderer* renderer);

    ///
    /// Returns the targets.
    Texture::Array& targets();

    ///
    /// Returns the targets.
    const Texture::Array& targets() const;

    ///
    /// Returns whether the frame buffer has a depth component.
    bool hasDepthComponent() const;

private:
    bool _depthComponent;
    Texture::Array _targets;
};

}