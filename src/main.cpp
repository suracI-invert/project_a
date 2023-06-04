#include"utils/shader.hpp"
#include"utils/Texture.hpp"
#include"utils/Services.hpp"

#include"systems/PhysicsSystem.hpp"
#include"systems/RenderSystem.hpp"

#include<chrono>
#include<random>

#include"components/Renderable.hpp"
#include"components/Gravity.hpp"
#include"components/RigidBody.hpp"
#include"components/Transform.hpp"


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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) cameraPos += cameraUp * cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) cameraPos -= cameraUp * cameraSpeed * deltaTime;
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

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, direction));
    cameraUp = glm::cross(direction, cameraRight);
}

void scroll_callback(GLFWwindow* window, double x, double y) {
    fov -= (float)y;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 110.0f) fov = 110.0f;
}

int main(int argc, char** argv) {
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

    Services::loadShader("src/shader/vertex.glsl", "src/shader/fragment.glsl", "default");
    Services::loadTexture("build/img/container.jpg", false, "container");

    ECS::init();

    // ECS::RegisterComponent<Gravity>();
    ECS::RegisterComponent<Transform>();
    ECS::RegisterComponent<RigidBody>();
    ECS::RegisterComponent<Renderable>();
    
    auto physicsSystem = ECS::RegisterSystem<PhysicsSystem>();
    {
        Signature signature;
        // signature.set(ECS::GetComponentType<Gravity>());
        signature.set(ECS::GetComponentType<Transform>());
        signature.set(ECS::GetComponentType<RigidBody>());
        ECS::SetSystemSignature<PhysicsSystem>(signature);
    }
    physicsSystem->init();

    auto renderSystem = ECS::RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(ECS::GetComponentType<Transform>());
        signature.set(ECS::GetComponentType<Renderable>());
        ECS::SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->init(Services::getShader("default"));

    Entity entities[10];

    std::default_random_engine generator;
	std::uniform_real_distribution<float> randPositionX(0.0f, 5.0f);
	std::uniform_real_distribution<float> randPositionY(0.0f, 5.0f);
	std::uniform_real_distribution<float> randPositionZ(-5.0f, 5.0f);
	std::uniform_real_distribution<float> randRotation(5.0f, 20.0f);
	std::uniform_real_distribution<float> randScale(1.0f, 10.0f);

    float scale = randScale(generator);

    for (auto& entity : entities) {
        entity = ECS::CreateEntity();
        // ECS::AddComponent<Gravity>(entity, {.g = 10});
        ECS::AddComponent<Transform>(
            entity, 
            {
                .position = glm::vec3(randPositionX(generator), randPositionY(generator), randPositionZ(generator)),
                .rotation = randRotation(generator),
                .scale = scale
            }
        );
        ECS::AddComponent<RigidBody>(
            entity, 
            {
                .velocity = glm::vec3(),
                .acceleration = 0.0f
            }
        );
        ECS::AddComponent<Renderable>(
            entity, {Services::getTexture("container")}
        );
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        
        physicsSystem->update(lastFrame);
        renderSystem->update(lastFrame, view, fov, WIDTH, HEIGHT);


        glfwSwapBuffers(window);
        glfwPollEvents();

        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();
    }

    glfwTerminate();
    return 0;
}