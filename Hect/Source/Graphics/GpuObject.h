namespace hect
{

class Gpu;

///
/// Data which provides a handle to the API-specific data.
struct GpuObjectData
{
    virtual ~GpuObjectData() { }
};

///
/// An object which can be uploaded to the GPU.
class GpuObject
{
    friend class Gpu;
public:
    GpuObject();
    virtual ~GpuObject();

    ///
    /// Returns whether the object is uploaded to the GPU.
    bool isUploaded() const;

protected:

    ///
    /// Returns the GPU that the object is uploaded to.
    Gpu* gpu() const;

private:
    mutable bool _uploaded;
    mutable GpuObjectData* _data;
    mutable Gpu* _gpu;
};

}