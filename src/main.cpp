#include"game.hpp"

#include"components/Color.hpp"
#include"components/Gravity.hpp"
#include"components/RigidBody.hpp"
#include"components/Transform.hpp"

#include"systems/PhysicsSystem.hpp"
#include"systems/RenderSystem.hpp"

#include<utils/shader.hpp>
#include<utils/Texture.hpp>
#include<utils/Services.hpp>

#include<chrono>
#include<random>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 1024;

const float sensitivity = 0.1f;
const float cameraSpeed = 5.0f;

const float MAX_FOV = 140.0f;
const float MIN_FOV = 60.0f;;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float mouseLastX = WIDTH / 2;
float mouseLastY = HEIGHT / 2;
bool mouseInitMovement = true;
float yaw = -90.0f;
float pitch = 0.0f;

float fov = 90.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraFront * cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraFront * cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
}

void mouse_callback(GLFWwindow* window, double x, double y) {
    if (mouseInitMovement) {
        mouseLastX = x;
        mouseLastY = y;
        mouseInitMovement = false;
    }

    float xoffset = x - mouseLastX;
    float yoffset = mouseLastY - y;
    mouseLastX = x;
    mouseLastY = y;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double x, double y) {
    fov -= (float)y;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 110.0f) fov = 110.0f;
}

int main(int argc, char** argv) {
    // game gameWorld = game{"test", 50, 50, 1280, 720, false};
    // manager.init();
    // std::cout<<"123";
    // manager.RegisterComponent<Gravity>();
    // manager.RegisterComponent<Transform>();
    // manager.RegisterComponent<RigidBody>();
    // manager.RegisterComponent<Color>();
    
    // auto physicsSystem = manager.RegisterSystem<PhysicsSystem>();
    // {
    //     Signature signature;
    //     signature.set(manager.GetComponentType<Gravity>());
    //     signature.set(manager.GetComponentType<Transform>());
    //     signature.set(manager.GetComponentType<RigidBody>());
    //     manager.SetSystemSignature<PhysicsSystem>(signature);
    // }
    // physicsSystem->init();

    // auto renderSystem = manager.RegisterSystem<RenderSystem>();
    // {
    //     Signature signature;
    //     signature.set(manager.GetComponentType<Transform>());
    //     signature.set(manager.GetComponentType<Color>());
    //     manager.SetSystemSignature<RenderSystem>(signature);
    // }

    // renderSystem->init();

    // std::vector<Entity> entities(1);

    // std::default_random_engine generator;
	// std::uniform_real_distribution<float> randPosition(0.0f, 1900.0f);
	// std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	// std::uniform_real_distribution<float> randScale(500.0f, 1000.0f);
	// std::uniform_int_distribution<uint8_t> randColor(0, 255);

    // float scale = randScale(generator);

    // for (auto& entity : entities) {
    //     entity = manager.CreateEntity();
    //     manager.AddComponent<Gravity>(entity, {.g = 10});
    //     manager.AddComponent<Transform>(
    //         entity, 
    //         {
    //             .position = vec(randPosition(generator), 0.0f),
    //             .rotation = 0,
    //             .scale = vec(scale, scale)
    //         }
    //     );
    //     manager.AddComponent<RigidBody>(
    //         entity, 
    //         {
    //             .velocity = vec(),
    //             .acceleration = vec()
    //         }
    //     );
    //     manager.AddComponent<Color>(
    //         entity,
    //         {
    //             .r = randColor(generator),
    //             .g = randColor(generator),
    //             .b = randColor(generator),
    //             .a = 0xff
    //         }
    //     );
    // }

    // float dt = 0.0f;

    // bool quit = false;

    // SDL_Event e;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);
    if (!window) {
        std::cout<<"Failed to create window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to init glad";
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  -1.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // unsigned int indices[] = {
    //     0, 1, 3,
    //     1, 2, 3
    // };



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Services::loadShader("src/shader/vertex.glsl", "src/shader/fragment.glsl", "default");
    Services::loadTexture("build/img/container.jpg", false, "container");
    Services::loadTexture("build/img/Inazuma_Shogunate.png", true, "icon");

    Shader* shader = Services::getShader("default");

    shader->use();
    glUniform1i(glGetUniformLocation(shader->id, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shader->id, "texture2"), 1);
    // glUniform1f(glGetUniformLocation(shader->id, "mixtexture"), 0.2);




    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader->id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(shader->id, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Services::getTexture("container")->id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Services::getTexture("icon")->id);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::rotate(
                glm::translate(glm::mat4(1.0f), cubePositions[i]), 
                (float)glfwGetTime() * glm::radians(20.0f * (i + 1)), 
                glm::vec3(0.5f, 1.0f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shader->id, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();
    }



    // while (!quit) {
    //     // while (SDL_PollEvent(&e) != 0) {
    //     //     if (e.type == SDL_QUIT) quit = true;
    //     // }
    //     // auto startTime = std::chrono::high_resolution_clock::now();
    //     // physicsSystem->update(dt);
        
    //     // renderSystem->update(dt);
    //     // auto stopTime = std::chrono::high_resolution_clock::now();
    //     // dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();

    // }

    // gameWorld.~game();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}