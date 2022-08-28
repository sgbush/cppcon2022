



#include <chrono>
#include <functional>
#include <string_view>
#include <cmath>

#include "mcu/filestream.hpp"



using namespace std::chrono;

template<typename T>
void Benchmark(const std::function<void()>& f, const std::string_view label)
{
    const auto start = high_resolution_clock::now();
    f();        // <--- function to be timed
    auto elapsed = high_resolution_clock::now() - start;

    mcu::debug << label << " : " << mcu::FileStream::RadixEnum::Decimal << duration_cast<T>( elapsed ) << "\r\n";
}

void MyExpensiveFunction()
{
    constexpr size_t length = 100;
    for(size_t index = 0; index < length; index += 1)
    {
        float arg = index/length;
        std::exp( std::sin(arg) + std::cos(arg) );
    }
}

int main(int , char** )
{    
    mcu::debug << "Application start...\r\n";

    auto timeout = high_resolution_clock::now() + seconds(1);

    while (true)
    {
        Benchmark<microseconds>(MyExpensiveFunction, "Trig function");

        while ( high_resolution_clock::now() < timeout ) continue;
        timeout = high_resolution_clock::now() + seconds(1);
    }

    std::exit(0);
}



