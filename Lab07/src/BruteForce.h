#pragma once
#include "Terrain.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/glm.hpp>
#include "GL.h"

class BruteForce : public Terrain
{
public:

    void Render();
    void generateTerrain();
    void modelSetup();
    Terrain::terrainDataStruct t;
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    unsigned int texID = 0, texID2 = 0;
    void resetTerrain();
};
