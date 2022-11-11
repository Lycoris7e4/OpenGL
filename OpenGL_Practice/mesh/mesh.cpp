#include "mesh.h"
#include <../shader/shader.h>

Mesh::Mesh(std::vector<MESH::Vertex> vertices, std::vector<unsigned int> indices, std::vector<MESH::Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::Draw(ShaderProgram *shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        shader->setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    vertex.open();
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    vertex.close();

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
    vertex.initVAO();
    vertex.open();

    vertex.setBuffer(&vertices[0], vertices.size() * sizeof(MESH::Vertex));
    vertex.setIndex(&indices[0], indices.size() * sizeof(unsigned int));

    vertex.setAttrib(0, 3, sizeof(MESH::Vertex), (void*)0);
    vertex.setAttrib(1, 3, sizeof(MESH::Vertex), (void*)offsetof(MESH::Vertex, Normal));
    vertex.setAttrib(2, 2, sizeof(MESH::Vertex), (void*)offsetof(MESH::Vertex, TexCoords));
    vertex.setAttrib(3, 3, sizeof(MESH::Vertex), (void*)offsetof(MESH::Vertex, Tangent));
    vertex.setAttrib(4, 3, sizeof(MESH::Vertex), (void*)offsetof(MESH::Vertex, Bitangent));
    vertex.setAttribI(5, 4, sizeof(MESH::Vertex), (void*)offsetof(MESH::Vertex, m_BoneIDs));
    vertex.setAttrib(6, 4, sizeof(MESH::Vertex), (void*)offsetof(MESH::Vertex, m_Weights));

    vertex.close();
}
