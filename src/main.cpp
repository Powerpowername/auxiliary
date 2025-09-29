#include <iostream>


#include "auxiliary.hpp"

void callback(int a,int b)
{
    std::cout << a << std::endl;
}
int main()
{
    auxi::clock::blockClock clk;
    int a = 1;
    clk.untilTime(1000,callback,1,1);
    return 0;
}