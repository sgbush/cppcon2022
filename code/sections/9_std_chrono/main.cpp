



#include <chrono>
#include <functional>
#include <string_view>
#include <iostream>
#include <cmath>

#include "../4_lean_stream_io/filestream.hpp"



using namespace std::chrono;

std::ostream& operator<<(std::ostream& stream, microseconds interval)
{
    stream << interval.count() << "us";

    return stream;
}

// implement our own now() function, which in the embedded application would be based on the hardware timer
std::chrono::time_point<std::chrono::high_resolution_clock> std::chrono::high_resolution_clock::now()
{
    return std::chrono::time_point<std::chrono::high_resolution_clock>(std::chrono::milliseconds(0));
}

template<typename T>
void Benchmark(const std::function<void()>& f, const std::string_view label)
{
    const auto start = high_resolution_clock::now();
    f();        // <--- function to be timed
    auto elapsed = high_resolution_clock::now() - start;

    std::cout << label << " : " << duration_cast<T>( elapsed ) << "\r\n";
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
    Benchmark<microseconds>(MyExpensiveFunction, "Trig function");

    std::exit(0);
}
