namespace hect
{

template <typename T>
std::shared_ptr<T> AssetEntry<T>::get()
{
    // Throw an error if the asset loading failed
    if (_errorOccurred)
    {
        throw Error(format("Failed to load asset '%s': %s", _path.toString().c_str(), _errorMessage.c_str()));
    }

    return _asset;
}

template <typename T>
AssetEntry<T>::AssetEntry(AssetCache& assetCache, const Path& path) :
    _assetCache(&assetCache),
    _path(path),
    _errorOccurred(false)
{
}

template <typename T>
void AssetEntry<T>::_load()
{
    _asset = std::make_shared<T>();

    // Load the asset and save the error message
    try
    {
        LOG_INFO(format("Loading '%s'...", _path.toString().c_str()));
        AssetLoader<T>::load(*_asset, _path, *_assetCache);
    }
    catch (Error& error)
    {
        // Save the error message
        _errorOccurred = true;
        _errorMessage = error.what();
    }
}

}