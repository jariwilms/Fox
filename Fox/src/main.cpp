#include "stdafx.hpp"

#include "Fox/Application.hpp"

template<typename T>
class CRTP
{
public:
    void print()
    {
        static_cast<T&>(*this)._print();
    }

private:
    friend T;

    CRTP() = default;
};
class MyClass : public CRTP<MyClass>
{
public:

    MyClass() = default;

protected:
    friend CRTP<MyClass>;

    void _print()
    {
        std::cout << "MyClass";
    }
};


int main(int argc, char* argv[])
{
    auto application = std::make_unique<fox::Application>(argc, argv);
    application->run();

    return EXIT_SUCCESS;
}
