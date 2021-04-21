#include "CMD2Model.h"
CMD2Model::CMD2Model(){}

animationState CMD2Model::animationList[ 21 ] =
        {
                // first, last, fps
                {   0,  39,  9 },	// STAND
                {  40,  45, 10 },	// RUN
                {  46,  53, 10 },	// ATTACK
                {  54,  57,  7 },	// PAIN_A
                {  58,  61,  7 },	// PAIN_B
                {  62,  65,  7 },	// PAIN_C
                {  66,  71,  7 },	// JUMP
                {  72,  83,  7 },	// FLIP
                {  84,  94,  7 },	// SALUTE
                {  95, 111, 10 },	// FALLBACK
                { 112, 122,  7 },	// WAVE
                { 123, 134,  6 },	// POINTIING
                { 135, 153, 10 },	// CROUCH_STAND
                { 154, 159,  7 },	// CROUCH_WALK
                { 160, 168, 10 },	// CROUCH_ATTACK
                { 196, 172,  7 },	// CROUCH_PAIN
                { 173, 177,  5 },	// CROUCH_DEATH
                { 178, 183,  7 },	// DEATH_FALLBACK
                { 184, 189,  7 },	// DEATH_FALLFORWARD
                { 190, 197,  7 },	// DEATH_FALLBACKSLOW
                { 198, 198,  5 },	// BOOM
        };

std::string sMD2AnimationNames[MAX_ANIMATIONS] =
        {
                "Stand",
                "Run",
                "Attack",
                "Pain A",
                "Pain B",
                "Pain C",
                "Jump",
                "Flip",
                "Salute",
                "Fallback",
                "Wave",
                "Pointing",
                "Crouch Stand",
                "Crouch Walk",
                "Crouch Attack",
                "Crouch Pain",
                "Crouch Death",
                "Death Fallback",
                "Death Fall Forward",
                "Death Fallback Slow",
                "Boom"
        };
