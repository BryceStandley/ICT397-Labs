#include "Terrain.h"

Terrain::Terrain()
{
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;
    size = 128;
}

Terrain::~Terrain()
{
    delete[] terrainData;
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Terrain::SetDefaults()
{
    //filename = "./res/HeightMaps/height128.raw";
    size = 512;
    scaleX = 1;
    scaleY = 3;
    scaleZ = 1;
    dirt = "./res/textures/dirt/Ground044_1K_Color.jpg";
    dirtNormal = "./res/textures/dirt/Ground044_1K_Normal.jpg";
    grass = "./res/textures/grass/Grass004_1K_Color.jpg";
    grassNormal = "./res/textures/grass/Grass004_1K_Normal.jpg";
    mountain = "./res/textures/mountain/Rock007_1K_Color.jpg";
    mountainNormal = "./res/textures/mountain/Rock007_1K_Normal.jpg";
    snow = "./res/textures/snow/Snow005_1K_Color.jpg";
    snowNormal = "./res/textures/snow/Snow005_1K_Normal.jpg";

}

void Terrain::Init()
{
    SetShader();
    SetDefaults();
    if(filename.empty())
        GenFaultFormation(size, size, 0, 1, 0.3, true);
    else
        LoadHeightField(filename, size);
    GenerateTerrain();
    SetTextures();
}

bool Terrain::LoadHeightField(std::string filename, int size)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file)
    {
        std::cout << "File aint here brother" << std::endl;
        return false;
    }
    if (terrainData)
        delete[] terrainData;

    if (size > 0)
    {
        int nSize = size * size;
        terrainData = new unsigned char[nSize];
    }

    if (terrainData == nullptr)
        return false;

    file.seekg(0, std::ios::end);
    int length = file.tellg();

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(terrainData),length);
    file.close();
    this->size = size;

    return true;
}

void Terrain::SetShader()
{
    std::cout << "Loading Terrain Shaders..." << std::endl;
    shader = new Shader("./res/Shaders/cVert.glsl", "./res/Shaders/cFrag.glsl");
}

void Terrain::setScalingFactor(float xScale, float yScale, float zScale)
{
    scaleX = xScale;
    scaleY = yScale;
    scaleZ = zScale;
}

float Terrain::GetHeight(int xpos, int zpos) {
    if(InBounds(xpos, zpos))
        return ((float)(terrainData[(zpos * size) + xpos]) * scaleY);
    else
        return ((float)(terrainData[(zpos - 1 * size) + xpos]) * scaleY);
}

float Terrain::GetAverageHeight(int xpos, int zpos)
{
    std::vector<float> heights;
    heights.push_back(GetHeight(xpos, zpos) / 10.0f);

    heights.push_back(GetHeight(xpos - 1 , zpos - 1) / 10.0f);
    heights.push_back(GetHeight(xpos, zpos - 1) / 10.0f);
    /*
    heights.push_back(GetHeight(xpos + 1, zpos - 1) / 10.0f);

    heights.push_back(GetHeight(xpos - 1, zpos) / 10.0f);
    heights.push_back(GetHeight(xpos + 1, zpos) / 10.0f);

    heights.push_back(GetHeight(xpos - 1, zpos + 1) / 10.0f);
    heights.push_back(GetHeight(xpos, zpos + 1) / 10.0f);
    heights.push_back(GetHeight(xpos + 1, zpos + 1) / 10.0f);
    */
    float tot = 0.0f;
    for (float h : heights)
    {
        tot += h;
    }

    return tot / heights.size();
}


unsigned char Terrain::GetHeightColor(int xpos, int zpos) {
    if (InBounds(xpos, zpos)) {
        return terrainData[zpos * size + xpos];
    }
    return 1;
}

void Terrain::SetHeightAtPoint(unsigned char height, int xpos, int zpos)
{
    terrainData[(zpos * GetSize()) + xpos] = height;
}

bool Terrain::InBounds(int xpos, int zpos) const
{
    if ((xpos >= 0 && xpos < size * scaleX) && (zpos >= 0 && zpos < size * scaleZ))
        return true;
    else
        return false;
}

int Terrain::GetSize() const
{
    return size;
}

void Terrain::FilterPass(float* startP, int increment, float weight) const
{
    float yprev = *startP; // the starting point in the terrain array
    int j = increment; // must be either +1, -1, +size, or -size
    float k = weight;
    // loop through either
    // one row from left to right if increment = +1, or
    // one row from right to left if increment = -1, or
    // one column from top to bottom if increment = +size, or
    // one column from bottom to top if increment = -size
    for (int i = 1; i < GetSize(); i++) {
        // yi = k yi-1 + (1-k) xi
        *(startP + j) = k * yprev + (1 - k) * (*(startP + j)); //
        yprev = *(startP + j);
        j += increment;
    }
}

