#pragma once

namespace hect
{

///
/// Manages layers of concurrent logic.
class Logic :
    public Uncopyable
{
public:
    void addLayer(LogicLayer& layer);
    void removeLayer(LogicLayer& layer);

    size_t layerCount() const;

    void update(TimeSpan timeStep);

private:
    Timer _timer;
    TimeSpan _accumulator;
    TimeSpan _delta;

    std::vector<LogicLayer*> _layers;
};

}