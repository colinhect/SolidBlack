#include "Hect.h"

using namespace hect;

#include "Internal/Bullet.h"

RigidBody::RigidBody() :
    _mass(0),
    _bulletRigidBody(nullptr),
    _bulletMesh(nullptr)
{
}

RigidBody::~RigidBody()
{
    // Delete the Bullet rigid body
    if (_bulletRigidBody)
    {
        btRigidBody* rigidBody = (btRigidBody*)_bulletRigidBody;
        delete rigidBody->getMotionState();
        delete rigidBody->getCollisionShape();
        delete rigidBody;
    }

    // Delete up the Bullet mesh
    if (_bulletMesh)
    {
        btTriangleMesh* mesh = (btTriangleMesh*)_bulletMesh;
        delete mesh;
    }
}

double RigidBody::mass() const
{
    return _mass;
}

void RigidBody::setMass(double mass)
{
    if (_bulletRigidBody)
    {
        throw Error("Cannot set mass after the rigid body is created");
    }
    _mass = mass;
}

const Vector3<>& RigidBody::linearVelocity() const
{
    // Update the current value from the Bullet rigid body
    if (_bulletRigidBody)
    {
        btRigidBody* rigidBody = (btRigidBody*)_bulletRigidBody;
        _linearVelocity = convertFromBullet(rigidBody->getLinearVelocity());
    }

    return _linearVelocity;
}

void RigidBody::setLinearVelocity(const Vector3<>& linearVelocity)
{
    // Set the new value in the bullet rigid body as well
    if (_bulletRigidBody)
    {
        btRigidBody* rigidBody = (btRigidBody*)_bulletRigidBody;
        rigidBody->setLinearVelocity(convertToBullet(linearVelocity));
    }

    _linearVelocity = linearVelocity;
}

const Vector3<>& RigidBody::angularVelocity() const
{
    // Update the current value from the Bullet rigid body
    if (_bulletRigidBody)
    {
        btRigidBody* rigidBody = (btRigidBody*)_bulletRigidBody;
        _angularVelocity = convertFromBullet(rigidBody->getAngularVelocity());
    }

    return _angularVelocity;
}

void RigidBody::setAngularVelocity(const Vector3<>& angularVelocity)
{
    // Set the new value in the bullet rigid body as well
    if (_bulletRigidBody)
    {
        btRigidBody* rigidBody = (btRigidBody*)_bulletRigidBody;
        rigidBody->setLinearVelocity(convertToBullet(angularVelocity));
    }

    _angularVelocity = angularVelocity;
}

AssetHandle<Mesh>& RigidBody::mesh()
{
    return _mesh;
}

const AssetHandle<Mesh>& RigidBody::mesh() const
{
    return _mesh;
}

void RigidBody::setMesh(const AssetHandle<Mesh>& mesh)
{
    if (_bulletRigidBody)
    {
        throw Error("Cannot set mesh after the rigid body is created");
    }
    _mesh = mesh;
}

void RigidBodySerializer::save(const RigidBody& rigidBody, DataWriter& writer) const
{
    writer.writeDouble("mass", rigidBody.mass());
    writer.writeVector3("linearVelocity", rigidBody.linearVelocity());
    writer.writeVector3("angularVelocity", rigidBody.angularVelocity());
    writer.writeString("mesh", rigidBody.mesh().path().toString());
}

void RigidBodySerializer::load(RigidBody& rigidBody, DataReader& reader, AssetCache& assetCache) const
{
    if (reader.hasMember("mass"))
    {
        rigidBody.setMass(reader.readDouble("mass"));
    }

    if (reader.hasMember("linearVelocity"))
    {
        rigidBody.setLinearVelocity(reader.readVector3("linearVelocity"));
    }

    if (reader.hasMember("angularVelocity"))
    {
        rigidBody.setAngularVelocity(reader.readVector3("angularVelocity"));
    }

    if (reader.hasMember("mesh"))
    {
        std::string meshPath = reader.readString("mesh");
        AssetHandle<Mesh> mesh = assetCache.getHandle<Mesh>(meshPath);

        rigidBody.setMesh(mesh);
    }
}