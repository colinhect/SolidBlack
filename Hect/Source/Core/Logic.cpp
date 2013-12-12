#include "Hect.h"

using namespace hect;

void Logic::addLayer(LogicLayer& layer)
{
    _layers.push_back(&layer);
}

void Logic::removeLayer(LogicLayer& layer)
{
    _layers.erase(std::remove(_layers.begin(), _layers.end(), &layer), _layers.end());
}

size_t Logic::layerCount() const
{
    return _layers.size();
}

void Logic::update(TimeSpan timeStep)
{
    TimeSpan deltaTime = _timer.elapsed();
    _timer.reset();

    _accumulator += deltaTime;
    _delta += deltaTime;

    while (_accumulator.microseconds() >= timeStep.microseconds())
    {
        // Update the layers
        for (LogicLayer* layer : _layers)
        {
            layer->update(timeStep.seconds());
        }

        _delta = TimeSpan();
        _accumulator -= timeStep;
    }

    // Render the layers
    for (LogicLayer* layer : _layers)
    {
        layer->render(_delta.seconds() / timeStep.seconds());
    }
}