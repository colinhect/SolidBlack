#pragma once

namespace hect
{

///
/// Provides read and write access to persistent storage.
///
/// \warning Only one can be instantiated at a time.
class Storage :
    public Uncopyable
{
public:

    ///
    /// Constructs the storage access
    ///
    /// \throws Error If an instance is already instantiated.
    Storage();

    ///
    /// Closes any open file handles.
    ~Storage();

    ///
    /// Returns the full path to the working directory of the executable.
    Path workingDirectory() const;

    ///
    /// Returns the full path to the user's home directory.
    Path userDirectory() const;

    ///
    /// Sets the directory where write access is allowed and directed to.
    ///
    /// \param path The path to the directory to direct write access.
    void setWriteDirectory(const Path& path);

    ///
    /// Adds a data source to be accessible for reading.
    ///
    /// \remarks A data source can be a directory or an archive.  Any file
    /// with the same path as a file in a previously added data source will
    /// be overriden by the file in the most recently added data source.
    ///
    /// \param path Path to the directory or archive to add for reading.
    void addDataSource(const Path& path);

    ///
    /// Opens a file for reading.
    ///
    /// \param path The path to the file to open for reading.
    ///
    /// \returns A stream for the opened file.
    FileReadStream openFileForRead(const Path& path) const;

    ///
    /// Opens a file for writing.
    ///
    /// \warning The write directory must be set using the
    /// setWriteDirectory() method.
    ///
    /// \param path The path to the file to open for writing relative to
    /// the write directory path.
    ///
    /// \returns A stream for the opened file.
    FileWriteStream openFileForWrite(const Path& path);

    ///
    /// Creates a directory.
    ///
    /// \remarks Any missing parent directories are also created if they don't
    /// exist.  If the directory already exists then nothing happens.
    ///
    /// \warning The write directory must first be set using the
    /// setWriteDirectory() method.
    ///
    /// \param path The path to the directory to create relative to the
    /// write directory path.
    void createDirectory(const Path& path);

    ///
    /// Removes the file or directory at the given path.  If the path does
    /// not exist then nothing happens.
    ///
    /// \warning The write directory mustfirst  be set using the
    /// setWriteDirectory() method.
    ///
    /// \param path The path to the file or directory to remove relative to
    /// the write directory path.
    void remove(const Path& path);

    ///
    /// Returns whether there is a file or directory at the given path.
    ///
    /// \param path The path to check the existence of.
    bool exists(const Path& path) const;

private:
    Path _convertPath(const char* rawPath) const;
};

}