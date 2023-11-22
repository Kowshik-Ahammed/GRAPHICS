//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "sphere.h"
#include "sphere2.h"
#include "directionLight.h"
#include "spotLight.h"


#include "cube.h"
#include "curve.h"
#include "octagon.h"
#include "stb_image.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 70.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);



int noOfPointLights = 12;

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(25.0f,  30.0f,  13.0f),
    glm::vec3(-23.0f,  30.0f,  13.0f),
    glm::vec3(-23.0f,  30.0f,  25.0f),
    glm::vec3(-23.0f,  30.0f,  40.0f),
     glm::vec3(25.0f,  30.0f,  25.0f),


     glm::vec3(25.0f,  30.0f,  -15.0f),
     glm::vec3(25.0f,  30.0f, - 19.0f),
     glm::vec3(0.0f,  13.0f,  15.0f),
     glm::vec3(-25.0f,  30.0f,  -30.0f),
     glm::vec3(-25.0f,  30.0f, - 35.0f),

      glm::vec3(-10.0f,  8.0f,  22.0f),
       glm::vec3(10.0f,  8.0f,  22.0f),

     /*glm::vec3(25.0f,  20.0f,  85.0f),
     glm::vec3(25.0f,  20.0f,  95.0f),
     glm::vec3(25.0f,  20.0f,  105.0f),
     glm::vec3(25.0f, 20.0f,  115.0f),
     glm::vec3(25.0f,  20.0f,  125.0f),*/







};

glm::vec3 spotLightPositions[] = {
    glm::vec3(0.0f,  50.0f,  -10.0f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    1     // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f,//k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f,//k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f,//k_q
    4       // light number
);

PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    5      // light number
);

//new light

PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    6      // light number
);

PointLight pointlight7(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    7       // light number
);
PointLight pointlight8(

    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number
);
PointLight pointlight9(

    pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    9       // light number
);

PointLight pointlight10(

    pointLightPositions[9].x, pointLightPositions[9].y, pointLightPositions[9].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.5f,   //k_c
    0.009f,  //k_l
    0.0032f,//k_q
    10       // light number
);

PointLight pointlight11(

    pointLightPositions[10].x, pointLightPositions[10].y, pointLightPositions[10].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.01f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    11       // light number
);

PointLight pointlight12(

    pointLightPositions[11].x, pointLightPositions[11].y, pointLightPositions[11].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.01f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    12       // light number
);
//
//PointLight pointlight13(
//
//    pointLightPositions[12].x, pointLightPositions[12].y, pointLightPositions[12].z,  // position
//    0.05f, 0.05f, 0.05f,     // ambient
//    0.8f, 0.8f, 0.8f,     // diffuse
//    1.0f, 1.0f, 1.0f,        // specular
//    0.01f,   //k_c
//    0.009f,  //k_l
//    0.0032f, //k_q
//    13       // light number
//);
//
//PointLight pointlight14(
//
//    pointLightPositions[13].x, pointLightPositions[13].y, pointLightPositions[13].z,  // position
//    0.05f, 0.05f, 0.05f,     // ambient
//    0.8f, 0.8f, 0.8f,     // diffuse
//    1.0f, 1.0f, 1.0f,        // specular
//    0.01f,   //k_c
//    0.009f,  //k_l
//    0.0032f, //k_q
//    14       // light number
//);
//
//PointLight pointlight15(
//
//    pointLightPositions[14].x, pointLightPositions[14].y, pointLightPositions[14].z,  // position
//    0.05f, 0.05f, 0.05f,     // ambient
//    0.8f, 0.8f, 0.8f,     // diffuse
//    1.0f, 1.0f, 1.0f,        // specular
//    0.01f,   //k_c
//    0.009f,  //k_l
//    0.0032f, //k_q
//    15       // light number
//);



SpotLight spotlight(

    spotLightPositions[0].x, spotLightPositions[0].y, spotLightPositions[0].z, // position
    0.0, -1.0, 0.0,             //direction
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    60.0,
    50       // light number
);

DirectionLight directionallight(

    0.0, -1.0, 0.0,             //direction
    0.00001f, 0.00001f, 0.00001f,     // ambient
    0.4f, 0.4f, 0.4f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    100       // light number
);

