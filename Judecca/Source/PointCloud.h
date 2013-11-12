#pragma once

#include <Hect.h>
using namespace hect;

#include "DensitySampler.h"

class PointCloud
{
public:
    PointCloud(unsigned seed, unsigned pointCount, const AxisAlignedBox<>& area, const DensitySampler& sampler, unsigned channel);

    const Mesh::Ref& mesh() const;

private:
    Mesh::Ref _mesh;
};
