#pragma once

namespace hect
{

class Renderer;

///
/// A target that can be rendered to.
class RenderTarget
{
    friend class Engine;
public:

    ///
    /// Constructs a render target without width or height.
    RenderTarget();

    ///
    /// Constructs a render target given the width and height.
    ///
    /// \param width The width.
    /// \param height The height.
    RenderTarget(unsigned width, unsigned height);
    virtual ~RenderTarget() { }

    ///
    /// Binds this target as the active target to the given renderer.
    ///
    /// \param renderer The renderer to bind the target for.
    virtual void bind(Renderer* renderer) = 0;

    ///
    /// Returns the width.
    unsigned width() const;

    ///
    /// Returns the height.
    unsigned height() const;

    ///
    /// Returns the component ratio.
    float aspectRatio() const;

protected:

    ///
    /// Sets the width.
    ///
    /// \param width The new width.
    void setWidth(unsigned width);

    ///
    /// Sets the height.
    ///
    /// \param height The new height.
    void setHeight(unsigned height);

private:
    unsigned _width;
    unsigned _height;
};

}