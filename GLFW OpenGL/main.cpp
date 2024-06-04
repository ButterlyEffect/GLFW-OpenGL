//
//  main.cpp
//  GLFW OpenGL
//
//  Created by Simon Zorrilla on 6/4/24.
//

#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;



int main(int argc, const char * argv[]) {
    //init GFLW
    glfwInit();
    //Set properties for window
    // v3.4
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3);
    // Telling GLFW we want to use the core-profile means we'll get
    // access to a smaller subset of OpenGL features without
    // backwards-compatible features we no longer need
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // NEEDED FOR MAC
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // prevent resize
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE);
    
    
    /*
     Next we're required to create a window object. This window object
     holds all the windowing data and is required by most of GLFW's
     other functions
     */
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    
    // required for Mac
    // the problem is due to retina display with 4x resolution
    // it messes up the positioning of the window.
    // we want to get the actually screen size so the window stays true to the mac
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; //allows newer opengl functionality
    
    
    // we mentioned that GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function:
    
    if(GLEW_OK != glewInit()){
        std::cout << "Failed to initialize GLEW" << std::endl;
        
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    while (!glfwWindowShouldClose(window)){
        //while window is open or not closing continue this loop
        // process inputs, stages etc
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );
        
        glfwSwapBuffers(window);
    }
    
    // window has now closed
    
    glfwTerminate();
    return 0;
}