// light settings
bool pointLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool directionLightOn = true;
void chotogombuz(unsigned int& cubeVAO, BezierCurve& semiDome, Octagon& base, Octagon& mid, Shader& lightingShader, glm::mat4 alTogether);


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

void structure(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 12.0;
    float width = 1.0;
    float length = 0.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    //left side
    scale = glm::scale(identityMatrix, glm::vec3(width * 0.8, height * 0.8, length));
    translate = glm::translate(identityMatrix, glm::vec3(-4.1, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);


    scale = glm::scale(identityMatrix, glm::vec3(width * 0.8, height * 0.8, length));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    scale = glm::scale(identityMatrix, glm::vec3(4.2f, 0.6f, 0.5f));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 12.0 * 0.8, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);


   


}


void structure1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 12.0;
    float width = 1.0;
    float length = -3.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    //left side
    scale = glm::scale(identityMatrix, glm::vec3(width * 0.4, height * 0.8, length));
    translate = glm::translate(identityMatrix, glm::vec3(-4.1, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    scale = glm::scale(identityMatrix, glm::vec3(width * 0.4, height * 0.8, length));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    scale = glm::scale(identityMatrix, glm::vec3(3.9f, height * 0.8,0.5 ));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 0.0, -9.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    scale = glm::scale(identityMatrix, glm::vec3(3.9f, 0.2, length));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 4.6, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);



    


   /* scale = glm::scale(identityMatrix, glm::vec3(width * 0.8, height * 0.8, length));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    scale = glm::scale(identityMatrix, glm::vec3(4.2f, 0.6f, 0.5f));
    translate = glm::translate(identityMatrix, glm::vec3(-7.5, 12.0 * 0.8, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);*/




}

void structure2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 12.0;
    float width = 1.0;
    float length = 0.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    scale = glm::scale(identityMatrix, glm::vec3(width, height, 3));
    translate = glm::translate(identityMatrix, glm::vec3(3.0, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);


    scale = glm::scale(identityMatrix, glm::vec3(width, height, 3));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);


    scale = glm::scale(identityMatrix, glm::vec3(7.5f, 1.0, 3.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 12.0, -6.0));
    model = alTogether * translate * scale;

    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);


    scale = glm::scale(identityMatrix, glm::vec3(7.5f, 0.3, 3.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 6.5, -6.0));
    model = alTogether * translate * scale;

    drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);

    scale = glm::scale(identityMatrix, glm::vec3(7.5f, height, 0.2f));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 0.0, -5.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

}



void grassfield(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTex)
{

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translateMatrix = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    string diffuseMapPath ="GRASS.jpg";
    string specularMapPath ="GRASS.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);


    //water
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0, 0.1, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.53, 0.81, 0.92);


    //right gr

    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTex, model);
    //drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 0.0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.2, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 25.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(31.0, 0.2, 3.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);

    //left gr

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-34.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderWithTex, model);
 //  drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 0.0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.2, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-34.5, 0.0, 25.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(31.0, 0.2, 3.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);



    //grass
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.1, 50.0));
    model = alTogether* translateMatrix * scaleMatrix;
     drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 0.0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.1, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.1, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.5, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.1, 50.0));
    model = alTogether * translateMatrix * scaleMatrix;
     drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 0.0);

     //wall

     translateMatrix = glm::translate(identityMatrix, glm::vec3(28.0, 0.0, 50.0));
     scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 4.0, 1.0));
     model = alTogether * translateMatrix * scaleMatrix;
     //drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);



}

void tajmahal(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 12.0;
    float width = 1.0;
    float length = 0.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    
    scale = glm::scale(identityMatrix, glm::vec3(width, height, length));
    translate = glm::translate(identityMatrix, glm::vec3(3.0, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    
    scale = glm::scale(identityMatrix, glm::vec3(width, height, length));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 0.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

    scale = glm::scale(identityMatrix, glm::vec3(7.5f, 1.0f,0.5f));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 12.0, -6.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);


    model = alTogether * identityMatrix;
    structure(cubeVAO, lightingShader, model);

    
    translate = glm::translate(identityMatrix, glm::vec3(11.3, 0.0, 0.0));
    model = alTogether * translate;
    structure(cubeVAO, lightingShader, model);

    rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-9.0, 0.0, 0.7));
    model = alTogether * translate * rotate ;
    structure(cubeVAO, lightingShader, model);


    rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(17.0, 0.0, -6.9));
    model = alTogether * translate * rotate;
    structure(cubeVAO, lightingShader, model);

    model = alTogether * identityMatrix;
    structure1(cubeVAO, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(11.3, 0.0, 0.0));
    model = alTogether * translate;
    structure1(cubeVAO, lightingShader, model);

    rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-9.0, 0.0, 0.7));
    model = alTogether * translate * rotate;
    structure1(cubeVAO, lightingShader, model);


    rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(17.0, 0.0, -6.9));
    model = alTogether * translate * rotate;
    structure1(cubeVAO, lightingShader, model);


   /* model = alTogether * identityMatrix;
    structure1(cubeVAO, lightingShader, model);*/

}

