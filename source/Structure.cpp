#include "Structure.h"
#include "BlobReader.h"
#include "Core.h"
#include "ResourceCache.h"
#include "StructureGeom.h"

Structure::Structure(const void* data, size_t size)
{
    BlobReader reader(data, size);

    auto resourceId = reader.read<uint32_t>();
    // 0x1 above ground
    // 0x2 has objects
    // 0x4 unknown
    // 0x8 unknown, extra 4 bytes
    auto flags = reader.read<uint32_t>();
    assert(flags <= 0xF);

    auto resourceId2 = reader.read<uint32_t>();
    assert(resourceId2 == resourceId);

    auto numTextures = reader.read<uint8_t>();
    _textures.resize(numTextures);

    auto numConnections = reader.read<uint8_t>();
    auto numVisible = reader.read<uint16_t>();

    for(auto& texture : _textures)
    {
        auto textureId = reader.read<uint16_t>();
        texture = Core::get().resourceCache().get(0x08000000 | textureId);
    }

    auto geometryId = reader.read<uint16_t>();
    _geometry = Core::get().resourceCache().get(0x0D000000 | geometryId);

    reader.read<uint16_t>(); // structure index (resourceId & 0x0000FFFF)

    _position.x = reader.read<float>();
    _position.y = reader.read<float>();
    _position.z = reader.read<float>();

    _rotation.w = reader.read<float>();
    _rotation.x = reader.read<float>();
    _rotation.y = reader.read<float>();
    _rotation.z = reader.read<float>();

    for(auto ci = 0u; ci < numConnections; ci++)
    {
        reader.read<uint16_t>();
        reader.read<uint16_t>();
        reader.read<uint16_t>(); // structure index
        reader.read<uint16_t>();
    }

    for(auto vi = 0u; vi < numVisible; vi++)
    {
        reader.read<uint16_t>(); // structure index
    }

    if(flags & 2)
    {
        auto numObjects = reader.read<uint32_t>();
        _objects.resize(numObjects);

        for(auto& object : _objects)
        {
            auto modelId = reader.read<uint32_t>();
            object.resource = Core::get().resourceCache().get(modelId);

            object.position.x = reader.read<float>();
            object.position.y = reader.read<float>();
            object.position.z = reader.read<float>();

            object.rotation.w = reader.read<float>();
            object.rotation.x = reader.read<float>();
            object.rotation.y = reader.read<float>();
            object.rotation.z = reader.read<float>();
        }
    }

    if(flags & 8)
    {
        // I'm not sure this is where this is supposed to be
        reader.read<uint32_t>();
    }

    reader.assertEnd();
}

Structure::Structure(Structure&& other)
{
    _textures = move(other._textures);
    _objects = move(other._objects);
    _geometry = move(other._geometry);
}

const Vec3& Structure::position() const
{
    return _position;
}

const Quat& Structure::rotation() const
{
    return _rotation;
}

const vector<ResourcePtr>& Structure::textures() const
{
    return _textures;
}

const vector<Object>& Structure::objects() const
{
    return _objects;
}

const StructureGeom& Structure::geometry() const
{
    return _geometry->cast<StructureGeom>();
}