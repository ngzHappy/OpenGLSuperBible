#include <iostream>
#include <cstddef>
#include <utility>
#include <type_traits>

class alignas(32) Data{};

class Data1{
public:
    alignas(double) float b;
    alignas(int) int a;
};

struct alignas(32) TestReturnType {
    int value;
};

TestReturnType test() { return{ 12 }; }

struct alignas(16) Alignas16Float {
    float value;
};

struct alignas(16) STD140Test{
    float scale;
    alignas(16) float translation[3];
    alignas(16) Alignas16Float rotate[3];
    alignas(16) float matrix[4][4];
};

int main(int argc, char *argv[])
{

    std::cout<<offsetof(STD140Test,scale)<<std::endl;
    std::cout<<offsetof(STD140Test,translation)<<std::endl;
    std::cout<<offsetof(STD140Test,rotate)<<std::endl;
    std::cout<<offsetof(STD140Test,matrix)<<std::endl;

    std::cout << sizeof(Data) <<std::endl;
    std::cout << offsetof(Data1,a) <<std::endl;
    std::cout << offsetof(Data1,b) <<std::endl;
    std::cout << alignof(std::result_of_t< decltype(&test)() >) <<std::endl;
    
    return 0;
    (void)argc;
    (void)argv;
    
}


