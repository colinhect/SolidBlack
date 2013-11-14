namespace hect
{

///
/// A state of the engine (e.g. main menu, single player game, credits).
class State
{
public:

    ///
    /// Constructs a state given the engine and the time step.
    ///
    /// \param engine The engine.
    /// \param timeStep The duration of time between each update (in seconds).
    State(Engine& engine, double timeStep);
    virtual ~State() { }

    ///
    /// Called when the state begins.
    virtual void begin();

    ///
    /// Called when the state ends.
    virtual void end();

    ///
    /// Called once every time step.
    ///
    /// \param timeStep The duration of time between each update (in seconds).
    virtual void update(double timeStep);

    ///
    /// Called when the a frame is rendered.
    ///
    /// \param delta The delta between the last call to update() and the next
    /// call to update() (useful for interpolation).
    virtual void render(double delta);

    ///
    /// Returns whether the state is active.
    bool isActive() const;

    ///
    /// Returns the time between each frame.
    double timeStep() const;

protected:

    ///
    /// Returns the engine.
    Engine& engine();

    ///
    /// Sets whether the state is active.
    ///
    /// \remarks When the current state of the engine is no longer active
    /// it will end and the next state on the stack will begin.
    ///
    /// \param active True if the state is active; false otherwise.
    void setActive(bool active);

private:
    Engine* _engine;
    double _timeStep;
    bool _active;
};

}