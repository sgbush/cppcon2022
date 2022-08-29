

#include <cstddef>
#include <cstdlib>
#include <vector>
#include <memory>
#include <cmath>
#include <malloc.h>
#include <iostream>

static size_t AllocatedBytes = 0;

constexpr bool use_arena = false;

void* operator new(size_t size)
{
    constexpr size_t ArenaSize = 1'000'000;
    static char Arena[ArenaSize];

    AllocatedBytes += size;
    if constexpr ( use_arena )
    {
        return (Arena + AllocatedBytes);
    }
    else
    {
        return malloc(size);
    }
}

void operator delete(void* ptr)
{
    if constexpr ( !use_arena )
    {
        free(ptr);
    }
}

void operator delete(void* ptr, size_t )
{
    if constexpr ( !use_arena )
    {
        free(ptr);
    }
}


class CalculationNode
{
    public:
    using NodeHandle = std::unique_ptr<CalculationNode>;

    public:
    static size_t NodeCount;

    private:
    size_t mNodeNumber;
    std::vector<NodeHandle> mNodeCollection;

    public:
    CalculationNode() : mNodeNumber(NodeCount++), mNodeCollection() {}
    CalculationNode(size_t levels)
    {
        size_t index = 1;
        while ( index <= levels )
        {
            this->AddNodes(std::pow(2,levels));
            index += 1;
        }
    }

    void AddNodes(size_t count)
    {
        size_t index = 0;
        while ( index < count )
        {
            this->mNodeCollection.emplace_back( std::make_unique<CalculationNode>() );
            index += 1;
        }
    }

};

size_t CalculationNode::NodeCount = 0;

int main(int , char** )
{

    CalculationNode* tree = new CalculationNode(10);

    std::cout << "Node count=" << CalculationNode::NodeCount << "\r\n";
    std::cout << "Class size=" << sizeof(CalculationNode) << "( " << sizeof(std::vector<CalculationNode::NodeHandle>) << " + " << sizeof(size_t) << " )" << "\r\n";
    std::cout << "Total allocation=" << AllocatedBytes << "\r\n";
    std::cout << "Useful allocation=" << CalculationNode::NodeCount*sizeof(CalculationNode) << "\r\n";
    std::cout << "Overhead=" << static_cast<float>((AllocatedBytes - CalculationNode::NodeCount*sizeof(CalculationNode)))/static_cast<float>(AllocatedBytes) << "\r\n";

    std::exit(0);
}