int3 anorms[162] =
        {
                {-0.525731, 0.000000, 0.850651},
                { -0.442863, 0.238856, 0.864188 },
                { -0.295242, 0.000000, 0.955423 },
                { -0.309017, 0.500000, 0.809017 },
                { -0.162460, 0.262866, 0.951056 },
                { 0.000000, 0.000000, 1.000000 },
                { 0.000000, 0.850651, 0.525731 },
                { -0.147621, 0.716567, 0.681718 },
                { 0.147621, 0.716567, 0.681718 },
                { 0.000000, 0.525731, 0.850651 },
                { 0.309017, 0.500000, 0.809017 },
                { 0.525731, 0.000000, 0.850651 },
                { 0.295242, 0.000000, 0.955423 },
                { 0.442863, 0.238856, 0.864188 },
                { 0.162460, 0.262866, 0.951056 },
                { -0.681718, 0.147621, 0.716567 },
                { -0.809017, 0.309017, 0.500000 },
                { -0.587785, 0.425325, 0.688191 },
                { -0.850651, 0.525731, 0.000000 },
                { -0.864188, 0.442863, 0.238856 },
                { -0.716567, 0.681718, 0.147621 },
                { -0.688191, 0.587785, 0.425325 },
                { -0.500000, 0.809017, 0.309017 },
                { -0.238856, 0.864188, 0.442863 },
                { -0.425325, 0.688191, 0.587785 },
                { -0.716567, 0.681718, -0.147621 },
                { -0.500000, 0.809017, -0.309017 },
                { -0.525731, 0.850651, 0.000000 },
                { 0.000000, 0.850651, -0.525731 },
                { -0.238856, 0.864188, -0.442863 },
                { 0.000000, 0.955423, -0.295242 },
                { -0.262866, 0.951056, -0.162460 },
                { 0.000000, 1.000000, 0.000000 },
                { 0.000000, 0.955423, 0.295242 },
                { -0.262866, 0.951056, 0.162460 },
                { 0.238856, 0.864188, 0.442863 },
                { 0.262866, 0.951056, 0.162460 },
                { 0.500000, 0.809017, 0.309017 },
                { 0.238856, 0.864188, -0.442863 },
                { 0.262866, 0.951056, -0.162460 },
                { 0.500000, 0.809017, -0.309017 },
                { 0.850651, 0.525731, 0.000000 },
                { 0.716567, 0.681718, 0.147621 },
                { 0.716567, 0.681718, -0.147621 },
                { 0.525731, 0.850651, 0.000000 },
                { 0.425325, 0.688191, 0.587785 },
                { 0.864188, 0.442863, 0.238856 },
                { 0.688191, 0.587785, 0.425325 },
                { 0.809017, 0.309017, 0.500000 },
                { 0.681718, 0.147621, 0.716567 },
                { 0.587785, 0.425325, 0.688191 },
                { 0.955423, 0.295242, 0.000000 },
                { 1.000000, 0.000000, 0.000000 },
                { 0.951056, 0.162460, 0.262866 },
                { 0.850651, -0.525731, 0.000000 },
                { 0.955423, -0.295242, 0.000000 },
                { 0.864188, -0.442863, 0.238856 },
                { 0.951056, -0.162460, 0.262866 },
                { 0.809017, -0.309017, 0.500000 },
                { 0.681718, -0.147621, 0.716567 },
                { 0.850651, 0.000000, 0.525731 },
                { 0.864188, 0.442863, -0.238856 },
                { 0.809017, 0.309017, -0.500000 },
                { 0.951056, 0.162460, -0.262866 },
                { 0.525731, 0.000000, -0.850651 },
                { 0.681718, 0.147621, -0.716567 },
                { 0.681718, -0.147621, -0.716567 },
                { 0.850651, 0.000000, -0.525731 },
                { 0.809017, -0.309017, -0.500000 },
                { 0.864188, -0.442863, -0.238856 },
                { 0.951056, -0.162460, -0.262866 },
                { 0.147621, 0.716567, -0.681718 },
                { 0.309017, 0.500000, -0.809017 },
                { 0.425325, 0.688191, -0.587785 },
                { 0.442863, 0.238856, -0.864188 },
                { 0.587785, 0.425325, -0.688191 },
                { 0.688191, 0.587785, -0.425325 },
                { -0.147621, 0.716567, -0.681718 },
                { -0.309017, 0.500000, -0.809017 },
                { 0.000000, 0.525731, -0.850651 },
                { -0.525731, 0.000000, -0.850651 },
                { -0.442863, 0.238856, -0.864188 },
                { -0.295242, 0.000000, -0.955423 },
                { -0.162460, 0.262866, -0.951056 },
                { 0.000000, 0.000000, -1.000000 },
                { 0.295242, 0.000000, -0.955423 },
                { 0.162460, 0.262866, -0.951056 },
                { -0.442863, -0.238856, -0.864188 },
                { -0.309017, -0.500000, -0.809017 },
                { -0.162460, -0.262866, -0.951056 },
                { 0.000000, -0.850651, -0.525731 },
                { -0.147621, -0.716567, -0.681718 },
                { 0.147621, -0.716567, -0.681718 },
                { 0.000000, -0.525731, -0.850651 },
                { 0.309017, -0.500000, -0.809017 },
                { 0.442863, -0.238856, -0.864188 },
                { 0.162460, -0.262866, -0.951056 },
                { 0.238856, -0.864188, -0.442863 },
                { 0.500000, -0.809017, -0.309017 },
                { 0.425325, -0.688191, -0.587785 },
                { 0.716567, -0.681718, -0.147621 },
                { 0.688191, -0.587785, -0.425325 },
                { 0.587785, -0.425325, -0.688191 },
                { 0.000000, -0.955423, -0.295242 },
                { 0.000000, -1.000000, 0.000000 },
                { 0.262866, -0.951056, -0.162460 },
                { 0.000000, -0.850651, 0.525731 },
                { 0.000000, -0.955423, 0.295242 },
                { 0.238856, -0.864188, 0.442863 },
                { 0.262866, -0.951056, 0.162460 },
                { 0.500000, -0.809017, 0.309017 },
                { 0.716567, -0.681718, 0.147621 },
                { 0.525731, -0.850651, 0.000000 },
                { -0.238856, -0.864188, -0.442863 },
                { -0.500000, -0.809017, -0.309017 },
                { -0.262866, -0.951056, -0.162460 },
                { -0.850651, -0.525731, 0.000000 },
                { -0.716567, -0.681718, -0.147621 },
                { -0.716567, -0.681718, 0.147621 },
                { -0.525731, -0.850651, 0.000000 },
                { -0.500000, -0.809017, 0.309017 },
                { -0.238856, -0.864188, 0.442863 },
                { -0.262866, -0.951056, 0.162460 },
                { -0.864188, -0.442863, 0.238856 },
                { -0.809017, -0.309017, 0.500000 },
                { -0.688191, -0.587785, 0.425325 },
                { -0.681718, -0.147621, 0.716567 },
                { -0.442863, -0.238856, 0.864188 },
                { -0.587785, -0.425325, 0.688191 },
                { -0.309017, -0.500000, 0.809017 },
                { -0.147621, -0.716567, 0.681718 },
                { -0.425325, -0.688191, 0.587785 },
                { -0.162460, -0.262866, 0.951056 },
                { 0.442863, -0.238856, 0.864188 },
                { 0.162460, -0.262866, 0.951056 },
                { 0.309017, -0.500000, 0.809017 },
                { 0.147621, -0.716567, 0.681718 },
                { 0.000000, -0.525731, 0.850651 },
                { 0.425325, -0.688191, 0.587785 },
                { 0.587785, -0.425325, 0.688191 },
                { 0.688191, -0.587785, 0.425325 },
                { -0.955423, 0.295242, 0.000000 },
                { -0.951056, 0.162460, 0.262866 },
                { -1.000000, 0.000000, 0.000000 },
                { -0.850651, 0.000000, 0.525731 },
                { -0.955423, -0.295242, 0.000000 },
                { -0.951056, -0.162460, 0.262866 },
                { -0.864188, 0.442863, -0.238856 },
                { -0.951056, 0.162460, -0.262866 },
                { -0.809017, 0.309017, -0.500000 },
                { -0.864188, -0.442863, -0.238856 },
                { -0.951056, -0.162460, -0.262866 },
                { -0.809017, -0.309017, -0.500000 },
                { -0.681718, 0.147621, -0.716567 },
                { -0.681718, -0.147621, -0.716567 },
                { -0.850651, 0.000000, -0.525731 },
                { -0.688191, 0.587785, -0.425325 },
                { -0.587785, 0.425325, -0.688191 },
                { -0.425325, 0.688191, -0.587785 },
                { -0.425325, -0.688191, -0.587785 },
                { -0.587785, -0.425325, -0.688191 },
                { -0.688191, -0.587785, -0.425325 } };

