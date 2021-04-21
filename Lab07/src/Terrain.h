#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct Vertex
{
    std::vector<glm::vec3> position = {};
    std::vector<glm::vec3> color = {};
    std::vector<glm::vec3> texture = {};
    std::vector<glm::vec3> normal = {};
};

class Terrain
{

protected:
    unsigned char* terrainData; //data of the heightfield
    float scaleX;
    float scaleY;
    float scaleZ;
    std::string filename;
    std::string dirt, dirtNormal, grass, grassNormal, mountain, mountainNormal, snow, snowNormal;

private:
    int size; //the size of the heightfield along x and z - power of 2
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    unsigned int dirtID = 0, dirtNormalID = 0, grassID = 0, grassNormalID = 0, mountainID = 0, mountainNormalID = 0,
        snowID = 0, snowNormalID = 0;
    Shader* shader = nullptr;
    bool wireFlag = false;
    std::vector<unsigned int> Indices = {};
    Vertex vertex{};
    std::vector<glm::vec3> totalData = {};
    TextureLoader t;

public:


    Terrain();
    ~Terrain();

    void Init();
    void Render(glm::mat4& proj, glm::mat4& view, glm::vec3& cameraPos);
    void SetShader();
    bool LoadHeightField(std::string filename, int size);
    void setScalingFactor(float xScale, float yScale, float zScale);
    int GetSize() const;
    float GetAverageHeight(int xpos, int zpos);
    float GetHeight(int xpos, int zpos);
    unsigned char GetHeightColor(int xpos, int zpos);
    bool InBounds(int x, int y) const;
    void GenerateTerrain();
    void ModelSetup();
    void SetTextures();
    void SetDefaults();
    bool GenFaultFormation(int iter, int hSize, int minHeight, int maxHeight, float weight, bool random);
    void NormaliseTerrain(float* heights) const;
    void FilterPass(float* startP, int increment, float weight) const;
    void AddFilter(float* heights, float weight);
    void SetHeightAtPoint(unsigned char height, int xpos, int zpos);
    void ResetTerrain();
    void SetWireFlag(bool w);

    void GenerateVertices(Vertex &vert);
    void GenerateIndices(std::vector<unsigned int> &indices) const;
    void GenerateColors(Vertex &vert);
    void GenerateTextures(Vertex &vert) const;
    void GenerateNormals(std::vector<unsigned int> &indices, Vertex &vert) const;
};

