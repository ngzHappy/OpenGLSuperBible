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

int main(int argc, char *argv[])
{
    std::cout << sizeof(Data) <<std::endl;
    std::cout << offsetof(Data1,a) <<std::endl;
    std::cout << offsetof(Data1,b) <<std::endl;
    std::cout << alignof(std::result_of_t< decltype(&test)() >) <<std::endl;
    
    return 0;
    (void)argc;
    (void)argv;
    
}