void Terrain::AddFilter(float* heights, float weight)
{
    int i;
    //erode left to right, starting from the beginning of each row
    for (i = 0; i < GetSize(); i++)
        FilterPass(&heights[GetSize() * i], 1, weight);
    //erode right to left, starting from the end of each row
    for (i = 0; i < GetSize(); i++)
        FilterPass(&heights[GetSize() * i + GetSize() - 1], -1, weight);
    //erode top to bottom, starting from the beginning of each column
    for (i = 0; i < GetSize(); i++)
        FilterPass(&heights[i], GetSize(), weight);
    //erode from bottom to top, starting from the end of each column
    for (i = 0; i < GetSize(); i++)
        FilterPass(&heights[GetSize() * (GetSize() - 1) + i], -GetSize(), weight);
}

void Terrain::NormaliseTerrain(float* heights) const
{
    float fMin, fMax;
    float fHeight;
    int i;
    fMin = heights[0];
    fMax = heights[0];
    //find the min and max values of the height terrainData
    for (i = 1; i < size * size; i++) {
        if (heights[i] > fMax) fMax = heights[i];
        else if (heights[i] < fMin) fMin = heights[i];
    }
    //find the range of the altitude
    if (fMax <= fMin)
        return;

    fHeight = fMax - fMin;

    //scale the values to a range of 0-255
    for (i = 0; i < size * size; i++)
        heights[i] = ((heights[i] - fMin) / fHeight) * 255.0f;
}

bool Terrain::GenFaultFormation(int iter, int hSize, int minHeight, int maxHeight, float weight, bool random)
{
    int x1, x2, z1, z2;
    float* heights = nullptr;
    int displacement;
    if (hSize <= 0)
        return false;
    if (random) //create truly random map
        srand(time(nullptr));
    // allocate memory for heightfield array
    size = hSize;
    heights = new float[size * size]; //allocate memory
    terrainData = new unsigned char[size * size]; // terrainData is declared in terrain class
    if (heights == nullptr || terrainData == nullptr)
        return false;

    // initialise the heightfield array to all zeros
    for (int i = 0; i < size * size; i++)
        heights[i] = 0.0;
    // generate heightfield
    for (int j = 0; j < iter; j++) {
        //calculate the displacement value for the current iteration
        displacement = maxHeight - ((maxHeight - minHeight) * j) / iter;

        //pick the first random point P1(x1, z1) from the height map
        x1 = (rand() % size);
        z1 = (rand() % size);
        // pick up the second random point P2(x2, z2) and make sure it is
        // different from the first point
        do {
            x2 = (rand() % size);
            z2 = (rand() % size);
        } while (x2 == x1 && z2 == z1);
        //for each point P(x, z) in the field, calculate the new height values
        for (int z = 0; z < size; z++) {
            for (int x = 0; x < size; x++) {
                // determine which side of the line P1P2 the point P lies in
                if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
                    heights[(z * size) + x] += (float)displacement;
                }
            }
        }
        AddFilter(heights, weight);
    }
    // normalise the heightfield
    NormaliseTerrain(heights);
    // copy the float heightfield to terrainData (in unsign char)
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            SetHeightAtPoint((unsigned char)heights[(z * size) + x], x, z);
        }
    }
    // dispose of the temporary array heights
    delete[] heights;
    return true;
}

void Terrain::ModelSetup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, totalData.size() * sizeof(glm::vec3), &totalData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

    //postion attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attributes
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //normal attributes
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);
}

void Terrain::SetTextures()
{
    dirtID = t.TextureFromFile(dirt);
    dirtNormalID = t.TextureFromFile(dirtNormal);

    grassID = t.TextureFromFile(grass);
    grassNormalID = t.TextureFromFile(grassNormal);

    mountainID = t.TextureFromFile(mountain);
    mountainNormalID = t.TextureFromFile(mountainNormal);

    snowID = t.TextureFromFile(snow);
    snowNormalID = t.TextureFromFile(snowNormal);


    shader->use();
    shader->setInt("dirtTexture", 0);
    shader->setInt("dirtNormalTexture", 1);

    shader->setInt("grassTexture", 2);
    shader->setInt("grassNormalTexture", 3);

    shader->setInt("mountainTexture", 4);
    shader->setInt("mountainNormalTexture", 5);

    shader->setInt("snowTexture", 6);
    shader->setInt("snowNormalTexture", 7);

}
void Terrain::SetWireFlag(bool w){ wireFlag = w;}

