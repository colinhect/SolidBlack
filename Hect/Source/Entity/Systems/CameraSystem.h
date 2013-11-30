#pragma once

namespace hect
{

///
/// Provides access to the active camera in the scene.
class CameraSystem :
    public System
{
public:

    ///
    /// \copydoc System::includeEntity()
    bool includesEntity(const Entity& entity) const;

    ///
    /// Returns whether there is an active camera in the scene.
    bool hasCamera() const;

    ///
    /// Returns the active camera in the scene.
    ///
    /// \warning Always call hasCamera() before calling this function to
    /// avoid undefined behavior.
    Camera& camera();

    ///
    /// Updates all cameras to follow their transforms.
    void update();
};

}