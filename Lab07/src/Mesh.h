#ifndef MESH_H
#define MESH_H

#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include <string>
#include <vector>

struct Vert {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    // mesh Data
    std::vector<Vert>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    glm::mat4 transform;
    unsigned int VAO;

    // constructor
    Mesh(std::vector<Vert> vert, std::vector<unsigned int> indi, std::vector<Texture> text, glm::mat4 &transf)
    {
        this->vertices = vert;
        this->indices = indi;
        this->textures = text;
        this->transform = transf;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        SetupMesh();
    }
    // render the mesh
    void Draw(Shader& shader);

private:
    // Render bufferes
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void SetupMesh();
};

#endif