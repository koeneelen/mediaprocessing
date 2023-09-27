#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "world.h"
#include <QPixmap>
#include <QDebug>
#define TILE_SIZE 16

struct GameData
{

    std::unique_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthPacks;
    int imageHeight;
    int imageWidth;
    int tileSize;
    std::vector<std::vector<int>> pixelWeights;
    std::vector<std::vector<bool>> passable;
    GameData(QString path)
    {
        world.createWorld(path, 5, 5, 0.25f);
        protagonist = world.getProtagonist();

        for(auto &tile : world.getTiles())
        {
            std::shared_ptr<Tile> dummy = std::move(tile);
            tiles.push_back(dummy);
        }

        for(auto &enemy : world.getEnemies())
        {
            std::shared_ptr<Enemy> dummy = std::move(enemy);
            enemies.push_back(dummy);
        }

        for(auto &healthPack : world.getHealthPacks())
        {
            std::shared_ptr<Tile> dummy = std::move(healthPack);
            healthPacks.push_back(dummy);
        }



        imageHeight = world.getRows();
        imageWidth = world.getCols();
        tileSize = TILE_SIZE;


        // Load the image based on the path
        QPixmap image(path);

        if (image.isNull()) {
            qDebug() << "Failed to load image.";
            return;
        }

        // Calculate pixelWeights and passable based on the loaded image
        pixelWeights.resize(image.height(), std::vector<int>(image.width(), 0));
        passable.resize(image.height(), std::vector<bool>(image.width(), true));

        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QPoint point(x, y);
                QColor pixelColor = image.toImage().pixelColor(point);

                // Calculate the weight based on the pixel's grayscale value
                int weight = 255 - pixelColor.red(); // Inverse the grayscale value
                // For impassable (black) pixels, set a maximum weight
                if (pixelColor == Qt::black) {
                    weight = std::numeric_limits<int>::max();
                    passable[y][x] = false;
                }

                pixelWeights[y][x] = weight;
            }
        }
    }
    void setHeuristic(int hr){
        heuristic = hr;
    }
    int getHeuristic(){
        return heuristic;
    }
private:
    World world;
    int heuristic;
};

#endif // GAMEDATA_H
