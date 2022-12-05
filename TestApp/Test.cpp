#include <Cayenne.h>

class TestApp : public Cayenne::Application
{
public:
    TestApp()
    {

    }

    ~TestApp()
    {

    }
};

Cayenne::Application* Cayenne::CreateApplication()
{
    return new TestApp();
}