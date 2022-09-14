<section data-background="assets/cppcon-banner.png" data-background-size="contain">
---
# Modern C++ To Impress Your Embedded Dev Friends
**Steve Bush** - Research Fellow

Digital Innovation - Smart Products

The Procter & Gamble Company
---
# Abstract
<span style="font-size:75%;">C++ is often talked about in terms of what cannot or should not be done in the context of embedded systems.  In contrast, this talk is about some of the things that modern C++ idioms allow us to do better or more expressively than comparable operations in C.  We will cover several patterns that allow an embedded developer to express intent clearly, ease maintenance, and encourage re-use while avoiding overheads that are costly in resource-constrained systems.  Examples include initialization structures that are self-describing and IDE-friendly, small code implementations that make available sections of the C++ Standard Library for embedded use, and tools for understanding and controlling our use of limited memory resources.</span>
---
# About Me
* Research Fellow at Procter & Gamble
* P&G is a global consumer goods manufacturer
* Embedded product developer, C++ evangelist
---
<image src="assets/PGBrands.png" style="max-width: 100%;"></image>
---
<image src="assets/CESProducts.png" style="max-width: 100%;"></image> 
---
# Objective
Making embedded code easier (and more pleasant) to write and maintain
---
# Agenda
* GPIO configuration
* Compile-Time Lookup Table Generation
* Developer-Friendly Numeric Constructs
* Lean stream-based IO
* Heap memory management for allocate-once 
* Use `std::chrono` like a boss
* A `std::random` topic
---
# Companion Repository
[(https://github.com/sgbush/cppcon2022](https://github.com/sgbush/cppcon2022)
