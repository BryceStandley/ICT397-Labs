#include "BruteForce.h"

void BruteForce::generateTerrain()
{
    float colorVal = 0.0f;
    t.texCoords.emplace_back(0,0);
    for (unsigned int z = 0; z < GetSize(); ++z)
    {
        for (unsigned int x = 0; x < GetSize(); ++x)
        {
            colorVal = (float)GetHeightColor((int)x, (int)z) / 255;

            t.vertex.emplace_back((float)x *scaleX, GetHeight((int)x, (int)z) / 10.0f, (float)z * scaleZ); //position values
            t.vertex.emplace_back(colorVal, colorVal, colorVal); // color values
            glm::vec2 tex(((float)x / (float)GetSize()) * 50.0f, ((float)z / (float)GetSize()) * 100.0f);
            t.vertex.emplace_back(tex.x, 0.0f, tex.y);

            if (z + 1 < GetSize())
            {
                t.indices.emplace_back(((float)z * (float)GetSize() + (float)x));

                t.indices.emplace_back(((float)z * (float)GetSize()) + (float)x + (float)GetSize());
            }
        }

        t.indices.emplace_back(0xFFFFFFFFFF);
    }
}



void BruteForce::modelSetup()
{
    unsigned int VBO2;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, t.vertex.size() * sizeof(glm::vec3), &t.vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, t.indices.size() * sizeof(unsigned int), &t.indices[0], GL_STATIC_DRAW);

    //postion attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attributes
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

void BruteForce::Render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, t.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void BruteForce::resetTerrain()
{
    t.vertex.clear();
    t.indices.clear();
    t.texCoords.clear();
}