void Terrain::Render(glm::mat4& proj, glm::mat4& view, glm::vec3& cameraPos)
{
    if (wireFlag)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grassID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, grassNormalID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, dirtID);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, dirtNormalID);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, mountainID);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, mountainNormalID);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, snowID);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, snowNormalID);

    shader->use();
    shader->setMat4("projection", proj);
    shader->setMat4("view", view);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::scale(model, glm::vec3(0.2f)); // scale down terrain
    shader->setMat4("model", model);


    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", 48.0f, 5.0f, 45.3f); //48.0f,1.5f,45.3f
    shader->setVec3("viewPos", cameraPos);


    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);


}

void Terrain::GenerateVertices(Vertex &vert)
{
    for (unsigned int z = 0; z < GetSize(); ++z)
    {
        for (unsigned int x = 0; x < GetSize(); ++x)
        {
            glm::vec3 positions((float)x * scaleX, GetHeight((int)x, (int)z) / 10.0f, (float)z * scaleZ);
            vert.position.push_back(positions);
        }
    }
}

void Terrain::GenerateIndices(std::vector<unsigned int> &indices) const
{
    for (unsigned int z = 0; z < GetSize(); ++z)
    {
        for (unsigned int x = 0; x < GetSize(); ++x)
        {
            if (z + 1 < GetSize())
            {
                indices.push_back((z * GetSize() + x));

                indices.push_back((z * GetSize()) + x + GetSize());
            }
        }
        indices.push_back(0xFFFFFFFF);
    }
}

void Terrain::GenerateColors(Vertex &vert)
{
    float colorVal = 0.0f;

    for (unsigned int z = 0; z < GetSize(); ++z)
    {
        for (unsigned int x = 0; x < GetSize(); ++x)
        {
            colorVal = (float)GetHeightColor((int)x, (int)z) / 255;
            glm::vec3 color(0.0f, colorVal, 0.0f);
            vert.color.push_back(color);
        }
    }
}

void Terrain::GenerateTextures(Vertex &vert) const
{

    for (unsigned int z = 0; z < GetSize(); ++z)
    {
        for (unsigned int x = 0; x < GetSize(); ++x)
        {
            glm::vec3 tex(((float)x / (float)GetSize()) * 5.0f, 0.0f, ((float)z / (float)GetSize()) * 5.0f);
            vert.texture.push_back(tex);
        }
    }
}

void Terrain::GenerateNormals(std::vector<unsigned int> &indices, Vertex &vert) const
{
    for (unsigned int z = 0; z < GetSize(); ++z)
    {
        for (unsigned int x = 0; x < GetSize(); ++x)
        {
            const glm::vec3& west = vert.position[(x > 0 ? x - 1 : 0) + z * GetSize()];
            const glm::vec3& east = vert.position[(x < GetSize() - 1 ? x + 1 : x) + z * GetSize()];

            glm::vec3 slope_x = east - west;

            const glm::vec3& south = vert.position[x + (z > 0 ? z - 1 : 0) * GetSize()];
            const glm::vec3& north = vert.position[x + (z < GetSize() - 1 ? z + 1 : z) * GetSize()];

            glm::vec3 slope_y = north - south;


            glm::vec3 normal = cross(slope_x, slope_y);
            glm::vec3 normalized = glm::normalize(normal);
            vert.normal.push_back(normalized);
        }
    }
}

void Terrain::GenerateTerrain()
{
    GenerateVertices(vertex);
    GenerateColors(vertex);
    GenerateTextures(vertex);

    GenerateIndices(Indices);
    GenerateNormals(Indices, vertex);

    for (unsigned i = 0; i < vertex.position.size(); ++i)
    {
        totalData.push_back(vertex.position[i]);
        totalData.push_back(vertex.color[i]);
        totalData.push_back(vertex.texture[i]);
        totalData.push_back(-vertex.normal[i]);

    }
    ModelSetup();
}

void Terrain::ResetTerrain()
{
    delete[] terrainData;
    terrainData = new unsigned char[size * size];
    totalData.clear();
    vertex.texture.clear();
    vertex.position.clear();
    vertex.color.clear();
    vertex.normal.clear();
    Indices.clear();

    GenFaultFormation(size, size, 0, 1, 0.3, true);
    GenerateTerrain();
}

