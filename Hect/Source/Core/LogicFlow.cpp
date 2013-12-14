#include "Hect.h"

using namespace hect;

LogicFlow::LogicFlow(TimeSpan timeStep) :
    _timeStep(timeStep)
{
}

void LogicFlow::addLayer(LogicLayer& layer)
{
    _layers.push_back(&layer);
}

void LogicFlow::removeLayer(LogicLayer& layer)
{
    _layers.erase(std::remove(_layers.begin(), _layers.end(), &layer), _layers.end());
}

void LogicFlow::removeAllLayers()
{
    _layers.clear();
}

bool LogicFlow::update()
{
    _removeInactiveLayers();

    if (_layers.size() == 0)
    {
        return false;
    }

    TimeSpan deltaTime = _timer.elapsed();
    _timer.reset();

    _accumulator += deltaTime;
    _delta += deltaTime;

    while (_accumulator.microseconds() >= _timeStep.microseconds())
    {
        // Update the layers
        for (LogicLayer* layer : _layers)
        {
            layer->fixedUpdate(_timeStep.seconds());
        }

        _delta = TimeSpan();
        _accumulator -= _timeStep;
    }

    // Render the layers
    for (LogicLayer* layer : _layers)
    {
        layer->frameUpdate(_delta.seconds() / _timeStep.seconds());
    }

    return true;
}

void LogicFlow::_removeInactiveLayers()
{
    // Build a list of inactive layers
    std::vector<LogicLayer*> inactiveLayers;
    for (LogicLayer* layer : _layers)
    {
        if (!layer->isActive())
        {
            inactiveLayers.push_back(layer);
        }
    }

    // Remove all inactive layers
    for (LogicLayer* layer : inactiveLayers)
    {
        removeLayer(*layer);
    }
}