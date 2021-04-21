#ifndef MODEL_H
#define MODEL_H

#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


class Model
{
public:
    // model data
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;
    glm::mat4 globalInverseTransform = {};

    Model() {std::cout << "ERROR::MODEL.CPP::Cant make model object without a path" << std::endl;}

    Model(std::string const& path)
    {
        LoadModel(path);
    }

    // draws the model, and thus all its meshes
    void Draw(Shader& shader, glm::mat4 model);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.

    glm::mat4 to_glm(aiMatrix4x4t<float> m);

    glm::vec3 to_glm(aiVector3t<float> v);

    glm::quat to_glm(aiQuaterniont<float> q);

    void LoadModel(std::string const& path);

    // add transform
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void ProcessNode(aiNode* node, const aiScene* scene, glm::mat4 transform);

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, glm::mat4 transform);

    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif