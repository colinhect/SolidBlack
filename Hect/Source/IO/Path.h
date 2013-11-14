namespace hect
{

///
/// A path to a file or directory.
class Path
{
public:

    ///
    /// Constructs an empty path.
    Path();

    ///
    /// Constructs a path from a string.  Any leading or trailing slashes
    /// are ignored.
    ///
    /// \param path The path with each part delimited by a forward slash.
    Path(const char* path);

    ///
    /// Constructs a path from a string.  Any leading or trailing slashes
    /// are ignored.
    ///
    /// \param path The path with each part delimited by a forward slash.
    Path(const std::string& path);

    ///
    /// Returns the file extension of the path.
    std::string extension() const;

    ///
    /// Returns the concatenation of the path and another path.
    ///
    /// \param path The path to concatenate.
    Path operator+(const Path& path) const;

    ///
    /// Appends another path to the end of the path.
    ///
    /// \param path The path to append.
    Path& operator+=(const Path& path);

    ///
    /// Returns the raw path.
    const std::string& toString() const;

    ///
    /// Returns true if the path is less than the given path.
    bool operator<(const Path& path) const;

private:
    void _setRawPath(const char* rawPath);

    std::string _rawPath;
};

///
/// Outputs a path to a stream.
///
/// \param os the output stream.
/// \param path the path to output.
std::ostream& operator<<(std::ostream& os, const Path& path);

}