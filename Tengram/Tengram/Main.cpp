#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";

const char* vertexShaderSourceWithColor =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"

"out vec3 ourColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;"
"}\0";

//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";


const char* fragmentShaderSourceWithColor = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Recorrido Virtual Horror Fest", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceWithColor, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceWithColor, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //float vertices[] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f,   // top left 
    //    -1.0f,  -0.5f, 0.0f,  // top right
    //    -1.0f,   0.5f, 0.0f,  // bottom right
    //};
    //unsigned int indices[] = {  // note that we start from 0!
    //    0, 1, 3,  // first Triangle
    //    3, 2, 1,   // second Triangle

    //    3, 2, 5,   // third Triangle
    //    5, 4, 2   // fourth Triangle
    //};

        //0.0f, 0.0f, 0.0f, 0.184, 0.215, 0.576,  // 
        //0.0f, 0.0f, 0.0f, 0.184, 0.215, 0.576,  // 
        //0.0f, 0.0f, 0.0f, 0.184, 0.215, 0.576,  // 


    float verticesTriangulosColores[] = {
        //Celeste fuerte
        1.0f, 1.0f, 0.0f, 0.062, 0.647, 0.835,  // 0
        0.5f, 0.5f, 0.0f, 0.062, 0.647, 0.835,  // 1
        1.0f, 0.5f, 0.0f, 0.062, 0.647, 0.835,  // 2 - 1

        1.0f, 0.5f, 0.0f, 0.062, 0.647, 0.835,  // 3
        0.5f, 0.5f, 0.0f, 0.062, 0.647, 0.835,  // 4
        1.0f, 0.0f, 0.0f, 0.062, 0.647, 0.835,  // 5 - 2

        //Celeste Claro
       -1.0f, 1.0f, 0.0f, 0.274, 0.909, 0.964, // 1
        -0.5f, 0.5f, 0.0f, 0.274, 0.909, 0.964, //2
        -1.0f, 0.5f, 0.0f, 0.274, 0.909, 0.964, //3 - 1

        -0.5f, 0.5f, 0.0f, 0.274, 0.909, 0.964, //4
        -1.0f, 0.5f, 0.0f, 0.274, 0.909, 0.964, //5
        -1.0f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //6 - 2

        -0.5f, 0.5f, 0.0f, 0.274, 0.909, 0.964, //7
        -0.5f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //8
        -1.0f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //9 - 3

        0.0f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //10
        -0.5f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //11
        -0.5f, -0.5f, 0.0f, 0.274, 0.909, 0.964, //12 - 4

        -0.5f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //13
        -1.0f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //14
        -0.5f, -0.5f, 0.0f, 0.274, 0.909, 0.964, //15 - 5

        -1.0f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //16
        -0.5f, -0.5f, 0.0f, 0.274, 0.909, 0.964, //17
        -1.0f, -0.5f, 0.0f, 0.274, 0.909, 0.964, //18 - 6

        -1.0f, -1.0f, 0.0f, 0.274, 0.909, 0.964, //19
        -1.0f, -0.5f, 0.0f, 0.274, 0.909, 0.964, //20
        -0.5f, -0.5f, 0.0f, 0.274, 0.909, 0.964, //21 - 7

        0.0f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //22
        -0.5f, 0.5f, 0.0f, 0.274, 0.909, 0.964, //23
        -0.5f, 0.0f, 0.0f, 0.274, 0.909, 0.964, //24 - 8

        //Naranja 
        -1.0f, 1.0f, 0.0f, 0.964, 0.647, 0.274,  // 1
        -0.5f, 1.0f, 0.0f, 0.964, 0.647, 0.2740,  // 2
        -0.5f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 3 - 1

        -0.5f, 1.0f, 0.0f, 0.964, 0.647, 0.274,  // 4
        0.0f, 1.0f, 0.0f, 0.964, 0.647, 0.2740,  //5
        0.0f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 6 - 2

        -0.5f, 1.0f, 0.0f, 0.964, 0.647, 0.274,  // 7
        0.0f, 0.5f, 0.0f, 0.964, 0.647, 0.2740,  // 8
        -0.5f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 9 - 3

        -0.5f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 10
        0.0f, 0.5f, 0.0f, 0.964, 0.647, 0.2740,  // 11
        0.0f, 0.0f, 0.0f, 0.964, 0.647, 0.274,  // 12 - 4

        0.0f, 1.0f, 0.0f, 0.964, 0.647, 0.274,  // 13
        0.5f, 1.0f, 0.0f, 0.964, 0.647, 0.2740,  // 14
        0.0f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 15 - 5

        0.5f, 1.0f, 0.0f, 0.964, 0.647, 0.274,  // 16
        0.0f, 0.5f, 0.0f, 0.964, 0.647, 0.2740,  // 17
        0.5f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 18 - 6

        0.0f, 0.0f, 0.0f, 0.964, 0.647, 0.274,  // 19
        0.5f, 0.5f, 0.0f, 0.964, 0.647, 0.2740,  // 20
        0.0f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 21 - 7

        1.0f, 1.0f, 0.0f, 0.964, 0.647, 0.274,  // 22
        0.5f, 1.0f, 0.0f, 0.964, 0.647, 0.2740,  // 23
        0.5f, 0.5f, 0.0f, 0.964, 0.647, 0.274,  // 24 - 8

        //rojo

        0.0f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 1
        0.5f, 0.5f, 0.0f, 0.898, 0.043, 0.164,  // 2
        0.5f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 3 - 1

        0.5f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 4
        0.5f, 0.5f, 0.0f, 0.898, 0.043, 0.164,  // 5
        1.0f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 6 - 2

        0.0f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 7
        0.5f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 8
        0.5f, -0.5f, 0.0f, 0.898, 0.043, 0.164,  // 9 - 3

        1.0f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 10
        0.5f, 0.0f, 0.0f, 0.898, 0.043, 0.164,  // 11
        0.5f, -0.5f, 0.0f, 0.898, 0.043, 0.164,  // 12 - 4

        //Amarillo

        0.5f, -0.5f, 0.0f, 0.882, 0.807, 0.035,  // 1
        1.0f, -0.5f, 0.0f, 0.882, 0.807, 0.035,  // 2
        1.0f, 0.0f, 0.0f, 0.882, 0.807, 0.035,  // 3 - 1

        0.5f, -0.5f, 0.0f, 0.882, 0.807, 0.035,  //4 
        1.0f, -1.0f, 0.0f, 0.882, 0.807, 0.035,  // 5
        1.0f, -0.5f, 0.0f, 0.882, 0.807, 0.035,  // 6 - 2

        0.5f, -0.5f, 0.0f, 0.882, 0.807, 0.035,  // 7
        0.5f, -1.0f, 0.0f, 0.882, 0.807, 0.035,  // 8
        1.0f, -1.0f, 0.0f, 0.882, 0.807, 0.035,  // 9 - 3

        0.5f, -0.5f, 0.0f, 0.882, 0.807, 0.035,  // 10
        0.5f, -1.0f, 0.0f, 0.882, 0.807, 0.035,  // 11
        0.0f, -1.0f, 0.0f, 0.882, 0.807, 0.035,  // 12 - 4

        //Verde
        0.0f, 0.0f, 0.0f, 0.282, 0.576, 0.184,  // 1
        0.0f, -0.5f, 0.0f, 0.282, 0.576, 0.184,  // 2
        0.5f, -0.5f, 0.0f, 0.282, 0.576, 0.184,  // 3 - 1

        0.0f, 0.0f, 0.0f, 0.282, 0.576, 0.184,  // 4
        0.0f, -0.5f, 0.0f, 0.282, 0.576, 0.184,  // 5
        -0.5f, -0.5f, 0.0f, 0.282, 0.576, 0.184,  // 6 - 2

        //Azul

        0.0f, -0.5f, 0.0f, 0.184, 0.215, 0.576,  // 1
        0.5f, -0.5f, 0.0f, 0.184, 0.215, 0.576,  // 2
        0.0f, -1.0f, 0.0f, 0.184, 0.215, 0.576,  // 3 - 2

        0.0f, -0.5f, 0.0f, 0.184, 0.215, 0.576,  // 4
        -0.5f, -0.5f, 0.0f, 0.184, 0.215, 0.576,  // 5
        0.0f, -1.0f, 0.0f, 0.184, 0.215, 0.576,  // 6 - 2

        -0.5f, -0.5f, 0.0f, 0.184, 0.215, 0.576,  // 7
       -0.5f, -1.0f, 0.0f, 0.184, 0.215, 0.576,  // 8
        -1.0f, -1.0f, 0.0f, 0.184, 0.215, 0.576,  // 9 - 3

        -0.5f, -0.5f, 0.0f, 0.184, 0.215, 0.576,  // 10
        -0.5f, -1.0f, 0.0f, 0.184, 0.215, 0.576,  // 11
        -0.0f, -1.0f, 0.0f, 0.184, 0.215, 0.576,  // 12 - 4
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); //Número de elementos // referencia al buffer
    glGenBuffers(1, &EBO);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangulosColores), verticesTriangulosColores, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Column Major
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Column Major
    //glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glLineWidth(20.0);
        glPointSize(20.0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES , 0, 100);
        //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}