# Modern C++ To Impress Your Embedded Dev Friends
**Steve Bush** - Research Fellow

Digital Innovation - Smart Products

The Procter & Gamble Company
---
# Abstract
<span style="font-size:75%;">C++ is often talked about in terms of what cannot or should not be done in the context of embedded systems.  In contrast, this talk is about some of the things that modern C++ idioms allow us to do better or more expressively than comparable operations in C.  We will cover several patterns that allow an embedded developer to express intent clearly, ease maintenance, and encourage re-use while avoiding overheads that are costly in resource-constrained systems.  Examples include initialization structures that are self-describing and IDE-friendly, small code implementations that make available sections of the C++ Standard Library for embedded use, and tools for understanding and controlling our use of limited memory resources.</span>
---
# About Me
* Research Fellow at P&G
* P&G is a global consumer goods manufacturer
    * Tide, Ariel, Crest, Bounty, Pampers,…
    * Oral-B power toothbrushes
    * Numerous smart devices (see recent CES shows)
* Embedded product developer, C++ evangelist
--
<image src="assets/PGBrands.png" style="max-width: 100%;"></image>
--

---
# Agenda
* Compile-Time Lookup Table Generation
* User-Defined Literals for Developer-Friendly Constructs
* GPIO configuration
* Lean stream-based IO
* Macro-free code {in|ex}clusion
* Relentless use of `enum`s
* Use `std::chrono` like a boss
* Create `mcu::random_device` and get `std::random` stuff for free
* Heap memory management for allocate-once 
* Override `new()` for fine-grained memory tracking
* Use linker symbols in application code
* (Optional) Free yourself from your IDE
---
# Companion Repository
[(https://github.com/sgbush/cppcon2022](https://github.com/sgbush/cppcon2022)
