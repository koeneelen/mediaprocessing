#ifndef WORLDVIEW_H
#define WORLDVIEW_H
#include "GameData.h"
#include "qobject.h"
#include "qtmetamacros.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "world/world.h"
#include "qslider.h"
class WorldView : public QGraphicsView
{
    Q_OBJECT
public:
    WorldView(GameData& gameData,QGraphicsScene* scene, QWidget* parent);
    void renderWorld(GameData& gameData);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resetGameView();

    void renderProtagonist(Protagonist& protagonist);
    void clearProtagonist();
    void renderEnemies(const std::vector<std::shared_ptr<Enemy>>& enemies);
    void renderHealthPacks(const std::vector<std::shared_ptr<Tile>>& healthPacks);

    void renderPath(const std::vector<Tile>& path);
public slots:
    void updateProtagonistPosition();
    void onHeuristicValueChanged(int value);

private:
    QGraphicsPixmapItem * protagonistItem;
    GameData& gameData;
    int topLeftX;
    int topLeftY;
    QSlider* heuristicSlider;
};

#endif // WORLDVIEW_H
