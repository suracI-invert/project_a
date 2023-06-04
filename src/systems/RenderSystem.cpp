#include"RenderSystem.hpp"

#include"components/Transform.hpp"
#include"components/Renderable.hpp"


void RenderSystem::init(Shader* shader) {
    this->shader = shader;

    unsigned int VBO, EBO;
    
    // float vertices[] = {
    //     //pos       //tex
    //     1.0f, 1.0f, 1.0f, 1.0f, //top right
    //     1.0f, 0.0f, 1.0f, 0.0f, //bottom right
    //     0.0f, 0.0f, 0.0f, 0.0f, //bottom left
    //     0.0f, 1.0f, 0.0f, 1.0f  //top left
    // };

    // unsigned int indices[] = {
    //     0, 1, 2,    //first triangle
    //     1, 2, 3     //second triangle
    // };

    float vertices [] = {
        ///pos            ///tex
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   ///top right back       ///> 0
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   ///bottom right back    ///> 1
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   ///bottom left back     ///> 2
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   ///top left back        ///> 3

        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,   ///top right front      ///> 4
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   ///bottom right front   ///> 5
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   ///bottom left front    ///> 6
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f    ///top left front       ///> 7
    };

    unsigned int indices[] = {
        2, 1, 0, 0, 3, 2,   ///> back plane
        6, 5, 4, 4, 7, 6,   ///> front plane
        0, 4, 5, 0, 5, 1,   ///> right plane
        0, 4, 7, 0, 7, 3,   ///> top plane
        3, 2, 6, 3, 7, 6,   ///> left plane
        6, 2, 1, 6, 1, 5    ///> bottom plane
    };

    // float vertices[] = {
    //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,    2
    //     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,     1
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,     0
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,     0
    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,    3
    //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,    2

    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    6
    //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,     5
    //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,     4
    //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,     4
    //     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,    7
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    6

    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    5
    //     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    // };

    glGenVertexArrays(1, &this->quadVAO);
    glBindVertexArray(this->quadVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RenderSystem::update(float dt, const glm::mat4& view, float fov, unsigned int WIDTH, unsigned int HEIGHT) {
    this->shader->use();
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    this->shader->setMatrix4("projection", projection);
    this->shader->setMatrix4("view", view);


    for (const auto& entity : entities) {
        const auto& transform = ECS::GetComponent<Transform>(entity);
        const auto& renderable = ECS::GetComponent<Renderable>(entity);
        float scale = transform.scale;
        glm::vec3 size = glm::vec3(scale, scale, scale);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
        model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5 * size.y, -0.5 * size.z));
        model = glm::scale(model, size);
        this->shader->setMatrix4("model", model);
        glActiveTexture(GL_TEXTURE0);
        renderable.texture->bind();
        glBindVertexArray(this->quadVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}

RenderSystem::~RenderSystem() {
    glDeleteBuffers(1, &this->quadVAO);
    std::cout<<"Free VAO\n";
}