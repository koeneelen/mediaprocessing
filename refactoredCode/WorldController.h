#ifndef WORLDCONTROLLER_H
#define WORLDCONTROLLER_H

#include "pathfinding.h"
#include "qgraphicsscene.h"
#include "GameData.h"
#include <QKeyEvent>
#include <QObject>
#include "tilecontroller.h"

class WorldController :  public QGraphicsScene
{
Q_OBJECT
public:
WorldController(GameData& gameData);

    void startGame();
    void updateGame();
    void toggleAutoPlay();
    void moveProtagonistUp();
    void moveProtagonistDown();
    void moveProtagonistLeft();
    void moveProtagonistRight();

signals:
    void protagonistPositionChanged();
private:
    GameData& gameData;
    bool isValidPosition(int x, int y);
    Pathfinding pathfinder;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override ;

    std::vector<TileController> tileControllers;
};

#endif // WORLDCONTROLLER_H
