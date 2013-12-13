#pragma once

namespace hect
{

///
/// Manages a flow of logic layers.
///
/// \remarks All layers in the flow are updated in the order in which they were
/// added.  Inactive layers are removed from the flow.
class LogicFlow :
    public Uncopyable
{
public:

    ///
    /// Adds a layer to the flow.
    ///
    /// \remarks The layer will remain in the flow until it is inactive or
    /// explicitly removed.
    ///
    /// \param layer The layer to add.
    void addLayer(LogicLayer& layer);
    
    ///
    /// Removes a layer from the flow.
    ///
    /// \param layer The layer to remove.
    void removeLayer(LogicLayer& layer);

    ///
    /// Removes all layers from the flow.
    void removeAllLayers();

    ///
    /// Updates all layers in the flow.
    ///
    /// \param timeStep The duration of time between each fixed update.
    ///
    /// \returns True if there are layers in the flow; false otherwise.
    bool update(TimeSpan timeStep);

private:
    void _removeInactiveLayers();

    Timer _timer;
    TimeSpan _accumulator;
    TimeSpan _delta;

    std::vector<LogicLayer*> _layers;
};

}