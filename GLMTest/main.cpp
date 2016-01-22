#include <iostream>

// vec3, vec4, ivec4, mat4
#include <glm/glm.hpp>
// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::to_string
#include <glm/gtx/string_cast.hpp>

int main(int argc, char *argv[])
{

    glm::vec4 vec0(1,2,3,4) ;
    glm::mat4 mat0;
    glm::vec3 vec1(1,0,0);
    std::cout<< glm::to_string(vec0) <<std::endl;
    glm::rotate(mat0,1.0f,vec1);

    glm::mat4 mat4(
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,16
        );

    std::cout
        <<to_string( mat4 )
        <<std::endl;

    std::cout<< to_string( mat4[0] ) <<std::endl;

    auto look_at=glm::lookAt(glm::vec3(0,0,-1),glm::vec3(0,0,0),glm::vec3(0,1,0));
    auto ortho_=glm::ortho<float>(-1,1,-1,1,0,2);

    std::cout
        <<to_string( look_at*ortho_ )
        <<std::endl;

    return 0;
    (void)argc;(void)argv;

}




