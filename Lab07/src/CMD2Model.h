#pragma once
#ifndef CMD2MODEL_H
#define CMD2MODEL_h

#include "Texture.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include <vector>
#include <cstdio>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/normal.hpp>

typedef float int3[3];
struct md2_t
{
    int identify;
    int version;

    int skinWidth;
    int skinhHight;
    int frameSize;

    int numSkins;
    int numVerts;
    int numTex;
    int numTri;
    int numCmds;
    int numFrames;

    int ofsSkins;
    int ofsTex;
    int ofsTri;
    int ofsFrames;
    int ofsCmds;
    int ofsEnd;

};

struct vertex_md2
{
    unsigned char v[3];
    unsigned char lightnormalindex;

};

struct frame_md2
{
    float scale[3];
    float translate[3];
    char name[16];
    vertex_md2 verts[1];

};

struct animation_md2
{
    int firstFrame;
    int lastFrame;
    int fps;
};

// status animation
struct animationState
{
    int	startFrame;
    int	endFrame;
    int	fps;
    float currTime;
    float prevTime;
    float interpol;
    int	type;
    int	currFrame;
    int	nextFrame;

};

typedef enum {
    STAND,
    RUN,
    ATTACK,
    PAIN_A,
    PAIN_B,
    PAIN_C,
    JUMP,
    FLIP,
    SALUTE,
    FALLBACK,
    WAVE,
    POINTING,
    CROUCH_STAND,
    CROUCH_WALK,
    CROUCH_ATTACK,
    CROUCH_PAIN,
    CROUCH_DEATH,
    DEATH_FALLBACK,
    DEATH_FALLFORWARD,
    DEATH_FALLBACKSLOW,
    BOOM,

    MAX_ANIMATIONS

} animationType ;

class CMD2Model
{
public:
    CMD2Model();
    CMD2Model(const char* vShader, const char* fShader)
    {
        Shader s(vShader, fShader);
        shader = s;
    }
    //CMD2Model(glm::vec3 pos);
    void LoadModel(const char* sFilename, const char* tFilename);

    void RenderModel(animationState* animState, glm::mat4& proj, glm::mat4& view, glm::vec3 position, float rotation, float direction);

    animationState StartAnimation(animationType type);
    void UpdateAnimation(animationState* animState, float fTimePassed);
    void PauseAnimation();
    void StopAnimation();
    glm::vec3 GetPos() { return position; }
    void setPos(glm::vec3 p) { position = p; }

    static animationState animationList[21];
    Shader shader;
private:
    unsigned int modelVAO, VAO, VBO, EBO, textureId;

    glm::vec3 position;

    std::vector<unsigned int> uiFramesBuffer;

    md2_t header;
    std::vector< std::vector<glm::vec3> > vVertices;
    std::vector <std::vector< int > > vNormals;
    std::vector<int> glCommands;

    std::vector<VertexBuffer> vboFrameVertices;
    VertexBuffer vboTextureCoords;

    std::vector<int> renderModes;
    std::vector<int> numRenderVertices;
};
#endif
