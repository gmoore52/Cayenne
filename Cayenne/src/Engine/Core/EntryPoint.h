#ifndef CAYENNE_ENTRYPOINT_H
#define CAYENNE_ENTRYPOINT_H

#ifdef CY_PLATFORM_WINDOWS

    extern Cayenne::Application* Cayenne::CreateApplication();

    int main(int argc, char** argv)
    {
        Cayenne::Log::Init();
        CY_CORE_WARN("Log Initialized...");
        CY_INFO("Client Log Initialized...");

        auto app = Cayenne::CreateApplication();
        app->Run();
        delete app;
    }

#elifdef CY_PLATFORM_LINUX

    extern Cayenne::Application* Cayenne::CreateApplication();

    int main(int argc, char** argv)
    {
        Cayenne::Log::Init();
        CY_CORE_WARN("Log Initialized...");
        CY_INFO("Client Log Initialized...");

        auto app = Cayenne::CreateApplication();
        app->Run();
        delete app;
    }

#endif


#endif //CAYENNE_ENTRYPOINT_H
