#include <iostream>
#include <unistd.h>
#include <cmath>
#include <RhIO.hpp>

class A
{
    public:
        A() : bind("demo")
        {
            t = 0;

            bind.bindNew("a", a, RhIO::Bind::PullOnly)
                ->defaultValue(1)->comment("Sine amplitude")->persisted(true);

            bind.bindNew("shift", shift, RhIO::Bind::PullOnly)
                ->defaultValue(false);

            bind.bindNew("x", x, RhIO::Bind::PushOnly);
            bind.bindNew("y", y, RhIO::Bind::PushOnly);

            bind.bindFunc("test", "test command", &A::myCmd, *this);

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
            bind.pull();

            x = sin(t)*a;
            if (shift) x += 10;
            y = cos(t)*a;
            printf("%f\n", x);

            bind.push();
            t += 0.001;
            bind.out("debug") << "Calling usleep! t=" << t << std::endl;
            usleep(1000);
        }

    protected:
        float t, a, x, y;
        bool shift;
        RhIO::Bind bind;
};


int main()
{
    RhIO::Root.load("rhio");
    A a;

    while (true) {
        a.tick();
    }
}
