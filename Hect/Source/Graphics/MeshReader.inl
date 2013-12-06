namespace hect
{

template <typename T>
const T& MeshReader::_readAttributeData(const VertexAttribute& attribute) const
{
    return *(const T*)&_mesh->vertexData()[_vertexDataIndex + attribute.offset()];
}

}