void CMD2Model::LoadModel(const char* sFilename, const char* tFilename)
{
    FILE* fp;
    errno_t err;

    /*std::fstream fs;
    fs.open(sFilename, std::fstream::in | std::fstream::out | std::fstream::app);
    if(fs.fail())
    {
        std::cout << "ERROR OPENING FILE -> " << sFilename << std::endl;
    }*/
    fp = fopen(sFilename, "rb");
    if (fp == nullptr)
    {
        std::cout << "ERROR OPENING FILE -> " << sFilename << std::endl;
    }
    else
    {
        //std::cout << "DEBUG - 1" << std::endl;
        fread(&header, sizeof(md2_t), 1, fp);

        char* buffer = new char[header.numFrames * header.frameSize];
        fseek(fp, header.ofsFrames, SEEK_SET);
        fread(buffer, sizeof(char), header.numFrames * header.frameSize, fp);

        //std::cout << "DEBUG - 2" << std::endl;
        vVertices.resize(header.numFrames, std::vector<glm::vec3>(header.numVerts));
        vNormals.resize(header.numFrames, std::vector<int>(header.numVerts));

        for (int i = 0; i < header.numFrames; i++)
        {
            frame_md2* frame_ptr = (frame_md2*)&buffer[header.frameSize * i];

            for (int j = 0; j < header.numVerts; j++)
            {
                vVertices[i][j].x = frame_ptr->translate[0] + (float(frame_ptr->verts[j].v[0]) * frame_ptr->scale[0]);
                vVertices[i][j].y = frame_ptr->translate[1] + (float(frame_ptr->verts[j].v[1]) * frame_ptr->scale[1]);
                vVertices[i][j].z = frame_ptr->translate[2] + (float(frame_ptr->verts[j].v[2]) * frame_ptr->scale[2]);

                vNormals[i][j] = frame_ptr->verts[j].lightnormalindex;
            }
        }
        //std::cout << "DEBUG - 3" << std::endl;
        glCommands.resize(header.numCmds);
        fseek(fp, header.ofsCmds, SEEK_SET);
        fread(&glCommands[0], sizeof(int), header.numCmds, fp);

        int i = 0;
        int iTotalVertices = 0;

        //std::cout << "DEBUG - 4" << std::endl;
        vboFrameVertices.resize(header.numFrames);
        for (int i = 0; i < header.numFrames; i++)
        {
            vboFrameVertices[i].CreateVertexBuffer();
        }
        vboTextureCoords.CreateVertexBuffer();
        int x = 0;
        while (true)
        {
            x++;
            //std::cout << "DEBUG - 5." << x << std::endl;
            int action = glCommands[i];
            if (action == 0)
                break;

            int renderMode = action < 0 ? GL_TRIANGLE_FAN : GL_TRIANGLE_STRIP;
            int numVertices = action < 0 ? -action : action;
            i++;

            renderModes.push_back(renderMode);
            numRenderVertices.push_back(numVertices);

            for (int j = 0; j < numVertices; j++)
            {
                float s = *((float*)(&glCommands[i++]));
                float t = *((float*)(&glCommands[i++]));
                t = 1.0f - t;
                int vi = glCommands[i++];

                vboTextureCoords.AddData(&s, 4);
                vboTextureCoords.AddData(&t, 4);

                for (int k = 0; k < header.numFrames; k++)
                {
                    vboFrameVertices[k].AddData(&vVertices[k][vi], 12);
                    vboFrameVertices[k].AddData(&anorms[vNormals[k][vi]], 12);
                }
            }
        }

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        for (int i = 0; i < header.numFrames; i++)
        {
            vboFrameVertices[i].BindVBO();
            vboFrameVertices[i].UploadDataToGPU(GL_STATIC_DRAW);
        }

        vboFrameVertices[0].BindVBO();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));

        vboTextureCoords.BindVBO();
        vboTextureCoords.UploadDataToGPU(GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
        //std::cout << "DEBUG - 6" << std::endl;

        TextureLoader loader;
        textureId = loader.TextureFromFile(tFilename);


        //std::cout << "DEBUG - 7" << std::endl;
    }
}


