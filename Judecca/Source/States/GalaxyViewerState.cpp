#include "GalaxyViewerState.h"

#include "DensitySampler.h"
#include "PointCloud.h"
#include "Components/StarField.h"
#include "Components/FreeCameraController.h"

GalaxyViewerState::GalaxyViewerState(Engine& engine) :
    SolidBlackState(engine),
    _freeCameraControllerSystem(engine.input())
{
}

void GalaxyViewerState::begin()
{
    SolidBlackState::begin();

    Screen& screen = engine().screen();

    galaxyScene().addSystem(_freeCameraControllerSystem);

    // Add a free-controlled camera to the scene
    Entity cameraEntity = galaxyScene().createEntity();
    cameraEntity.addComponent<Transform>(Vector3<>(0, 1000, 30000));
    cameraEntity.addComponent<Camera>(Angle<>::fromDegrees(80), screen.aspectRatio(), 0.01, 250000);
    cameraEntity.addComponent<FreeCameraController>();
    cameraEntity.activate();

    _createGalaxy();

    galaxyScene().refresh();
}

void GalaxyViewerState::update(double timeStep)
{
    SolidBlackState::update(timeStep);

    _freeCameraControllerSystem.update(timeStep);
    galaxyScene().refresh();
}

void GalaxyViewerState::_createGalaxy()
{
    LOG_INFO("Creating galaxy...");

    // The entire area of the clouds in the galaxy
    AxisAlignedBox<> area(Vector3<>(-50000, -3000, -50000), Vector3<>(50000, 3000, 50000));

    // Create the cloud density sampler
    Image::Ref cloudDensityTop = assetCache().get<Image>("Textures/CloudDensityTop.png");
    Image::Ref cloudDensitySide = assetCache().get<Image>("Textures/CloudDensitySide.png");
    DensitySampler sampler(area, cloudDensityTop, cloudDensitySide);

    // Dust
    {
        Material::Ref material = assetCache().get<Material>("Materials/Dust.material");

        Entity dust = galaxyScene().createEntity();
        Transform& transform = dust.addComponent<Transform>();
        Geometry& geometry = dust.addComponent<Geometry>(transform);

        PointCloud pointCloud(123, 800000, area, sampler, 0);
        geometry.addMesh(pointCloud.mesh(), material);

        dust.activate();
    }

    // Dark
    {
        Material::Ref material = assetCache().get<Material>("Materials/Dark.material");

        Entity dark = galaxyScene().createEntity();
        Transform& transform = dark.addComponent<Transform>();
        Geometry& geometry = dark.addComponent<Geometry>(transform);

        PointCloud pointCloud(321, 300000, area, sampler, 1);
        geometry.addMesh(pointCloud.mesh(), material);

        dark.activate();
    }

    // Center
    {
        Material::Ref material = assetCache().get<Material>("Materials/Center.material");

        Entity center = galaxyScene().createEntity();
        Transform& transform = center.addComponent<Transform>();
        Geometry& geometry = center.addComponent<Geometry>(transform);

        PointCloud pointCloud(123, 24000, area, sampler, 2);
        geometry.addMesh(pointCloud.mesh(), material);

        center.activate();
    }

    // Star fields
    {
        AxisAlignedBox<> area(Vector3<>(-50000, -12500, -50000), Vector3<>(50000, 12500, 50000));

        Image::Ref densityTop = assetCache().get<Image>("Textures/StarDensityTop.png");
        Image::Ref densitySide = assetCache().get<Image>("Textures/StarDensitySide.png");
        DensitySampler::Ref sampler(new DensitySampler(area, densityTop, densitySide));

        Material::Ref material = assetCache().get<Material>("Materials/Star.material");

        unsigned maxDepth = 7;
        double starFieldSize = 40000;

        for (int x = -1; x < 2; x++)
        {
            for (int z = -1; z < 2; z++)
            {
                Vector3<> position(x, 0, z);

                Entity starField = galaxyScene().createEntity();
                starField.addComponent<StarField>(position * starFieldSize, starFieldSize, maxDepth, sampler, material);
                starField.activate();
            }
        }
    }

    LOG_INFO("Done");
}