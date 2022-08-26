



#pragma once

#include <random>
#include <cmath>
#include <concepts>


template<typename RandomDeviceType>
class BimodalDistrubution
{
    public:
    using ModeParamsType = std::normal_distribution<float>::param_type;

    private:
    RandomDeviceType mEntropySource;
    std::normal_distribution<float> mFirstModeDistribution;
    std::normal_distribution<float> mSecondModeDistribution;
    std::uniform_real_distribution<float> mWeightingDistribution;
    float mMode1Weight;
    
    public:
    BimodalDistrubution() : BimodalDistrubution( ModeParamsType(0.0f,1.0f), ModeParamsType(5.0f,3.0f), 0.7f ) {}
    BimodalDistrubution(const ModeParamsType& mode1, const ModeParamsType& mode2, float weight)
        : mEntropySource(),
        mFirstModeDistribution(mode1),
        mSecondModeDistribution(mode2),
        mWeightingDistribution(-1.0f, 1.0f),
        mMode1Weight(weight)
    {
    }

    static float signum(float u) { return ( (u > 0.0f) - (u < 0.0f) ); }

    float operator()()
    {
        auto x = mWeightingDistribution(mEntropySource);
        float result;

        if ( std::abs(x) < mMode1Weight )
        {
            result = mFirstModeDistribution(mEntropySource);
        }
        else
        {
            result =  signum(x)*mSecondModeDistribution(mEntropySource);
        }

        return result;
    }
};

