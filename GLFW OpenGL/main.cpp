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


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void drawTriangle(){
    // All coordinates within this so called normalized device coordinates
    // range will end up visible on your screen (and all coordinates outside this region won't).
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    // With the vertex data defined we'd like to send it as input to the first process
    // of the graphics pipeline: the vertex shader.
    // This is done by creating memory on the GPU where we store the vertex data,
    // configure how OpenGL should interpret the memory and specify how to send
    // the data to the graphics card. The vertex shader then processes as much
    // vertices as we tell it to from its memory.
    
    // Memory is managed with Vertex Buffer Objects (VBO) - stores large number of vertices in the GPU's memory
    // Once the data is in the graphics card's memory the vertex shader has almost instant access to
    // the vertices making it extremely fast
    
    
    // Just like any object in OpenGL, this buffer has a unique ID corresponding to that buffer,
    // so we can generate one with a buffer ID using the glGenBuffers function:
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // OpenGL has many types of buffer objects and the buffer type of a
    // vertex buffer object is GL_ARRAY_BUFFER. OpenGL allows us to bind
    // to several buffers at once as long as they have a different buffer
    // type.
    // We can bind the newly created buffer to the GL_ARRAY_BUFFER target with the glBindBuffer fun
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Then we can make a call to the glBufferData function that copies the
    // previously defined vertex data into the buffer's memory:
    // The fourth parameter specifies how we want the graphics card to manage the given data. This can take 3 forms:
    
    //GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    //GL_STATIC_DRAW: the data is set only once and used many times.
    //GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //Vertex Shader

}

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
        
        processInput(window);
        
        
        // rendering commands here
        // At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame (this could be the effect you're looking for, but usually you don't). We can clear the screen's color buffer using glClear where we pass in buffer bits to specify which buffer we would like to clear. The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT. Right now we only care about the color values so we only clear the color buffer.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        
        // will swap the color buffer (a large 2D buffer that contains color
        // values for each pixel in GLFW's window) that is used to render
        // to during this render iteration and show it as output to the screen.
        // double buffer (check notes)
        glfwSwapBuffers(window);
    }
    
    // window has now closed
    
    // properly clean/delete all of GLFW's resources
    glfwTerminate();
    return 0;
}
