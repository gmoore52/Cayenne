#include <Engine/core.h>
#ifndef CAYENNE_DATALOADER_H
#define CAYENNE_DATALOADER_H

namespace Cayenne
{
    class CY_API DataLoader{
    public:
        static unsigned char* LoadImage(const std::string& f_path);
    };
}

#endif //CAYENNE_DATALOADER_H
