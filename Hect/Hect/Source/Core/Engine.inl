namespace hect
{

template <typename T>
State& Engine::pushState()
{
    auto state = std::make_shared<T>();
    _states.push(state);
    return *state;
}

template <typename T, typename A0>
State& Engine::pushState(A0&& a0)
{
    auto state = std::make_shared<T>(a0);
    _states.push(state);
    return *state;
}

template <typename T, typename A0, typename A1>
State& Engine::pushState(A0&& a0, A1&& a1)
{
    auto state = std::make_shared<T>(a0, a1);
    _states.push(state);
    return *state;
}

template <typename T, typename A0, typename A1, typename A2>
State& Engine::pushState(A0&& a0, A1&& a1, A2&& a2)
{
    auto state = std::make_shared<T>(a0, a1, a2);
    _states.push(state);
    return *state;
}

}