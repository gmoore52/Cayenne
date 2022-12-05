//
// Created by gavin on 12/4/2022.
//

#ifndef CAYENNE_APPLICATION_H
#define CAYENNE_APPLICATION_H


#include "core.h"
//#include "events/Event.h"

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
