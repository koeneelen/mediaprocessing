#include "healthpackcontroller.h"


HealthPackController::HealthPackController(GameData *gameData): AbstractTileController(gameData)
{

}

void HealthPackController::performAction()
{
    // update protagonist health & set consumed

    float currentHealth = gameData->protagonist->getHealth();
    float newHealth = currentHealth + tile->getValue();

    if (currentHealth == 100)
    {
        qDebug() << "Health already full";
        return;
    }

    if (!consumed)
    {
        if (newHealth > 100)
            newHealth = 100;

        if (newHealth < 0)
        {
            //endgame
        }

        gameData->protagonist->setHealth(newHealth);

        consumed = true;
        qDebug() << "Consuming healthpack: new health = " << newHealth;
    }
    else
    {
        qDebug() << "Passing consumed healthpack";
    }
}

std::shared_ptr<Tile> HealthPackController::getTile()
{
    return tile;
}

void HealthPackController::setTile(std::shared_ptr<Tile> newTile)
{
    this->tile = newTile;
}
