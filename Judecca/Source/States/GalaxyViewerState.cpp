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

    Window& window = engine().window();

    galaxyScene().addSystem(_freeCameraControllerSystem);

    // Add a free-controlled camera to the scene
    Entity cameraEntity = galaxyScene().createEntity();
    cameraEntity.addComponent<Transform>(Vector3<>(0, 1000, 30000));
    cameraEntity.addComponent<Camera>(Angle<>::fromDegrees(80), window.aspectRatio(), 0.01, 250000);
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

    AxisAlignedBox<> area(Vector3<>(-50000, -3000, -50000), Vector3<>(50000, 3000, 50000));
    Image::Ref densityTop = assetCache().get<Image>("Textures/DensityTop.png");
    Image::Ref densitySide = assetCache().get<Image>("Textures/DensitySide.png");

    DensitySampler::Ref sampler(new DensitySampler(area, densityTop, densitySide));

    // Dust
    {
        Material::Ref material = assetCache().get<Material>("Materials/Dust.material");

        Entity dust = galaxyScene().createEntity();
        Transform& transform = dust.addComponent<Transform>();
        Geometry& geometry = dust.addComponent<Geometry>(transform);

        PointCloud pointCloud(123, 800000, area, *sampler, 0);
        geometry.addMesh(pointCloud.mesh(), material);

        dust.activate();
    }

    // Dark
    {
        Material::Ref material = assetCache().get<Material>("Materials/Dark.material");

        Entity dark = galaxyScene().createEntity();
        Transform& transform = dark.addComponent<Transform>();
        Geometry& geometry = dark.addComponent<Geometry>(transform);

        PointCloud pointCloud(321, 300000, area, *sampler, 1);
        geometry.addMesh(pointCloud.mesh(), material);

        dark.activate();
    }

    // Center
    {
        Material::Ref material = assetCache().get<Material>("Materials/Center.material");

        Entity center = galaxyScene().createEntity();
        Transform& transform = center.addComponent<Transform>();
        Geometry& geometry = center.addComponent<Geometry>(transform);

        PointCloud pointCloud(123, 24000, area, *sampler, 2);
        geometry.addMesh(pointCloud.mesh(), material);

        center.activate();
    }

    // Star fields
    {
        Entity starField = galaxyScene().createEntity();
        starField.addComponent<StarField>(Vector3<>(0, 0, 0), 16000, 5, sampler, Material::Ref());
        starField.activate();
    }

    LOG_INFO("Done");
}