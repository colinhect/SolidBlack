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
    /// Constructs a logic flow given the duration of time between each fixed
    /// update.
    ///
    /// \param timeStep The duration of time between each fixed update.
    LogicFlow(TimeSpan timeStep);

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
    /// \returns True if there are layers in the flow; false otherwise.
    bool update();

private:
    void _removeInactiveLayers();

    Timer _timer;
    TimeSpan _timeStep;
    TimeSpan _accumulator;
    TimeSpan _delta;

    std::vector<LogicLayer*> _layers;
};

}