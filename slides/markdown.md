# Modern C++ To Impress Your Embedded Dev Friends
**Steve Bush** - Research Fellow

Digital Innovation - Smart Products

The Procter & Gamble Company
---
# Abstract
C++ is often talked about in terms of what cannot or should not be done in the context of embedded systems.  In contrast, this talk is about some of the things that modern C++ idioms allow us to do better or more expressively than comparable operations in C.  We will cover several patterns that allow an embedded developer to express intent clearly, ease maintenance, and encourage re-use while avoiding overheads that are costly in resource-constrained systems.  Examples include initialization structures that are self-describing and IDE-friendly, small code implementations that make available sections of the C++ Standard Library for embedded use, and tools for understanding and controlling our use of limited memory resources.
---
# About Me
* Research Fellow at P&G
* P&G is a global consumer goods manufacturer
    * Tide, Ariel, Crest, Bounty, Pampers,…
    * Oral-B power toothbrushes
    * Numerous smart devices (see recent CES shows)
* Embedded product developer, C++ evangelist
---
# Agenda
* `constexpr` for Lookup Table Generation
* `constexpr` for Developer-Friendly Constructs
* GPIO configuration using `std::array`
* Lean stream-based IO
* Macro-free code {in|ex}clusion
* Heap memory management for allocate-once 
* Override `new()` for fine-grained memory tracking
* Relentless use of `enum`s
* Use `std::chrono` like a boss
* Create `mcu::random_device` and get `random` stuff for free
* Use linker symbols in application code
---
# Companion Repository
[(https://github.com/sgbush/cppcon2022](https://github.com/sgbush/cppcon2022)
---
# Compiler-Driven Lookup Table Generation
Why: Separate maintenance of spreadsheets, etc., is painful and prone to error
```c++
```
Some considerations
* Constants in embedded system must be carefully crafted to end up (usually) in the `.rodata` section
    * this results in constants being placed in flash - and not copied to RAM
* It is common for hardware and firmware to have to evolve together
    * example: changing resistor values to tune the performance of the system
---
Better: Incorporate governing equations into the code, and let the compiler generate constant tables
* 
---
# Developer-Friendly Numeric Structures
---
## Code
```c++[1|2-4]
void Function(int value)
{
    return;
}
```




