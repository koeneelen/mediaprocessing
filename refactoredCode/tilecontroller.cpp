#include "tilecontroller.h"
#include <memory>

TileController::TileController(GameData *gameData): AbstractTileController(gameData)
{

}

void TileController::performAction()
{
    // CONSUME ENERGY
    float currEnergy = gameData->protagonist->getEnergy();
    float tileValue = tile->getValue();
    float newEnergy = currEnergy - tileValue;

    if (newEnergy < 0)
    {
        // endgame?
    }

    gameData->protagonist->setEnergy(newEnergy);
    //emit energychanged?
    qDebug() << "Consuming energy, new prot. energy: " << gameData->protagonist->getEnergy();


    for (auto tileController : tileControllers)
        tileController->performAction();
}

std::shared_ptr<Tile> TileController::getTile()
{
    return tile;
}

void TileController::setTile(std::shared_ptr<Tile> newTile)
{
    this->tile = newTile;
}

void TileController::addTileController(AbstractTileController * tileController)
{
    tileControllers.push_back(tileController);
}
