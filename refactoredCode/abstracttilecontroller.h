#ifndef ABSTRACTTILECONTROLLER_H
#define ABSTRACTTILECONTROLLER_H
#include "GameData.h"
#include "qgraphicsscene.h"

class AbstractTileController
{
public:
    AbstractTileController(GameData * gameData);
    virtual ~AbstractTileController() = default;
    virtual void performAction();
    GameData * gameData;


private:
};

#endif // ABSTRACTTILECONTROLLER_H
