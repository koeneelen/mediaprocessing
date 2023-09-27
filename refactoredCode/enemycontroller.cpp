#include "enemycontroller.h"
#include <QMessageBox>
EnemyController::EnemyController(GameData * gameData): AbstractTileController(gameData)
{

}

void EnemyController::performAction()
{
    // attack enemy, change health, set enemy defeated or endgame
    float enemyStrength = enemy->getValue();
    float protHealth = gameData->protagonist->getHealth();
    float newHealth = protHealth - enemyStrength;

    if (newHealth < 0)
    {
        QMessageBox gameOverBox;
        gameOverBox.setWindowTitle("Game Over");
        gameOverBox.setText("Game Over!");
        gameOverBox.setStandardButtons(QMessageBox::Ok);

        int result = gameOverBox.exec();

        if (result == QMessageBox::Ok)
        {
            //restart game
        }

    }

    if (!enemy->getDefeated())
    {
        //reset energy
        gameData->protagonist->setEnergy(100);

        //set newHealth
        gameData->protagonist->setHealth(newHealth);

        //set enemy defeated
        enemy->setDefeated(true);
        qDebug() << "Attacking enemy, new health: " << newHealth;
    }
    else
    {
        qDebug() << "Passing dead enemy";
    }
}

std::shared_ptr<Enemy> EnemyController::getEnemy()
{
    return enemy;
}

void EnemyController::setEnemy(std::shared_ptr<Enemy> newEnemy)
{
    this->enemy = newEnemy;
}


