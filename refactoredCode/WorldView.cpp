#include "WorldView.h"
#include <QPixmap>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QDebug>
#include <iostream>
#include <QWheelEvent>
#include <QVBoxLayout>  // Include QVBoxLayout for layout management
#include <QSlider>

#define TILE_WIDTH 16
#define TILE_HEIGHT 16


WorldView::WorldView(GameData& gameData,QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent), gameData(gameData)
{

    // Create a layout to hold the tile map
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Create a widget to hold the tile map
    QWidget* tileMapWidget = new QWidget(this);
    mainLayout->addWidget(tileMapWidget);

    // Set the tile map widget as the viewport widget
    setViewport(tileMapWidget);

    // Create and set up your tile map using the renderWorld function
    renderWorld(gameData);

    // Create a slider and add it to the main layout
    QSlider* heuristicSlider = new QSlider(Qt::Horizontal);
    heuristicSlider->setRange(1, 10);  // Set the range as per your requirement
    connect(heuristicSlider, &QSlider::valueChanged, this, &WorldView::onHeuristicValueChanged);
    mainLayout->addWidget(heuristicSlider);

    // Set the main layout as the layout for the WorldView
    setLayout(mainLayout);

    // Add the slider to the WorldView widget directly
    heuristicSlider->setParent(this);

    //renderWorld(gameData);
    renderProtagonist(*gameData.protagonist);
    renderEnemies(gameData.enemies);
    renderHealthPacks(gameData.healthPacks);
}

void WorldView::renderWorld(GameData& gameData)
{
    scene()->clear();

    int numRows = gameData.imageHeight;
    int numCols = gameData.imageWidth;
    int tileWidth = TILE_WIDTH;
    int tileHeight = TILE_HEIGHT;

    const std::vector<std::shared_ptr<Tile>>& tiles = gameData.tiles;
    for (const auto& tilePtr : tiles) {
        const Tile& tile = *tilePtr;

        int x = tile.getXPos() * tileWidth;
        int y = tile.getYPos() * tileHeight;
        QRectF tileRect(x, y, tileWidth, tileHeight);

        QGraphicsRectItem* tileItem = new QGraphicsRectItem(tileRect);

        double greenValue = tile.getValue();
        QColor tileColor = QColor::fromRgbF(0.0, greenValue, 0.0);
        tileItem->setBrush(QBrush(tileColor));

        scene()->addItem(tileItem);
    }

    scene()->setSceneRect(0, 0, numCols * tileWidth, numRows * tileHeight);


}

void WorldView::renderProtagonist(Protagonist& protagonist)
{
    const QString& imagePath = ":/images/minion.png";
    QPixmap protagonistImage(imagePath);

    if (protagonistImage.isNull()) {
        qDebug() << "Error loading protagonist image";
        return;
    }

    int protagonistX = protagonist.getXPos() * TILE_WIDTH;
    int protagonistY = protagonist.getYPos() * TILE_HEIGHT;
    QRectF protagonistRect(protagonistX, protagonistY, TILE_WIDTH, TILE_HEIGHT);

    protagonistItem = new QGraphicsPixmapItem(protagonistImage);
    protagonistItem->setPos(protagonistRect.topLeft());

    protagonistItem->setZValue(1.0);

    scene()->addItem(protagonistItem);
}



void WorldView::wheelEvent(QWheelEvent* event)
{
    QPoint angleDelta = event->angleDelta();

    if (!angleDelta.isNull()) {
        int delta = angleDelta.y();

        double scaleFactor = 1.25;
        if (delta > 0) {
            scale(scaleFactor, scaleFactor);
        } else if (delta < 0) {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
}
void WorldView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

    QGraphicsView::mousePressEvent(event);
}

void WorldView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        setDragMode(QGraphicsView::NoDrag);
    }
    QGraphicsView::mouseReleaseEvent(event);
}
void WorldView::updateProtagonistPosition()
{
    scene()->removeItem(protagonistItem);
    renderProtagonist(*gameData.protagonist);
}

void WorldView::renderEnemies(const std::vector<std::shared_ptr<Enemy>>& enemies) {
    for (const auto& enemyPtr : enemies) {
        const Enemy& enemy = *enemyPtr;

        int x = enemy.getXPos() * TILE_WIDTH;
        int y = enemy.getYPos() * TILE_HEIGHT;

        QRectF enemyRect(x, y, TILE_WIDTH, TILE_HEIGHT);

        QGraphicsRectItem* enemyItem = new QGraphicsRectItem(enemyRect);

        QColor enemyColor = QColor::fromRgbF(1.0, 0.0, 0.0);
        enemyItem->setBrush(QBrush(enemyColor));
        enemyItem->setZValue(1.0);
        scene()->addItem(enemyItem);
    }
}

void WorldView::renderHealthPacks(const std::vector<std::shared_ptr<Tile>>& healthPacks) {
    for (const auto& healthPackPtr : healthPacks) {
        const Tile& healthPack = *healthPackPtr;
        int x = healthPack.getXPos() * TILE_WIDTH;
        int y = healthPack.getYPos() * TILE_HEIGHT;

        QRectF healthPackRect(x, y, TILE_WIDTH, TILE_HEIGHT);

        QGraphicsRectItem* healthPackItem = new QGraphicsRectItem(healthPackRect);

        QColor healthPackColor = QColor::fromRgbF(0.0, 0.0, 1.0);
        healthPackItem->setBrush(QBrush(healthPackColor));
        healthPackItem->setZValue(1.0);
        scene()->addItem(healthPackItem);
    }
}
void WorldView::onHeuristicValueChanged(int value) {
    double heuristicWeight = static_cast<double>(value);  // Convert slider value to double or adjust as needed
    gameData.setHeuristic(heuristicWeight);
}
