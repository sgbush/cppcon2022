Implement `std::random_device` 

and Get Free ~~Beer~~ Library Code
---
# Scenario
* You need a random number generator with a multimodal probability distribution

<image src="assets/bimodal.png" style="width:600px;"></image> 
---
# Scenario
* This gives a random walk with occasional large changes

<image src="assets/randomwalk.png" style="width:700px;"></image> 
Notes: This is not so far fetched since we work for a historic candle company
---
<image src="assets/luminary.jpeg" style="width:500px;"></image> 
---
# Fun with Random Numbers
```c++
class BimodalDistrubution
{
    public:
    using ModeParamsType = std::normal_distribution<float>::param_type;

    private:
    std::normal_distribution<float> mFirstModeDistribution;
    std::normal_distribution<float> mSecondModeDistribution;
    std::uniform_real_distribution<float> mWeightingDistribution;
    float mMode1Weight;
```
Notes: We do this to quickly prototype a solution. Point out the two normal distributions, and the weighting method between the two
---
# Fun with Random Numbers
```c++
class BimodalDistrubution
{
    ...
    template<typename Generator>
    float operator()(Generator& device)
    {
        auto x = mWeightingDistribution(device);
        float result;

        if ( std::abs(x) < mMode1Weight )
        {
            result = mFirstModeDistribution(device);
        }
        else
        {
            result =  signum(x)*mSecondModeDistribution(device);
        }

        return result;
    }
```
Notes: Point out how the third distribution is used to pick and choose between the primary mode and secondary
---
# Fun with Random Numbers
```c++
auto dev = std::random_device();
auto dist = BimodalDistribution();
float x = dist(dev);
```
---
# Fun with Random Numbers
```c++ [1-3|11-15|17-21]
namespace mcu
{
class random_device
{
    public:
    using result_type = unsigned int;
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    constexpr double entropy() const noexcept { return 32.0; }

    random_device()
    {
        RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
        RNG->CR |= RNG_CR_RNGEN;
    }
    random_device& operator=(const random_device& other) = delete;
    result_type operator()()
    {
        while ( !(RNG->SR & RNG_SR_DRDY) ) continue;
        return RNG->DR;
    }
};
}
```
Notes: However, we can run the code nearly unchanged if we have a random_device (hardware available on many MCUs). Since the library defines the std::random_device::operator() inline, we must create a random_device in our own namespace
---
# Fun with Random Numbers
```c++
auto dev = mcu::random_device();
auto dist = BimodalDistribution();
float x = dist(dev);
```
---
# Fun with Random Numbers
Demo Time