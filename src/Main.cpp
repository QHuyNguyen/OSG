//#include <iostream>
//#include <time.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//const char* vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "out vec4 vertexColor;\n"
//    "void main()\n"
//    "{\n"
//    " gl_Position = vec4(aPos, 1.0);\n"
//    " vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
//    "}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "in vec4 vertexColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vertexColor;\n"
//    "}\0";
//
////const char* vertexShaderSource = "#version 330 core\n"
////    "layout (location = 0) in vec3 aPos;\n"
////    "layout (location = 1) in vec3 aColor\n"
////
////    "out vec3 vertexColor;\n"
////
////    "void main()\n"
////    "{\n"
////    " gl_Position = vec4(aPos, 1.0);\n"
////    " vertexColor = aColor;\n"
////    "}\0";
////const char* fragmentShaderSource = "#version 330 core\n"
////    "out vec4 FragColor;\n"
////    "in vec3 vertexColor;\n"
////    "void main()\n"
////    "{\n"
////    "   FragColor =  vec4(vertexColor, 1.0);\n"
////    "}\0";
//
//void frameBuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//unsigned int createShader(unsigned int shaderType, const char* source)
//{
//    unsigned int shader = glCreateShader(shaderType);
//    glShaderSource(shader, 1, &source, NULL);
//    glCompileShader(shader);
//    return shader;
//}
//
//void createTexture()
//{
//    int width, height, nrChannels;
//    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//}
//
//int mains()
//{
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Fail" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glewInit();
//
//    glm::mat4 model = glm::mat4(1.0f); //Create model matrix
//    model = glm::rotate(model, glm::radians(-55.0f),
//        glm::vec3(1.0f, 0.0f, 0.0f));
//    glm::mat4 view = glm::mat4(1.0f);
//    // note that we’re translating the scene in the reverse direction
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    glm::mat4 projection;
//    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
//        100.0f);
//
//    float vertices[] =
//    {
//        -0.5f,  0.0f,   0.0f, //0
//         0.0f,  0.0f,   0.0f, //1
//         -0.5f,  0.5f,   0.0f,//2
//       //  0.0f,  0.0f,   0.0f, //1
//         0.0f,  0.5f,   0.0f //3
//        // -0.5f,  0.5f,   0.0f, //2
//    };
//    unsigned int indices[] =
//    {
//        0, 1, 2,
//        1, 3, 2
//    };
//
//    //Create Vertex Array Object
//    unsigned int VAO;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    //Create Vertex Buffer
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //create element buffer
//    unsigned int EBO;
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glEnableVertexAttribArray(1);
//
//    //Create vertex shader;
//    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
//
//    //Create Fragment Shaer
//    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
//
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        processInput(window);
//
//        glUseProgram(shaderProgram);
//        glClearColor(0.2, 0.3, 0.3, 1);
//        glClear(GL_COLOR_BUFFER_BIT);
//        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        //glDrawArrays(GL_TRIANGLES, 0, 3);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}
////OpenGL Code - Draw a Triangles
//    //glfwInit();
//    ///* Initialize the library */
//    //if (!glfwInit())
//    //    return -1;
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    //GLFWwindow* window;
//    ///* Create a windowed mode window and its OpenGL context */
//    //window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
//    //if (!window)
//    //{
//    //    glfwTerminate();
//    //    return -1;
//    //}
//    ///* Make the window's context current */
//    //glfwMakeContextCurrent(window);
//    //glewInit();
//    ////Vertex data
//    //float vertices[6] =
//    //{
//    //    -0.5f, -0.5f,
//    //    0.0f, 0.5f,
//    //    0.5f, -0.5f,
//    //};
//    ////create vertex array
//    //unsigned int vao;
//    //glGenVertexArrays(1, &vao);
//    //glBindVertexArray(vao);
//    ////create vertex buffer
//    //unsigned int vbo;
//    //glGenBuffers(1, &vbo);
//    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
//    ////specify vertex attribute
//    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
//    //glEnableVertexAttribArray(0);
//    ////vertex shader
//    //unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
//    //glShaderSource(vs, 1, &vertexShaderSource, NULL);
//    //glCompileShader(vs);
//    ////fragment shader
//    //unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
//    //glShaderSource(fs, 1, &vertexFragmentSource, NULL);
//    //glCompileShader(fs);
//    //unsigned int shaderProgram = glCreateProgram();
//    //glAttachShader(shaderProgram, vs);
//    //glAttachShader(shaderProgram, fs);
//    //glLinkProgram(shaderProgram);
//    //glDeleteShader(vs);
//    //glDeleteShader(fs);
//    //glUseProgram(shaderProgram);
//    ///* Loop until the user closes the window */
//    //while (!glfwWindowShouldClose(window))
//    //{
//    //    /* Render here */
//    //    glClear(GL_COLOR_BUFFER_BIT);
//
//    //    glDrawArrays(GL_TRIANGLES, 0, 3);
//
//    //    /* Swap front and back buffers */
//    //    glfwSwapBuffers(window);
//
//    //    /* Poll for and process events */
//    //    glfwPollEvents();
//    //}
//    //glfwTerminate();
//    //return 0;