#include <iostream>
#include <unistd.h>
#include <cmath>
#include <RhIO.hpp>

class MyClass
{
    public:
        MyClass() : bind("demo")
        {
            t = 0;

            // Sine amplitude parameter, can be persited if you type "save"
            bind.bindNew("a", a, RhIO::Bind::PullOnly)
                ->defaultValue(1)->comment("Sine amplitude")->persisted(true);

            // Example of boolean parameter
            bind.bindNew("shift", shift, RhIO::Bind::PullOnly)
                ->defaultValue(false);

            // Two parameters
            bind.bindNew("x", x, RhIO::Bind::PushOnly);
            bind.bindNew("y", y, RhIO::Bind::PushOnly);

            // A test command
            bind.bindFunc("test", "test command", &A::myCmd, *this);

            // A stream to debug
            bind.newStream("debug", "Debugging");
        }

        std::string myCmd(int i)
        {
            std::stringstream ss;

            ss << "i*2 = " << i*2;

            return ss.str();
        }

        void tick()
        {
            // Updating variables from RhIO
            bind.pull();

            // Doing some calculus
            x = sin(t)*a;
            if (shift) x += 10;
            y = cos(t)*a;

            // Sending variables to RhIO
            bind.push();

            t += 0.001;

            // Sending data to the debug node, can be monitored with cat debug
            bind.out("debug") << "Calling usleep! t=" << t << std::endl;
        }

    protected:
        float t, a, x, y;
        bool shift;
        RhIO::Bind bind;
};


int main()
{
    RhIO::Root.load("rhio");
    MyClass c;

    while (true) {
        c.tick();
        usleep(1000);
    }
}
