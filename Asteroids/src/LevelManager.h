#include "RenderObject.h"

#include <vector>

class LevelManager
{
public:
    std::vector<RenderObject> renderObjects;

    LevelManager();
    void addRenderObject(RenderObject renderObject);
    void tick();
private:
};
