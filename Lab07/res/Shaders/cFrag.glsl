#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;
in float height;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;


uniform sampler2D dirtTexture; //dirt
uniform sampler2D dirtNormalTexture; //dirt

uniform sampler2D grassTexture; //grass
uniform sampler2D grassNormalTexture; //grass

uniform sampler2D mountainTexture; //mountain
uniform sampler2D mountainNormalTexture; //mountain

uniform sampler2D snowTexture; //snow
uniform sampler2D snowNormalTexture; //detail

vec4 dirt = texture(dirtTexture, texCoord);
vec4 dirtDetail = texture(dirtNormalTexture, texCoord);

vec4 grass = texture(grassTexture, texCoord);
vec4 grassDetail = texture(grassNormalTexture, texCoord);

vec4 mountain = texture(mountainTexture, texCoord);
vec4 mountainDetail = texture(mountainNormalTexture, texCoord);

vec4 snow = texture(snowTexture, texCoord);
vec4 snowDetail = texture(snowNormalTexture, texCoord);

vec4 detail;


int dirtStart = 40;
int grassStart = 75;
int mountainStart = 150;
int snowStart = 200;

void main()
{
    vec4 finalColor;

    if(height > snowStart)
    {
        finalColor = snow;
        detail = snowDetail;
    }
    else if (height > mountainStart)
    {
        float blend = (height - mountainStart) / (snowStart - mountainStart);
        finalColor = mix(mountain, snow, blend);
        detail = mix(mountainDetail, snowDetail, blend);
    }
    else if (height > grassStart)
    {
        float blend = (height - grassStart) / (mountainStart - grassStart);
        finalColor = mix(grass, mountain, blend);
        detail = mix(grassDetail, mountainDetail, blend);
    }
    else if (height > dirtStart)
    {
        float blend = (height - dirtStart) / (grassStart - dirtStart);
        finalColor = mix(dirt, grass, blend);
        detail = mix(dirtDetail, grassDetail, blend);
    }
    else
    {
        finalColor = dirt;
        detail = dirtDetail;
    }


    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.05;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular);
    //FragColor = FragColor * vec4(result, 1.0f);
    FragColor = finalColor * vec4(result, 1.0);
    //FragColor = (finalColor * detail) * vec4(result, 1.0f);
    //FragColor = vec4(norm*0.5+0.5, 1.0);

}