#pragma once

#include"ecs.hpp"

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"utils/Services.hpp"

class RenderSystem : public System {
    private:
        Shader* shader;
        unsigned int quadVAO;
    public:
        void init(Shader* shader);
        void update(float dt, const glm::mat4& view, float fov, unsigned int WIDTH, unsigned int HEIGHT);
        ~RenderSystem();
};