void drawMinar(unsigned int& cubeVAO, BezierCurve& cylinder, BezierCurve& semiDome, Octagon& base, Octagon& oct, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    scale = glm::scale(identityMatrix, glm::vec3(2.0, 4.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * scale * translate;
    oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(2.5, 9.0, 2.5));
    translate = glm::translate(identityMatrix, glm::vec3(2.4, 2.0, 2.4));
    model = alTogether * translate * scale;
    cylinder.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.9, 0.3, 1.9));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
    model = alTogether * translate * scale;
    oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.7, 0.3, 1.7));
    translate = glm::translate(identityMatrix, glm::vec3(0.3, 13.0, 0.3));
    model = alTogether * translate * scale;
    oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.6, 18.5, 0.6));
    model = alTogether * translate * scale;
    chotogombuz(cubeVAO, semiDome, oct, oct, lightingShader, model);

}

void chotogombuz(unsigned int& cubeVAO, BezierCurve& semiDome, Octagon& base, Octagon& mid, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    scale = glm::scale(identityMatrix, glm::vec3(1.5, 2.0, 1.5));
    translate = glm::translate(identityMatrix, glm::vec3(1.8, -0.3, 1.8));
    model = alTogether * translate * scale;
    semiDome.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.0, 1.5));
    model = alTogether * scale;
    base.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.5, 0.3, 1.5));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 2.3, 0.0));
    model = alTogether * translate * scale;
    mid.drawOctagonWithMaterialisticProperty(lightingShader, model);


    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(1.1, 1.0, 0.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(2.2, 1.0, 0.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(3.2, 1.0, 1.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(3.2, 1.0, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(2.2, 1.0, 3.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(1.1, 1.0, 3.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 1.0, 1.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 1.0, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

}


void gombuz(unsigned int& cubeVAO, BezierCurve& Dome, Octagon& base, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    scale = glm::scale(identityMatrix, glm::vec3(4.0, 5.0, 4.0));
    translate = glm::translate(identityMatrix, glm::vec3(3.5, -0.7, 3.5));
    model = alTogether * translate * scale;
    Dome.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(3.0, 3.0, 3.0));
    model = alTogether * scale;
    base.drawOctagonWithMaterialisticProperty(lightingShader, model);

}




int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWi ndowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float minarVertices[] = {
     -0.77, 0.0, 5.1000,
     -0.76, 0.1, 5.1000,
     -0.75, 0.2, 5.1000,
     -0.74, 0.3, 5.1000,
     -0.73, 0.4, 5.1000,
     -0.72, 0.5, 5.1000,
     -0.71, 0.6, 5.1000,
     -0.70, 0.7, 5.1000,
     -0.69, 0.8, 5.1000,
     -0.68, 0.9, 5.1000,
     -0.67, 1.0, 5.1000,
     -0.66, 1.1, 5.1000,
     -0.65, 1.2, 5.1000,
     -0.64, 1.3, 5.1000,
     -0.63, 1.4, 5.1000,
     -0.62, 1.5, 5.1000,
     -0.61, 1.6, 5.1000,
     -0.60, 1.7, 5.1000,
     -0.59, 1.8, 5.1000,
     -0.58, 1.9, 5.1000,
    };

    float domeVerties[] = { 
        -0.4400, 0.7800, 5.1000,
        -0.4350, 0.7700, 5.1000,
        -0.4400, 0.9050, 5.1000,
        -0.4450, 1.0100, 5.1000,
        -0.5150, 1.1100, 5.1000,
        -0.6300, 1.1950, 5.1000,
        -0.7050, 1.3000, 5.1000,
        -0.7600, 1.4250, 5.1000,
        -0.7950, 1.5300, 5.1000,
        -0.7950, 1.6300, 5.1000,
        -0.7650, 1.7450, 5.1000,
        -0.7150, 1.8100, 5.1000,
        -0.6350, 1.8850, 5.1000,
        -0.5600, 1.9700, 5.1000,
        -0.4800, 2.0250, 5.1000,
        -0.4000, 2.0700, 5.1000,
        -0.3050, 2.1200, 5.1000,
        -0.1950, 2.1750, 5.1000,
        -0.1150, 2.2350, 5.1000,
        -0.0600, 2.2850, 5.1000,
        -0.0100, 2.3250, 5.1000,
        0.000, 2.4000, 5.1000

    };

    float semiDomeVerties[] = {
        -0.7600, 1.4250, 5.1000,
        -0.7950, 1.5300, 5.1000,
        -0.7950, 1.6300, 5.1000,
        -0.7650, 1.7450, 5.1000,
        -0.7150, 1.8100, 5.1000,
        -0.6350, 1.8850, 5.1000,
        -0.5600, 1.9700, 5.1000,
        -0.4800, 2.0250, 5.1000,
        -0.4000, 2.0700, 5.1000,
        -0.3050, 2.1200, 5.1000,
        -0.1950, 2.1750, 5.1000,
        -0.1150, 2.2350, 5.1000,
        -0.0600, 2.2850, 5.1000,
        -0.0100, 2.3250, 5.1000,
        0.000, 2.4000, 5.1000
    };

    glm::vec4 domeAmbient = glm::vec4(1.0, 0.8, 0.8, 1.0);
    glm::vec4 domeDiffusive = glm::vec4(1.0, 0.8, 0.8, 1.0);
    glm::vec4 domeSpecular = glm::vec4(1.0, 0.8, 0.8, 1.0);
    float domeShiny = 35.0f;

    BezierCurve dome = BezierCurve(domeVerties, 66, domeAmbient, domeDiffusive, domeSpecular, domeShiny, 0);
    BezierCurve semiDome = BezierCurve(semiDomeVerties, 45, domeAmbient, domeDiffusive, domeSpecular, domeShiny, 0);
    BezierCurve minar = BezierCurve(minarVertices, 60, domeAmbient, domeDiffusive, domeSpecular, domeShiny, 0);



    BezierCurve dome2 = BezierCurve(domeVerties, 75, domeAmbient, domeDiffusive, domeSpecular, domeShiny, 1);

    glm::vec4 octAmbient = glm::vec4(0.5, 0.5, 0.5, 1.0);
    glm::vec4 octDiffusive = glm::vec4(0.5, 0.5, 0.5, 1.0);
    glm::vec4 octSpecular = glm::vec4(0.7, 0.7, 0.7, 1.0);
    float octShiny = 32.0f;

    glm::vec4 octWhite = glm::vec4(0.7, 0.7, 0.7, 1.0);
    glm::vec4 octGrey = glm::vec4(0.7, 0.3, 0.3, 1.0);

    Octagon oct1 = Octagon(octAmbient, octDiffusive, octSpecular, octShiny);
    Octagon oct2 = Octagon(octWhite, octWhite, octWhite, octShiny);
    Octagon oct3 = Octagon(octGrey, octGrey, octGrey, octShiny);


    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




   // akash

     string diffuseMapPath1 ="skypec.jpg";
     string specularMapPath1 ="skypec.jpg";


    unsigned int diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
   // Cube cube = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);



    Sphere sphere = Sphere();

    Sphere2  sphere2 = Sphere2(5.0f, 144, 72, glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap1, specMap1, 0.0f, 0.0f, 1.0f, 1.0f);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    string diffuseMapPath = "container2.png";
    string specularMapPath = "container2_specular.png";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);




    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------

        // new code for draw

        

        //sesh 

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        
        //new lighr
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);
        pointlight8.setUpPointLight(lightingShader);
        pointlight9.setUpPointLight(lightingShader);
        pointlight10.setUpPointLight(lightingShader);
        pointlight11.setUpPointLight(lightingShader);
        pointlight12.setUpPointLight(lightingShader);
        /*pointlight13.setUpPointLight(lightingShader);
        pointlight14.setUpPointLight(lightingShader);
        pointlight15.setUpPointLight(lightingShader);*/
        
        spotlight.setUpSpotLight(lightingShader);
        directionallight.setUpDirectionalLight(lightingShader);

       // lightingShader.setVec3("directionLight.position", -0.5, 3.0, -0.5);
       

        
        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 250.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotate, rotateZMatrix, scaleMatrix, model, translate, scale, model2;
       
        

        //main building base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.0, 0.0, -40.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0, 1.0, 40.0));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.6, 0.6, 0.6);

        //left base

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-38.0, -0.5, -40.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(17.0, 1.0, 35.0));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.74, 0.247, 0.247);

        //right base
        // 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0, -0.6, -40.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(17.0, 1.0, 35.0));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.74, 0.247, 0.247);
        //akash

         translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0,0.0, 0.0));
         scaleMatrix = glm::scale(identityMatrix, glm::vec3(600.0, 600.0, 600.0));
         model = translateMatrix * scaleMatrix;
         sphere2.drawSphereWithTexture(lightingShader, model);



        //minar
        model2 = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.5f));

        translate = glm::translate(identityMatrix, glm::vec3(-3.5f, 10.0f, -22.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
        model = model2 * translate * scale;
        gombuz(cubeVAO, dome, oct2, lightingShader, model);
        
        translate = glm::translate(identityMatrix, glm::vec3(-9.0f, 10.0f, -14.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = model2 * translate * scale;
        chotogombuz(cubeVAO, semiDome, oct2, oct2, lightingShader, model);
        
        translate = glm::translate(identityMatrix, glm::vec3(4.5f, 10.0f, -14.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = model2 * translate * scale;
        chotogombuz(cubeVAO, semiDome, oct2, oct2, lightingShader, model);
        
        translate = glm::translate(identityMatrix, glm::vec3(-9.0f, 10.0f, -29.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = model2 * translate * scale;
        chotogombuz(cubeVAO, semiDome, oct2, oct2, lightingShader, model);
        
        translate = glm::translate(identityMatrix, glm::vec3(4.5f, 10.0f,  -29.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = model2 * translate * scale;
        chotogombuz(cubeVAO, semiDome, oct2, oct2, lightingShader, model);


        //Minar right
        translate = glm::translate(identityMatrix, glm::vec3(17.5, 0.0, -2.5));
        model = model2 * translate;
        drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);
        //Minar left
        translate = glm::translate(identityMatrix, glm::vec3(-22.5, 0.0, -2.5));
        model = model2 * translate;
        drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);
        //Minar right back
        translate = glm::translate(identityMatrix, glm::vec3(17.5, 0.0, -42.5));
        model = model2 * translate;
        drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);
        //Minar left back
        translate = glm::translate(identityMatrix, glm::vec3(-22.5, 0.0, -42.5));
        model = model2 * translate;
        drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


        






        //mid water
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0, 0.0, 50.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.0, 0.1, 8.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 0.53, 0.81, 0.92);

        //mid border

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0, 0.0, 52.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0, 0.5, 0.8));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0, 0.0, 56.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0, 0.5, 0.8));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0, 0.0, 52.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.5, 4.8));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.8, 0.0, 52.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.5, 4.8));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);








        //right water
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0, 0.0, 52.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 3.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 0.53, 0.81, 0.92);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0, 0.0, 50.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 2.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0, 0.0, 55.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 3.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);


        //left water

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-34.0, 0.0, 52.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 3.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 0.53, 0.81, 0.92);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-34.0, 0.0, 50.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 2.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-34.0, 0.0, 55.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.1, 3.0));
        model = translateMatrix * scaleMatrix;

        drawCube(cubeVAO, lightingShader, model, 1.0, 0.71, 0.76);





        //chad
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.0, 10.0, -32.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(13.0, 0.01, 26.5));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.0, 10.0, -32.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8, 0.01, 26.5));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);


        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.0, 10.0, -32.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.6, 0.01, 9.5));
        model = translateMatrix * scaleMatrix* rotate;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);


        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.0, 10.0, -19.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.6, 0.01, 9.5));
        model = translateMatrix * scaleMatrix * rotate;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-12.6, 10.0, -25.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8, 0.01, 12.8));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);


        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0, 10.0, -32.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.6, 0.01, 9.5));
        model = translateMatrix * scaleMatrix * rotate;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);


        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0, 10.0, -19.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.6, 0.01, 9.5));
        model = translateMatrix * scaleMatrix * rotate;

        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.2, 10.0, -25.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8, 0.01, 12.8));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5, 0.5, 0.5);


        model = identityMatrix;
        tajmahal(cubeVAO,lightingShader, model);

        rotate = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.7, 0.0, -19.2));
        model = translateMatrix * rotate;
        tajmahal(cubeVAO, lightingShader, model);


        rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, -18.6));
        model = translateMatrix * rotate;
        tajmahal(cubeVAO, lightingShader, model);



        rotate = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, -37.5));
        model = translateMatrix * rotate;
        tajmahal(cubeVAO, lightingShader, model);


       // inner window
       // 
        model = identityMatrix;
        structure2(cubeVAO, lightingShader, model);

        rotate = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, -37.5));
        model = translateMatrix * rotate;
        structure2(cubeVAO, lightingShader, model);

        rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, -18.6));
        model = translateMatrix * rotate;
        structure2(cubeVAO, lightingShader, model);

        rotate = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.7, 0.0, -19.2));
        model = translateMatrix * rotate;
        structure2(cubeVAO, lightingShader, model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //bed(cubeVAO, lightingShader, model);

       // glm::mat4 modelForSphere = glm::mat4(1.0f);
       // modelForSphere = glm::translate(model, glm::vec3(1.5f, 1.2f, 0.5f));
       // sphere.drawSphere(lightingShader, modelForSphere);
        lightingShader.setMat4("model", model);
        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < noOfPointLights; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);


        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        

        
        

        //spotlight.setUpSpotLight(lightingShaderWithTexture);

       //directionallight.setUpDirectionalLight(lightingShaderWithTexture);

        model = identityMatrix;
        lightingShaderWithTexture.setMat4("model", model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.2, 10.0, 20.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8, 5.01, 5.8));
        model = translateMatrix * scaleMatrix;
       // cube.drawCube(lightingShaderWithTexture, model);


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
       // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
       // glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);


        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);


        //new light

        pointlight6.setUpPointLight(lightingShaderWithTexture);
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        pointlight8.setUpPointLight(lightingShaderWithTexture);
        pointlight9.setUpPointLight(lightingShaderWithTexture);
        pointlight10.setUpPointLight(lightingShaderWithTexture);

        pointlight11.setUpPointLight(lightingShaderWithTexture);
        pointlight12.setUpPointLight(lightingShaderWithTexture);
       /* pointlight13.setUpPointLight(lightingShaderWithTexture);
        pointlight14.setUpPointLight(lightingShaderWithTexture);
        pointlight15.setUpPointLight(lightingShaderWithTexture);*/

       
        model = identityMatrix;
        grassfield(cubeVAO, lightingShader, model, lightingShaderWithTexture);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 108.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, -1.0));
        model = translateMatrix * scaleMatrix;
        grassfield(cubeVAO, lightingShader, model, lightingShaderWithTexture);

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(model, glm::vec3(-0.45f, -0.4f, -2.8f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(YAWR, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(YAWL, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(PITCHU, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(PITCHD, deltaTime);
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointlight5.turnOff();
            pointlight6.turnOff();
            pointlight7.turnOff();
            pointlight8.turnOff();
            pointlight9.turnOff();
            pointlight10.turnOff();
           /* pointlight11.turnOff();
            pointlight12.turnOff();
            pointlight13.turnOff();
            pointlight14.turnOff();*/
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight3.turnOn();
            pointlight4.turnOn();
            pointlight5.turnOn();
            pointlight6.turnOn();
            pointlight7.turnOn();
            pointlight8.turnOn();
            pointlight9.turnOn();
            pointlight10.turnOn();
           /* pointlight11.turnOn();
            pointlight12.turnOn();
            pointlight13.turnOn();
            pointlight14.turnOn();*/
            pointLightOn = !pointLightOn;
        }
    }


    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();

            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            specularToggle = !specularToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }

    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (directionLightOn)
        {
            directionallight.turnOff();
            directionLightOn = !directionLightOn;
        }
        else
        {
            directionallight.turnOn();
            directionLightOn = !directionLightOn;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}