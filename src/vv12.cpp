// HaulinCube.cpp : Defines the entry point for the application.
//
#include "pch.h"
#include "vv12.h"
#include "stb_image.h"

#include "Buffer.h"
#include "Shader.h"


GLFWwindow* window;
glm::mat4 view;

double x, y, z, tempX, tempY;
double oldXPos, oldYPos;
glm::quat rotationQuat;
bool hold;
float deltaX, deltaY;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        hold = true;
        glfwGetCursorPos(window, &oldXPos, &oldYPos);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action != GLFW_PRESS)
    {
        hold = false;
        x += deltaX;
        y += deltaY;

        if (x > 360)
        {
            x -= 360;
        }
        else if (x < 0)
        {
            x += 360;
        }

        if (y > 360)
        {
            y -= 360;
        }
        else if (y < 0)
        {
            y += 360;
        }
    }
}

void spin(GLFWwindow* window, double xpos, double ypos)
{

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        deltaX = (xpos - oldXPos) / 9;
        deltaY = (ypos - oldYPos) / 9;

        tempX = x + deltaX;
        tempY = y + deltaY;

        if (tempX > 360)
        {
            tempX -= 360;
        }
        else if (tempX < 0)
        {
            tempX += 360;
        }

        if (tempY > 360)
        {
            tempY -= 360;
        }
        else if (tempY < 0)
        {
            tempY += 360;
        }
        std::cout << "cal: " << ((int)tempX % 90) << std::endl;
        view = glm::rotate(glm::mat4(1.0), glm::radians((float)tempX), glm::vec3(0, 1, 0));
        //view = glm::rotate(view, glm::radians((float)tempY), glm::vec3(1, 0, 0));
    }
}



int main()
{
    x, y, z, tempX, tempY = 0;
    oldXPos, oldYPos = 0;
    hold = false;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Haulin Cube", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    std::cout << glGetString(GL_VERSION) << std::endl;
    if (glewInit() != GLEW_OK)
        std::cout << "FUCK" << std::endl;
    glEnable(GL_DEPTH_TEST);
    glfwSetCursorPosCallback(window, spin);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_LOW: std::cout << message << std::endl; break;
            case GL_DEBUG_SEVERITY_MEDIUM: std::cout << message << std::endl; break;
            case GL_DEBUG_SEVERITY_HIGH: std::cerr << message << std::endl; break;
            }
        }, nullptr);

    float cube[144] = {
        //front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, // 0
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 1
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 2
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f, // 3
         //left face
        -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 4 0
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f, // 5 1
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f, // 6 4
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 7 5
        //back face
        -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 8 4
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f, // 9 5
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f, //10 6
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, //11 7
        //right face
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, //12 2
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //13 3
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, //14 6
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f, //15 7
        //bottom face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  2.0f, //16 0
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  2.0f, //17 2
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  2.0f, //18 4
         0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  2.0f, //19 6
        //top face
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, //20 1
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f, //21 3
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f, //22 5
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f, //23 7
    };

    float testCube[48] = {
        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
    };

    float triangle[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int triInd[3] = {
        0, 1, 2
    };

    unsigned int indices[3 * 6 * 2] = {
        //front face
        0, 1, 3,
        0, 2, 3,
        //left face
        5, 6, 7,
        4, 5, 6,
        //back face
        8, 9, 10,
        9, 10, 11,
        //right face
        12, 13, 14,
        13, 14, 15,
        //bottom face
        16, 17, 18,
        17, 18, 19,
        //top face
        20, 21, 22,
        21, 22, 23
    }; 
    
    Shader* shader = new Shader("res/shaders/Cube.shader");

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer* vb = new VertexBuffer(&cube, 144 * sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void*)(3 * sizeof(float)));


    IndexBuffer* ib = new IndexBuffer(&indices, 36);

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    view = glm::mat4(1.0);
    glm::mat4 mvp = proj * view;

    // Load textures
    int width, height, bpp;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* texBuffer = stbi_load("res/textures/grassSide.png", &width, &height, &bpp, 4);
    unsigned int textures[3];
    glGenTextures(3, textures);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texBuffer);

    if (texBuffer)
        stbi_image_free(texBuffer);
    //top texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    texBuffer = stbi_load("res/textures/grassTop.png", &width, &height, &bpp, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texBuffer);

    if (texBuffer)
        stbi_image_free(texBuffer);
    //bottom texture
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    texBuffer = stbi_load("res/textures/grassBottom.png", &width, &height, &bpp, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texBuffer);


    int loc = shader->GetUniformLocation("u_textures");
    int samplers[3] = { 0, 1, 2 };
    glUniform1iv(loc, 3, samplers);

    if (texBuffer)
        stbi_image_free(texBuffer);
  
    int location = shader->GetUniformLocation("u_MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        GLClearError();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mvp = proj * view;
        glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3 * 6 * 2, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete(shader);
    delete(vb);
    delete(ib);
    glfwTerminate();
    return 0;
}