void CMD2Model::RenderModel(animationState* animState, glm::mat4& proj, glm::mat4& view, glm::vec3 position, float rotation, float direction)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    //std::cout << "DEBUG - 10.1" << std::endl;
    shader.use();
    shader.setInt("texture0", 0);
    shader.setMat4("projection", proj);
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, rotation, glm::vec3(1, 0, 0));
    model = glm::rotate(model, direction, glm::vec3(0, 0, 1));
    shader.setMat4("model", model);
    shader.setMat4("normal", model);

    glBindVertexArray(VAO);
    //std::cout << "DEBUG - 10.2" << std::endl;
    int iTotalOffset = 0;

    if(animState == NULL)
    {
        glEnableVertexAttribArray(0);
        vboFrameVertices[0].BindVBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);
        shader.setFloat("fInterpolation", -1.0f);
        //std::cout << "DEBUG - 10.3" << std::endl;
        for (int i = 0; i < renderModes.size(); i++)
        {
            //std::cout << "DEBUG - 10.4." << i << std::endl;
            glDrawArrays(renderModes[i], iTotalOffset, numRenderVertices[i]);
            iTotalOffset += numRenderVertices[i];
        }
    }
    else
    {
        glEnableVertexAttribArray(0);
        vboFrameVertices[animState->currFrame].BindVBO();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(3);
        vboFrameVertices[animState->nextFrame].BindVBO();
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(2);
        vboFrameVertices[animState->currFrame].BindVBO();
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

        glEnableVertexAttribArray(4);
        vboFrameVertices[animState->nextFrame].BindVBO();
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);

        shader.setFloat("fInterpolation", animState->interpol);
        //std::cout << "RENDER SIZE - " << renderModes.size() << std::endl;
        for (int i = 0; i < renderModes.size(); i++)
        {
            //std::cout << "DEBUG - 10.5." << i << std::endl;
            glDrawArrays(renderModes[i], iTotalOffset, numRenderVertices[i]);
            iTotalOffset += numRenderVertices[i];
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

animationState CMD2Model::StartAnimation(animationType type)
{
    animationState res;
    res.startFrame = animationList[type].startFrame;
    res.endFrame = animationList[type].endFrame;
    res.currFrame = animationList[type].startFrame;
    res.nextFrame = animationList[type].startFrame + 1;

    res.fps = animationList[type].fps;
    res.type = type;

    res.currTime = 0.0f;
    res.prevTime = 0.0f;

    res.interpol = 0.0f;

    return res;
}

void CMD2Model::UpdateAnimation(animationState* animState, float fTimePassed)
{
    animState->currTime += fTimePassed;

    if(animState->currTime - animState->prevTime > (1.0f / float(animState->fps)))
    {
        animState->prevTime = animState->currTime;

        animState->currFrame = animState->nextFrame;
        animState->nextFrame++;
        if(animState->nextFrame > animState->endFrame)
            animState->nextFrame = animState->startFrame;
    }

    animState->interpol = float(animState->fps) * (animState->currTime - animState->prevTime);
}