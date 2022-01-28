#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource =    "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";

// Fragment Shader source code
const char* fragmentShaderSource =  "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{"
                                    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                    "}\n\0";


int main()
{
    glfwInit();                                                                                     // Initialize GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                                                  // Tell GLFW what version of OpenGL we are using, In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                                  // Tell GLFW we are using the CORE profile, So that means we only have the modern functions

    GLFWwindow* window = glfwCreateWindow(800, 800, "Triangle", NULL, NULL);                        // Create a GLFWwindow object of 800 by 800 pixels, naming it "Triangle"
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                                                 // Introduce the window into the current context

    gladLoadGL();                                                                                   // Load GLAD so it configures OpenGL
    glViewport(0, 0, 800, 800);                                                                     // Specify the viewport of OpenGL in the Window£¬In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);                                         // Create Vertex Shader Object and get its reference
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);                                     // Attach Vertex Shader source to the Vertex Shader Object
    glCompileShader(vertexShader);                                                                  // Compile the Vertex Shader into machine code

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);                                     // Create Fragment Shader Object and get its reference
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);                                 // Attach Fragment Shader source to the Vertex Shader Object
    glCompileShader(fragmentShader);                                                                // Compile the Fragment Shader into machine code


    GLuint shaderProgram = glCreateProgram();                                                       // Create Shader Program Object and get its reference
    glAttachShader(shaderProgram, vertexShader);                                                    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);                                                                   // Wrap-up/link all shaders together into the Shader Program

    glDeleteShader(vertexShader);                                                                   // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(fragmentShader);

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,                                                    // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,                                                     // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f                                                   // Upper corner
    };

    GLuint VAO, VBO;                                                                                // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
    glGenVertexArrays(1, &VAO);                                                                     // Generate the VAO and VBO with only 1 object each, VAO exists in order to quickly be able switch between differents VBOs
    glGenBuffers(1, &VBO);                                                                          // VBO to store vertex data and send big batches to GPU

    glBindVertexArray(VAO);                                                                         // Make the VAO the current Vertex Array Object by binding it                                

    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                             // Bind the VBO specifing it's a GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);                      // Introduce the vertices into the VBO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);                   // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glEnableVertexAttribArray(0);                                                                   // Enable the Vertex Attribute so that OpenGL knows to use it

    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                               // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindVertexArray(0);
        
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);                                                    // Specify the color of the background
        glClear(GL_COLOR_BUFFER_BIT);                                                               // clean the back buffer and assign the new color to it
        glUseProgram(shaderProgram);                                                                // Tell OpenGL which Shader Program we want to use
        glBindVertexArray(VAO);                                                                     // Bind the VAO so OpenGL knows to use it
        glDrawArrays(GL_TRIANGLES, 0, 3);                                                           // Draw the triangle using the GL_TRIANGLES primitive
        glfwSwapBuffers(window);                                                                    // Swap the back buffer with the front buffer
        glfwPollEvents();                                                                           // Take care of all GLFW events
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}