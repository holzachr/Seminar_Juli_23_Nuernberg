// =====================================================================================
// Module Interface Partition 'hello_world'
// =====================================================================================

/// HelloWorld.ixx

export module hello_world;

import std;

// export exportiert den gesamten Namespace inkl. allem.
export namespace MyHelloWorld
{
    int globalData{};

    void sayHello()
    {
        std::printf("Hello Module! Data is %d\n", globalData);
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
