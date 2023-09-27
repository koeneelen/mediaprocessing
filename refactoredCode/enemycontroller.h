#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include "abstracttilecontroller.h"

class EnemyController: public AbstractTileController
{

public:
    EnemyController(GameData * gameData);
    void performAction();

    std::shared_ptr<Enemy> getEnemy();
    void setEnemy(std::shared_ptr<Enemy> newEnemy);




private:
    std::shared_ptr<Enemy> enemy;
};

#endif // ENEMYCONTROLLER_H
