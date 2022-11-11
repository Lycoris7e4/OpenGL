#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "../vertex/vertex.h"

#define MAX_BONE_INFLUENCE 4

class ShaderProgram;

namespace MESH {
    struct Vertex;
    struct Texture;
}

class Mesh {
public:
    std::vector<MESH::Vertex>       vertices;
    std::vector<unsigned int>       indices;
    std::vector<MESH::Texture>      textures;
    Vertex vertex;

    Mesh(std::vector<MESH::Vertex> vertices, std::vector<unsigned int> indices, std::vector<MESH::Texture> textures);
    void Draw(ShaderProgram *shaderProgram);

private:
    void setupMesh();
};

namespace MESH {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };
}

#endif