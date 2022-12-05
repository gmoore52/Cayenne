#include <Engine/core.h>
#include <cayennepch.h>
#include <Engine/events/Event.h>

#ifndef CAYENNE_APPLICATION_H
#define CAYENNE_APPLICATION_H

namespace Cayenne {
    class CY_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };


    Application* CreateApplication();
}

#endif //CAYENNE_APPLICATION_H