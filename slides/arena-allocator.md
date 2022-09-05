# Dare to Use the Heap
### (With Some Caveats) <!-- .element: class="fragment" -->
### (In Non-Safety-Related Applications) <!-- .element: class="fragment" -->
---
# Using Heap in Embedded Applications
* Runtime behavior can cause heap exhaustion  <!-- .element: class="fragment" -->
* Long runtimes can cause (unsolvable) fragmentation  <!-- .element: class="fragment" -->
* Heap errors have no graceful resolution  <!-- .element: class="fragment" -->
* Many applications stick to static allocation  <!-- .element: class="fragment" -->
* Off Limits:&emsp;std::vector&emsp;std::map&emsp;std::list&emsp;std::deque   <!-- .element: class="fragment" -->
Notes: Describe the scenario where this does not apply - where allocation is only done at configuration time and not during run
---
# Using Heap in Embedded Applications
Use in allocate-once scenarios
```c++
class CalculationNode
{
    public:
    using NodeHandle = std::unique_ptr<CalculationNode>;

    private:
    size_t mNodeNumber;
    std::vector<NodeHandle> mNodeCollection;

    public:
    virtual bool Calculate()
    {
        for ( node : mNodeCollection ) node->Calculate();
    }
};
```
Notes: Point out the problem with this example - it proliferates allocations with terrible overhead for small allocations
---
# Use Arena Allocators
* For monotonic, allocate-once applications <!-- .element: class="fragment" -->
* Preferably deterministic memory usage <!-- .element: class="fragment" -->
* ...and failure is an option <!-- .element: class="fragment" -->
* See also Lakos (2017) and Steagall (2017) <!-- .element: class="fragment" -->
---
# Use Arena Allocators
Overriding the global `new` operator
```c++
void* operator new(size_t size)
{
    static constexpr size_t ArenaSize = 1'000;
    static char Arena[ArenaSize];

    auto ptr = Arena + AllocatedBytes;
    AllocatedBytes += size;
    return ptr;
}
```
Notes: Point out that the pointer really should be aligned, and should return nullptr when arena is exhausted
---
# Use Arena Allocators
Overriding `new` on a per-class basis
```c++ [1-9|11-24]
template<typename T>
class ArenaAllocator
{
    static constexpr size_t ArenaSize = 1'000;
    static char Arena[ArenaSize];

    public:
    T* allocate(size_t size) { /* ... */ }
};

class CalculationNode
{
    public:
    using NodeHandle = std::unique_ptr<CalculationNode>;

    private:
    std::vector<NodeHandle,ArenaAllocator<NodeHandle>> mCollectionOfNodes;

    void* operator new(size_t size)
    {
        ArenaAllocator<char> alloc;
        return alloc.allocate(size);
    }
};
```
Notes: This example suggests a graph calculation - lots of nodes, all very small, so lots of allocations with a lot of waste
---
# Use Arena Allocators
Demo Time
Notes: Run the example first without arena allocator, then with.  The example allocates size_t (4 bytes) until exhausted.
---
# Use Arena Allocators
It is possible to do runtime allocation while avoiding pitfalls of fragmentation, and to avoid heap overhead.  Be safe.
