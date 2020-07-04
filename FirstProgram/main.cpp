#include "Used_Function.h"

/*Macros ==> Window dimension*/
#define WIND_WIDTH (int)1000
#define WIND_HEIGH (int)750


Vertex vertices[] =     /*sizeof(vertices)=4*(6*3 +6) = 96 Bytes*/
{
    glm::vec3(0.5f,0.5f,0.f),      glm::vec3(1.f,0.f,0.f),     glm::vec2(0.f,1.f),
    glm::vec3(0.5f,-0.5f,0.f),     glm::vec3(0.f,1.f,0.f),     glm::vec2(0.f,0.f),
    glm::vec3(-0.5f,0.5f,0.f),     glm::vec3(0.f,0.f,1.f),     glm::vec2(1.f,0.f),

    glm::vec3(-0.5f,-0.5f,0.f),    glm::vec3(1.f,1.f,0.f),     glm::vec2(0.f,0.f),
};
unsigned NbOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = { 0,1,2,1,2,3 };
unsigned NbOfInd = sizeof(indices) / sizeof(GLuint);

int main()
{
    GLFWwindow* window;
    int FRAME_WIDTH = 0, FRAME_HEIGH = 0;
  
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  //when false is set you can't resize the window, & when it's true you can then, it's resizable by default

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIND_WIDTH, WIND_HEIGH, "Super Mario", NULL, NULL);

    /* Set the framebuffer */
    glfwSetFramebufferSizeCallback(window, resize_window_callback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    /*Shader Init*/
    GLuint MyProgram;
    if (!create_shader(MyProgram))
    {
        glfwTerminate();
        return -1;
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); /*Send Vertices data*/

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*We have to match our data to be understandble by the GPU by pointers -- [][][] pos -- [][][] color -- [][] textcoord*/ // Input assembly
    /*Position*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex,position));
    glEnableVertexAttribArray(0);
    /*Color*/
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    /*Text coord*/
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textcoord));
    glEnableVertexAttribArray(2);

    /*Bind*/
    glBindVertexArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(MyProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, NbOfInd);
        glDrawElements(GL_TRIANGLES, NbOfInd, GL_UNSIGNED_INT, 0);

        //glDrawArrays(GL_POINTS, 0, 4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        Close_Window_W_Esc(window);
    }
    /*Delete Program*/
    glDeleteProgram(MyProgram);

    glfwTerminate();
    return 0;
}
