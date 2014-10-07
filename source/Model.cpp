/*
 * Bael'Zharon's Respite
 * Copyright (C) 2014 Daniel Skorupski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "Model.h"
#include "BinReader.h"
#include "BSP.h"
#include "Core.h"
#include "ResourceCache.h"
#include "Surface.h"
#include "Texture.h"
#include "TextureLookup5.h"

enum ModelFlags
{
    kHasPhysicsBSP = 0x1,
    kHasDrawingBSP = 0x2,
    kHasDegrade = 0x8
};

static vector<TriangleFan> readTriangleFans(BinReader& reader)
{
    uint16_t numTriangleFans = reader.readPackedShort();

    vector<TriangleFan> triangleFans(numTriangleFans);

    for(uint16_t i = 0; i < numTriangleFans; i++)
    {
        uint16_t triangleFanNum = reader.readShort();
        assert(triangleFanNum == i);

        read(reader, triangleFans[i]);
    }

    return triangleFans;
}

Model::Model(uint32_t id, const void* data, size_t size) : ResourceImpl{id}, needsDepthSort{false}
{
    BinReader reader(data, size);

    uint32_t resourceId = reader.readInt();
    assert(resourceId == id);

    uint32_t flags = reader.readInt();
    assert(flags == 0x2 || flags == 0x3 || flags == 0xA || flags == 0xB);

    uint8_t numSurfaces = reader.readByte();
    surfaces.resize(numSurfaces);

    for(ResourcePtr& surface : surfaces)
    {
        uint32_t surfaceId = reader.readInt();
        surface = Core::get().resourceCache().get(surfaceId);

        bool hasAlpha = surface->cast<Surface>()
            .textureLookup5->cast<TextureLookup5>()
            .texture->cast<Texture>()
            .image.hasAlpha();
        needsDepthSort = needsDepthSort || hasAlpha;
    }

    uint32_t one = reader.readInt();
    assert(one == 1);

    uint16_t numVertices = reader.readShort();
    vertices.resize(numVertices);

    uint16_t flags2 = reader.readShort();
    assert(flags2 == 0x0000 || flags2 == 0x8000);

    for(uint16_t i = 0; i < numVertices; i++)
    {
        uint16_t vertexNum = reader.readShort();
        assert(vertexNum == i);

        read(reader, vertices[i]);
    }

    if(flags & kHasPhysicsBSP)
    {
        hitTriangleFans = readTriangleFans(reader);
        read(reader, hitTree, BSPTreeType::kPhysics);
    }

    // sort center
    /*x*/ reader.readFloat();
    /*y*/ reader.readFloat();
    /*z*/ reader.readFloat();

    if(flags & kHasDrawingBSP)
    {
        triangleFans = readTriangleFans(reader);

        unique_ptr<BSPNode> drawingBSP;
        read(reader, drawingBSP, BSPTreeType::kDrawing);
    }

    if(flags & kHasDegrade)
    {
        // Seems to be a reference to an 0x11 file? No idea what these are!
        reader.readInt();
    }

    reader.assertEnd();
}

Model::~Model()
{}
