#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Graphics/Window/GLWindow.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    Graphics::GLWindow glWindow = Graphics::GLWindow("Test", false);
    glWindow.setCurrContext();

    // Init GLEW and check if init is sucessful 
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glWindow.getWindow()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(glWindow.getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}