#include "WorldController.h"
#include <QKeyEvent>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include "pathfinding.h"
#include <QTimer>
#include "tilecontroller.h"
#include "enemycontroller.h"
#include "healthpackcontroller.h"
#include <memory>

WorldController::WorldController(GameData& gameData)
    : gameData(gameData)
    ,pathfinder(gameData.pixelWeights, gameData.passable, gameData.imageWidth,gameData.imageHeight)
{
    for (auto tile : gameData.tiles)
    {
        auto tileController = TileController(&gameData);
        tileController.setTile(tile);
        tileControllers.push_back(tileController);
    }

    for (auto enemy : gameData.enemies)
    {
        auto enemyController = new EnemyController(&gameData);
        enemyController->setEnemy(enemy);
        tileControllers.at( enemy->getXPos() + enemy->getYPos()*gameData.imageWidth ).addTileController(enemyController);
    }

    for (auto healthPack : gameData.healthPacks)
    {
        auto healthPackController = new HealthPackController(&gameData);
        healthPackController->setTile(healthPack);
        tileControllers.at( healthPack->getXPos() + healthPack->getYPos()*gameData.imageWidth ).addTileController(healthPackController);
    }
}

void WorldController::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    QString keyName = event->text();

    // Handle different key presses
    switch (key) {
    case Qt::Key_Up:    // Up arrow key
        moveProtagonistUp();
        break;
    case Qt::Key_Down:  // Down arrow key
        moveProtagonistDown();
        break;
    case Qt::Key_Left:  // Left arrow key
        moveProtagonistLeft();
        break;
    case Qt::Key_Right: // Right arrow key
        moveProtagonistRight();
        break;
    default:
        qDebug() << "Unhandled Key Pressed: " << key << " (" << keyName << ")";
        break;
    }
}

void WorldController::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // Get the mouse click coordinates in pixels
    int mouseX = event->scenePos().x();
    int mouseY = event->scenePos().y();

    // Calculate the tile size (assuming square tiles)
    int tileSize = gameData.tileSize;

    // Calculate the corresponding tile coordinates in the game world
    int tileX = mouseX / tileSize;
    int tileY = mouseY / tileSize;

    // Check if the tile coordinates are within the valid range
    if (isValidPosition(tileX, tileY)) {

        // Create a QPoint for the selected goal point
        QPoint goalPoint(tileX, tileY);

        // Create a QPoint for the protagonist's current position
        QPoint protagonistPosition(gameData.protagonist->getXPos(), gameData.protagonist->getYPos());

        // Calculate the path using A* pathfinding
        pathfinder.setHeuristicWeight(gameData.getHeuristic());
        std::vector<QPoint> path = pathfinder.findPath(protagonistPosition, goalPoint);
        // Update the protagonist's position along the calculated path
        int delayMs = 10; // Set your desired delay time in milliseconds


        for (const QPoint& step : path) {

            QTimer::singleShot(delayMs, [this, step]() {
                gameData.protagonist->setXPos(step.x());
                gameData.protagonist->setYPos(step.y());
                tileControllers.at( step.x() + step.y()*gameData.imageWidth ).performAction();
                emit protagonistPositionChanged();
            });

            delayMs += 10;
        }
    }
}


void WorldController::moveProtagonistUp()
{
    int currentX = gameData.protagonist->getXPos();
    int currentY = gameData.protagonist->getYPos();

    int newX = currentX;
    int newY = currentY - 1; // Move up
    if (isValidPosition(newX, newY)) {
        gameData.protagonist->setXPos(newX);
        gameData.protagonist->setYPos(newY);
        tileControllers.at( newX + newY*gameData.imageWidth ).performAction();
        emit protagonistPositionChanged();
    }
}

void WorldController::moveProtagonistDown()
{
    int currentX = gameData.protagonist->getXPos();
    int currentY = gameData.protagonist->getYPos();

    int newX = currentX;
    int newY = currentY + 1; // Move down
    if (isValidPosition(newX, newY)) {
        gameData.protagonist->setXPos(newX);
        gameData.protagonist->setYPos(newY);
        tileControllers.at( newX + newY*gameData.imageWidth ).performAction();
        emit protagonistPositionChanged();
    }
}

void WorldController::moveProtagonistLeft()
{
    int currentX = gameData.protagonist->getXPos();
    int currentY = gameData.protagonist->getYPos();

    int newX = currentX - 1; // Move left
    int newY = currentY;
    if (isValidPosition(newX, newY)) {
        gameData.protagonist->setXPos(newX);
        gameData.protagonist->setYPos(newY);
        tileControllers.at( newX + newY*gameData.imageWidth ).performAction();
        emit protagonistPositionChanged();
    }
}

void WorldController::moveProtagonistRight()
{
    int currentX = gameData.protagonist->getXPos();
    int currentY = gameData.protagonist->getYPos();

    int newX = currentX + 1; // Move right
    int newY = currentY;
    if (isValidPosition(newX, newY)) {
        gameData.protagonist->setXPos(newX);
        gameData.protagonist->setYPos(newY);
        tileControllers.at( newX + newY*gameData.imageWidth ).performAction();
        emit protagonistPositionChanged();
    }

}

bool WorldController::isValidPosition(int x, int y)
{
    if( 0<= y && y< gameData.imageHeight && 0<= x && x < gameData.imageWidth)
    {
        return true;
    }
    return false;
}
