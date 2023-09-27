#ifndef HEALTHPACKCONTROLLER_H
#define HEALTHPACKCONTROLLER_H
#include "abstracttilecontroller.h"
#include "GameData.h"

class HealthPackController: public AbstractTileController
{
public:
    HealthPackController(GameData * gameData);
    void performAction();

    std::shared_ptr<Tile> getTile();
    void setTile(std::shared_ptr<Tile> newTile);

private:
    std::shared_ptr<Tile> tile;
    bool consumed = false;
};

#endif // HEALTHPACKCONTROLLER_H
