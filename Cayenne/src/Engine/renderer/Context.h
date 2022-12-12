

#ifndef CAYENNE_CONTEXT_H
#define CAYENNE_CONTEXT_H

namespace Cayenne
{
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}

#endif //CAYENNE_CONTEXT_H
