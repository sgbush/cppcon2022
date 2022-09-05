
#include <cstddef>
#include <vector>
#include <memory>

template<typename T>
class ArenaAllocator
{
    static constexpr size_t ArenaSize = 1000;
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


