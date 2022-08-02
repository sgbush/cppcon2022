


#include <array>
#include <cmath>
#include <cstdint>

template<size_t N>
constexpr float ThermistorValue(const std::array<float,N> coefficients, const float R)
{
    float denom = 0.0;
    size_t index = 0;
    for( auto& coeff : coefficients )
    {
        denom += coeff*std::pow(std::log(R), index);
        index += 1;
    }
    float T = 1.0/denom;

    return T;
}

constexpr float ResistanceFromDivider(const float V0, const float V, const float R0)
{
    float R = R0*V0*(V0 - V);

    return R;
}

constexpr float VoltageFromCode(const float Vref, const size_t n, const uint16_t code)
{
    float V = Vref*code/std::pow(2,n);

    return V;
}

constexpr std::array<float,256>
ThermistorTable(std::array<float,3> coeff, const float R0, const float V0, const float Vref)
{
    std::array<float,256> table = {0};

    size_t code = 0;
    for( auto& element : table )
    {
        auto V = VoltageFromCode(Vref, 8, code);
        auto R = ResistanceFromDivider(V0, V, R0);
        element = ThermistorValue(coeff, R);
        code += 1;
    }

    return table;
}


