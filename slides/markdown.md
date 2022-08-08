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
* Compile-Time Lookup Table Generation
* User-Defined Literals for Developer-Friendly Constructs
* GPIO configuration
* Lean stream-based IO
* Macro-free code {in|ex}clusion
* Relentless use of `enum`s
* Use `std::chrono` like a boss
* Create `mcu::random_device` and get `random` stuff for free
* Heap memory management for allocate-once 
* Override `new()` for fine-grained memory tracking
* Use linker symbols in application code
---
# Companion Repository
[(https://github.com/sgbush/cppcon2022](https://github.com/sgbush/cppcon2022)
---
# Create Lookup Tables Using Compile-Time Expressions
---
# Compiler-Driven Lookup Table Generation
The Old Way
```c++
const float TemperatureFromThermistor[] = { 1.23456, ... };
```
* Generate via spreadsheet and copy and paste
* Generate via script and copy and paste
* Generate via script and incorporate into build system
Notes: Where does this table come from?  It must be maintained separately via spreadsheet or script.  Often, we change component values which necessitates re-creating lookup tables.  What if we check in a source code change and recompile, and it is all taken care of?
---
# Compiler-Driven Lookup Table Generation
Some considerations
* Constants in embedded system must be carefully crafted to end up (usually) in the `.rodata` section
    * this results in constants being placed in flash - and not copied to RAM
* It is common for hardware and firmware to have to evolve together
    * example: changing resistor values to tune the performance of the system
[image](image url "https://www.allaboutcircuits.com/uploads/articles/TI_IA_thermistor_figure1.jpg")
<img src="https://www.allaboutcircuits.com/uploads/articles/TI_IA_thermistor_figure1.jpg">
---
# Compiler-Driven Lookup Table Generation
Better: Incorporate governing equations into the code, and let the compiler generate constant tables
` $$ 1/T = A + B ln(R) + C ln(R)^3 $$`
` $$ R =  $$ `
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




