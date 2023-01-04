


#include <cstdint>
#include <array>
#include <span>
#include <concepts>

// representative of memory mapped configuration registers for the IO pin
struct GPIO_TypeDef { uint32_t ODR; };
extern GPIO_TypeDef* GPIOB;

// a type that will completely describe the function of the IO pin
using GPIODEF = \
struct IODefStuct {
    GPIO_TypeDef* GPIO;
    uint32_t PinNumber;
    enum IOFUNCTION:uint32_t { INPUT = 0, OUTPUT = 1, ALT = 2, ANALOG = 3 } Function;
    uint32_t AltFunc;
    enum IOTYPE:uint32_t { NORMAL = 0, OPENDRAIN = 1 } Type;
    enum IOSPEED:uint32_t { LOW = 0, MEDIUM = 1, HIGH = 2, VERYHIGH = 3 } Speed;
    enum IOPULL:uint32_t { NONE = 0, PULLUP = 1, PULLDOWN = 2 } Bias;
    enum IOSTATE:uint32_t { LOGIC_LOW, LOGIC_HIGH, DONT_CARE } InitialState;
};

// declarative GPIO configuration
// this will be located in flash, and the configure function will consume the data in pace, without the need to populate structs in stack memory
static const std::array<GPIODEF, 2> gpiodefs = {{
    // green LED
    {GPIOB, 0, 
    GPIODEF::IOFUNCTION::OUTPUT, 1, 
    GPIODEF::IOTYPE::NORMAL, 
    GPIODEF::IOSPEED::LOW, 
    GPIODEF::IOPULL::NONE, 
    GPIODEF::IOSTATE::LOGIC_LOW},
    // red LED
    {GPIOB, 2, 
    GPIODEF::IOFUNCTION::OUTPUT, 1, 
    GPIODEF::IOTYPE::NORMAL, 
    GPIODEF::IOSPEED::LOW, 
    GPIODEF::IOPULL::NONE, 
    GPIODEF::IOSTATE::LOGIC_LOW},

    // ... and so on

}};



// represenative of the hardware configuration register set
struct SPI_TypeDef {};

// a less than optimal example - the code has to somehow know how to manipulate the chipselect pin
struct SPIBus
{
    SPIBus(SPI_TypeDef* peripheral) {  }
};

struct SPIProtocol
{
    enum class SPIMode { Mode1, Mode2, Mode3, Mode4 };
    SPIProtocol(SPIMode mode, uint32_t speed) {  }
};

struct SPIConnection
{
    SPIConnection(const SPIBus& bus, const SPIProtocol& conn, const GPIODEF& chipselect) {  }
};



// a better implementation - the logic level of 'assert' is determined in the coding of the functor
class GPIOAssertFunctor
{
    const GPIODEF& mGPIO;

    public:
    constexpr GPIOAssertFunctor(const GPIODEF& io) : mGPIO(io) {}
    void operator()(bool enable) const
    {
        if ( enable )
        {
            mGPIO.GPIO->ODR |= ( 0b1 << mGPIO.PinNumber );
        }
        else
        {
            mGPIO.GPIO->ODR &= ~( 0b1 << mGPIO.PinNumber );
        }
    }
};


struct SPIConnection2
{
    const GPIOAssertFunctor& mEnableFunction;

    SPIConnection2(const SPIBus& bus, const SPIProtocol& conn, const GPIOAssertFunctor& enable) : mEnableFunction(enable) {  }

    bool ReadWrite(std::span<char> outdata, std::span<char> indata, size_t length)
    {
        mEnableFunction(true);
    }
};



// a more expressive implementation
// uses more code, but the meaning of 'assert' is clearly stated in the declaration (see below)
class AssertType {};
class AssertTypeLogicHigh : public AssertType { static constexpr bool ValueWhenAsserted = true; };
class AssertTypeLogicLow : public AssertType { static constexpr bool ValueWhenAsserted = false; };

template<typename Assert> requires std::derived_from<Assert,AssertType>
class GPIOAssertFunctor2
{
    const GPIODEF& mGPIO;
    public:
    constexpr GPIOAssertFunctor2(const GPIODEF& io) : mGPIO(io) {}
    void operator()(bool enable)
    {
        if ( enable == Assert::ValueWhenAsserted )
        {
            mGPIO.GPIO->ODR |= ( 0b1 << mGPIO.PinNumber );
        }
        else
        {
            mGPIO.GPIO->ODR &= ~( 0b1 << mGPIO.PinNumber );
        }
    }
};


template<typename T> requires std::derived_from<T,AssertType>
struct SPIConnection3
{
    const GPIOAssertFunctor2<T>& mEnableFunction;

    SPIConnection3(const SPIBus& bus, const SPIProtocol& conn, const GPIOAssertFunctor2<T>& enable) : mEnableFunction(enable) {  }

    bool ReadWrite(std::span<char> outdata, std::span<char> indata, size_t length)
    {
        mEnableFunction(true);
    }
};




extern SPI_TypeDef* SPI1;
const GPIOAssertFunctor2<AssertTypeLogicLow> MemoryChipSelect;


auto bus = SPIBus(SPI1);
auto protocol = SPIProtocol(SPIProtocol::SPIMode::Mode1, 4'000'000);
auto connection = SPIConnection3(bus, protocol, MemoryChipSelect);