#include <aw/graphics/core/vertex.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
VertexLayout<3> Vertex::Layout = {
    VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), vOffsetof(Vertex, position)},
    VertexAttribute{1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), vOffsetof(Vertex, normal)},
    VertexAttribute{3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), vOffsetof(Vertex, texCoord)},
};

VertexLayout<1> VertexPos::Layout = {
    VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPos), vOffsetof(VertexPos, position)},
};

VertexLayout<3> VertexPosNormalColor::Layout = {
    VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormalColor), vOffsetof(VertexPosNormalColor, position)},
    VertexAttribute{1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormalColor), vOffsetof(VertexPosNormalColor, normal)},
    VertexAttribute{2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormalColor), vOffsetof(VertexPosNormalColor, color)},
};

VertexLayout<2> VertexPosTex::Layout = {
    VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), vOffsetof(VertexPosTex, position)},
    VertexAttribute{3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), vOffsetof(VertexPosTex, texCoord)},
};

VertexLayout<2> VertexPosColor::Layout = {
    VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), vOffsetof(VertexPosColor, position)},
    VertexAttribute{2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), vOffsetof(VertexPosColor, color)},
};

VertexLayout<5> VertexBones::Layout = {
    VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBones), vOffsetof(VertexBones, position)},
    VertexAttribute{1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBones), vOffsetof(VertexBones, normal)},
    VertexAttribute{3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexBones), vOffsetof(VertexBones, texCoord)},
    VertexAttribute{4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBones), vOffsetof(VertexBones, boneIds)},
    VertexAttribute{5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBones), vOffsetof(VertexBones, boneWeights)},
};
} // namespace aw
