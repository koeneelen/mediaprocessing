#ifndef TILECONTROLLER_H
#define TILECONTROLLER_H
#include "abstracttilecontroller.h"

class TileController: public AbstractTileController
{
public:
    TileController(GameData * gameData);
    ~TileController() override = default;
    void performAction();

    std::shared_ptr<Tile> getTile();
    void setTile(std::shared_ptr<Tile> newTile);
    void addTileController(AbstractTileController * tileController);

private:
    std::shared_ptr<Tile> tile;
    std::vector<AbstractTileController *> tileControllers;
};


#endif // TILECONTROLLER_H
