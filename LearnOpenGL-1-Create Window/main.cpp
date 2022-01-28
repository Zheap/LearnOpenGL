#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();                                                                     // Initialize GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                                  // Tell GLFW what version of OpenGL we are using £¬In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                  // Tell GLFW we are using the CORE profile£¬So that means we only have the modern functions

    GLFWwindow* window = glfwCreateWindow(800, 800, "Learn OpenGL", NULL, NULL);    // Create a GLFWwindow object of 800 by 600 pixels, naming it "Learn OpenGL"
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                                 // Introduce window to current context

    gladLoadGL();                                                                   // Load GLAD so it configures OpenGL
    glViewport(0, 0, 800, 800);                                                     // Specify the viewport of OpenGL in the window, in this case, the viewport goes from x = 0, y = 0, to x = 800, y = 800

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);                                           // Specify the color of background
    glClear(GL_COLOR_BUFFER_BIT);                                                   // Clean the back color and assign the new color to it
    glfwSwapBuffers(window);                                                        // Swap the back buffer with the front buffer

    while (!glfwWindowShouldClose(window))                                          // Main while loop
    {
        glfwPollEvents();                                                           // Take care of all GLFW events
    }

    glfwDestroyWindow(window);                                                      // Delete window before ending the program
    glfwTerminate();                                                                // Terminate GLFW before ending the program
    return 0;
}
