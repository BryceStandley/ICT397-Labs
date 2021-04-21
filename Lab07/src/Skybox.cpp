#include "Skybox.h"


Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVAO);
}

void Skybox::Init()
{

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxVertices), &skyBoxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    cubeFaces.emplace_back("./res/textures/skybox/right.jpg");
    cubeFaces.emplace_back("./res/textures/skybox/left.jpg");
    cubeFaces.emplace_back("./res/textures/skybox/top.jpg");
    cubeFaces.emplace_back("./res/textures/skybox/bottom.jpg");
    cubeFaces.emplace_back("./res/textures/skybox/front.jpg");
    cubeFaces.emplace_back("./res/textures/skybox/back.jpg");


    cubeTexture = loadCubemap(cubeFaces);

    std::cout << "Loading Skybox Shaders..." << std::endl;
    const char* vertexShader = "./res/Shaders/skybox_vert.glsl";
    const char* fragmentShader = "./res/Shaders/skybox_frag.glsl";
    skyShader = std::make_unique<Shader>(vertexShader, fragmentShader);
    skyShader->use();
    skyShader->setInt("skybox", 0);

}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data =
                stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,
                         height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i]
                      << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void Skybox::Draw(const glm::mat4& view, const glm::mat4& projection) const
{
    glDepthFunc(GL_LEQUAL);
    skyShader->use();
    skyShader->setMat4("view", view);
    skyShader->setMat4("projection", projection);

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    //glActiveTexture(GL_TEXTURE0);
    glDepthFunc(GL_LESS); // set depth function back to default

}