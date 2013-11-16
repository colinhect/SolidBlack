#pragma once

namespace hect
{

///
/// A higher-level abstraction over a hardware-accelerated graphics API such as
/// OpenGL or DirectX.
class Gpu :
    public Uncopyable
{
    friend class Engine;
public:

    ///
    /// Contains the capabilities of the underlying hardware.
    struct Capabilities
    {
        ///
        /// The maximum number of textures that can be bound.
        unsigned maxTextureUnits;
    };

    ///
    /// Begin a new frame.
    void beginFrame();

    ///
    /// End the current frame.
    void endFrame();

    ///
    /// Binds a render mode.
    ///
    /// \param mode The render mode to bind.
    void bindMode(const RenderMode& mode);

    ///
    /// Selects a render target to begin rendering to.
    ///
    /// \remarks All rendering occurring after this call will render to the
    /// bound target.
    ///
    /// \param renderTarget The render target to bind.
    void bindTarget(RenderTarget& renderTarget);

    ///
    /// Selects a screen as the active render target.
    ///
    /// \param screen The screen to bind.
    void bindScreen(Screen& screen);

    ///
    /// Selects a frame buffer as the active render target.
    ///
    /// \param frameBuffer The frame buffer to bind.
    void bindFrameBuffer(FrameBuffer& frameBuffer);

    ///
    /// Uploads a frame buffer.
    ///
    /// \param frameBuffer The frame buffer to upload.
    void uploadFrameBuffer(FrameBuffer& frameBuffer);

    ///
    /// Destroys a frame buffer.
    ///
    /// \param frameBuffer The frame buffer to destroy.
    void destroyFrameBuffer(FrameBuffer& frameBuffer);

    ///
    /// Binds a shader.
    ///
    /// \param shader The shader to bind.
    void bindShader(Shader& shader);

    ///
    /// Uploads a shader.
    ///
    /// \param shader The shader to upload.
    void uploadShader(Shader& shader);

    ///
    /// Destroys a shader.
    ///
    /// \param shader The shader to destroy.
    void destroyShader(Shader& shader);

    ///
    /// Sets the value of a shader parameter.
    ///
    /// \param parameter The parameter.
    /// \param value The new value.
    void setShaderParameter(const Shader::Parameter& parameter, const Shader::Value& value);

    ///
    /// Uploads a shader module.
    ///
    /// \param module The shader module to upload.
    void uploadShaderModule(ShaderModule& module);

    ///
    /// Destroys a shader module.
    ///
    /// \param module The shader module to destroy.
    void destroyShaderModule(ShaderModule& module);

    ///
    /// Binds a texture.
    ///
    /// \param texture The texture to bind.
    /// \param index The texture index to bind to.
    ///
    /// \throws Error If the binding index lies outside of the hardware
    /// capabilities.
    void bindTexture(Texture& texture, unsigned index);

    ///
    /// Uploads a texture.
    ///
    /// \param texture The texture to upload.
    void uploadTexture(Texture& texture);

    ///
    /// Destroys a texture.
    ///
    /// \param texture The texture to destroy.
    void destroyTexture(Texture& texture);

    ///
    /// Downloads the 2-dimensional of the given uploaded texture.
    ///
    /// \param texture The texture the download the image of.
    ///
    /// \returns The downloaded image.
    ///
    /// \throws Error If the texture is not uploaded.
    Image downloadTextureImage(const Texture& texture);

    ///
    /// Binds a mesh.
    ///
    /// \param mesh The mesh to bind.
    void bindMesh(Mesh& mesh);

    ///
    /// Uploads a mesh.
    ///
    /// \param mesh The mesh to upload.
    void uploadMesh(Mesh& mesh);

    ///
    /// Destroys a mesh.
    ///
    /// \param mesh The mesh to destroy.
    void destroyMesh(Mesh& mesh);

    ///
    /// Draws to the render target in the current state.
    void draw();

    ///
    /// Clears the render target.
    void clear();

    ///
    /// Returns the capabilities of the underlying hardware.
    const Capabilities& capabilities() const;

private:
    Gpu();
    void initialize();

    Capabilities _capabilities;

    RenderTarget* _boundTarget;
    Shader* _boundShader;
    Mesh* _boundMesh;
    std::vector<Texture*> _boundTextures;
};

}