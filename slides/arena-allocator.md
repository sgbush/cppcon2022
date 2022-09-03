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
```c++
void* operator new(size_t size)
{
    constexpr size_t ArenaSize = 1'000'000;
    static char Arena[ArenaSize];

    AllocatedBytes += size;
    return (Arena + AllocatedBytes);
}
```