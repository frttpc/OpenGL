#pragma once

#include <vector>
#include "glm/glm.hpp"
using namespace std;

namespace CubeData
{
    vector<glm::vec3> positions = {
        // front
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        // back
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        // right
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        // left
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        // top
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        // bottom
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, -1.0)};

    vector<glm::vec3> normals = {
        // front
        glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0),
        // back
        glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, -1.0),
        // right
        glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),
        // left
        glm::vec3(-1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0),
        // top
        glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0),
        // bottom
        glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, -1.0, 0.0)};

    vector<glm::vec2> uvs_myFace(unsigned x = 1, unsigned y = 1)
    {
        vector<glm::vec2> uv = {
            // front
            glm::vec2(1 * x, 1 * y),
            glm::vec2(1 * x, 0 * y),
            glm::vec2(0 * x, 0 * y),
            glm::vec2(0 * x, 1 * y),
            // back
            glm::vec2(1 * x, 1 * y),
            glm::vec2(1 * x, 0 * y),
            glm::vec2(0 * x, 0 * y),
            glm::vec2(0 * x, 1 * y),
            // right
            glm::vec2(1 * x, 1 * y),
            glm::vec2(1 * x, 0 * y),
            glm::vec2(0 * x, 0 * y),
            glm::vec2(0 * x, 1 * y),
            // left
            glm::vec2(1 * x, 1 * y),
            glm::vec2(1 * x, 0 * y),
            glm::vec2(0 * x, 0 * y),
            glm::vec2(0 * x, 1 * y),
            // top
            glm::vec2(1 * x, 1 * y),
            glm::vec2(1 * x, 0 * y),
            glm::vec2(0 * x, 0 * y),
            glm::vec2(0 * x, 1 * y),
            // bottom
            glm::vec2(1 * x, 1 * y),
            glm::vec2(1 * x, 0 * y),
            glm::vec2(0 * x, 0 * y),
            glm::vec2(0 * x, 1 * y),
        };
        return uv;
    }

    vector<glm::vec2> uvs_plane(unsigned x = 1, unsigned y = 1)
    {
        vector<glm::vec2> uv = {
            // front
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y),
            // back
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y),
            // right
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y),
            // left
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y),
            // top
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y),
            // bottom
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y)
            };
        return uv;
    }

    vector<glm::vec2> uvs_chest(unsigned x = 1, unsigned y = 1)
    {
        vector<glm::vec2> uv = {
            // front
            glm::vec2(1.0 * x, 0.5 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.5 * x, 0.0 * y),
            glm::vec2(0.5 * x, 0.5 * y),
            // back
            glm::vec2(1.0 * x, 0.5 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.5 * x, 0.0 * y),
            glm::vec2(0.5 * x, 0.5 * y),
            // right
            glm::vec2(0.5 * x, 0.5 * y),
            glm::vec2(0.5 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.5 * y),
            // left
            glm::vec2(0.5 * x, 0.5 * y),
            glm::vec2(0.5 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.5 * y),
            // top
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.5 * y),
            glm::vec2(0.5 * x, 0.5 * y),
            glm::vec2(0.5 * x, 1.0 * y),
            // bottom
            glm::vec2(1.0 * x, 1.0 * y),
            glm::vec2(1.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 0.0 * y),
            glm::vec2(0.0 * x, 1.0 * y)
        };
        return uv;
    }

    vector<unsigned int> indices = {
        // front
        0,
        1,
        2,
        2,
        3,
        0,
        // back
        4,
        5,
        6,
        6,
        7,
        4,
        // right
        8,
        9,
        10,
        10,
        11,
        8,
        // left
        12,
        13,
        14,
        14,
        15,
        12,
        // top
        16,
        17,
        18,
        18,
        19,
        16,
        // bottom
        20,
        21,
        22,
        22,
        23,
        20,
    };
}