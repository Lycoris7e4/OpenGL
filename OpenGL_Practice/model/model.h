#ifndef  MODEL_H_
#define MODEL_H_

#include <string>
#include <vector>

#include "../mesh/mesh.h"

class ShaderProgram;
class Mesh;

struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;

enum aiTextureType;

class Model {
public:
    Model(const std::string& path, bool gamma = false);
    void Draw(ShaderProgram *shader);

private:
    std::vector<MESH::Texture> textures_loaded;
    std::vector<Mesh*> meshes;
    std::string directory;
    bool gammaCorrection;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<MESH::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

#endif // MODEL_H_

