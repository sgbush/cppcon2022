# Configure GPIO Declaratively
---
# Declarative GPIO
The Old Way
```c++ [1-6|10-11|13-17]
GPIOInit_t config;
config.PinNumber = 1;
config.Mode = GPIO_MODE_PUSH_PULL;
config.Pull = GPIO_PULLUPDOWN_NONE;
config.Speed = GPIO_SPEED_MEDIUM;
config.AlternateFunc = GPIO_AF_6;

extern GPIO_Type* GPIOA;

GPIO_Configure(GPIOA, &config);
GPIO_WritePin(GPIOA, 1, GPIO_LOGIC_HIGH);

config.PinNumber = 4;
config.AlternateFunc = GPIO_AF_2;

GPIO_Configure(GPIOA, &config);
GPIO_WritePin(GPIOA, 4, GPIO_LOGIC_LOW);

```
---
# Declarative GPIO
Better Way: Strong types in an iterable container
```c++ [1-12|13-30]
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
}};
```
---
# Declarative GPIO
* Weak enums are used because they convert implicitly to their underlying type
    * *But* they are constrained to tight scope to minimize errors
* Syntax is expressive - and easy to maintain
* Easy to consolidate an entire project's IO configuration in one place
---
# Declarative GPIO
Configuring and Using IO Definitions
* Preferred: Configure all in one go
* Passing around IO Defs to delegates
---
# Declarative GPIO
Configuring
```c++
bool Configure(const GPIODEF& def)
{
    // ... chip-specific register settings ...
}
```
---
# Declarative GPIO
Configuring: the iterators way
```c++
template<typename Iter>
bool Configure(Iter begin, Iter end)
{
    while ( begin != end ) Configure(begin++);
}
```
---
# Declarative GPIO
Configuring: the ranges way
```c++
template<typename T> requires std::ranges::range<T>
bool Configure(const T& definitions)
{
    for(auto& def : definitions) Configure(def);
}
```
---
# Declarative GPIO
---
# Declarative GPIO


