#include <iostream>

// vec3, vec4, ivec4, mat4
#include <glm/glm.hpp>
// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::to_string
#include <glm/gtx/string_cast.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>


#if !defined(VALUE)
#define VALUE( ... ) (/**/__VA_ARGS__/**/)
#endif

#if !defined(ROW_AS_COLUMN_MAT4X4)
#define ROW_AS_COLUMN_MAT4X4( \
_00,_01,_02,_03,\
_10,_11,_12,_13,\
_20,_21,_22,_23,\
_30,_31,_32,_33 ) /**/\
(_00),(_10),(_20),(_30),\
(_01),(_11),(_21),(_31),\
(_02),(_12),(_22),(_32),\
(_03),(_13),(_23),(_33) /**/
#endif

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

    glm::value_ptr( mat4 );

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




