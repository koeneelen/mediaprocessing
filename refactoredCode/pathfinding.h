#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "qdebug.h"
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <QPoint>
#include <algorithm>

class Pathfinding {
public:
    Pathfinding(const std::vector<std::vector<int>>& pixelWeights, const std::vector<std::vector<bool>>& passable, int imageWidth, int imageHeight)
        : pixelWeights(pixelWeights), passable(passable), imageWidth(imageWidth), imageHeight(imageHeight) {}

    std::vector<QPoint> findPath(const QPoint& start, const QPoint& goal) {
        std::vector<QPoint> path;
        std::vector<std::vector<int>> gValues(imageHeight, std::vector<int>(imageWidth, std::numeric_limits<int>::max()));
        std::vector<QPoint> parents(imageWidth * imageHeight, QPoint(-1, -1));

        // A* algorithm
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
        std::vector<bool> closedSet(imageWidth * imageHeight, false);

        int startX = start.x();
        int startY = start.y();
        int goalX = goal.x();
        int goalY = goal.y();

        openSet.push({ QPoint(startX, startY), 0 });

        // checkme
        gValues.resize(imageHeight, std::vector<int>(imageWidth, std::numeric_limits<int>::max()));
        gValues[startY][startX] = 0;

        while (!openSet.empty()) {
            Node currentNode = openSet.top();
            openSet.pop();

            int currentX = currentNode.point.x();
            int currentY = currentNode.point.y();

            if (currentX == goalX && currentY == goalY) {
                // Found the goal, reconstruct the path
                qDebug() << "found path";

                path = reconstructPath(parents, QPoint(goalX, goalY));
                break;
            }

            closedSet[currentY * imageWidth + currentX] = true;

            // Define possible adjacent moves
            const int dx[] = { -1, 0, 1, 0, -1, 1, -1, 1 };
            const int dy[] = { 0, -1, 0, 1, -1, -1, 1, 1 };

            for (int i = 0; i < 8; ++i) {
                int newX = currentX + dx[i];
                int newY = currentY + dy[i];


                if (newX >= 0 && newX <imageWidth && newY >= 0 && newY < imageHeight && passable[newY][newX] && !closedSet[newY * imageWidth + newX]) {


                    int tentativeG = gValues[currentY][currentX] + ((i % 2 == 0) ? 1 : 1.414) + pixelWeights[newY][newX];

                    if (tentativeG < gValues[newY][newX]) {

                        parents[newY * imageWidth + newX] = QPoint(currentX, currentY);
                        gValues[newY][newX] = tentativeG;

                        int hValue = octileDistance(newX, newY, goalX, goalY);
                        int fValue = tentativeG + heuristicWeight * hValue;
                        qDebug() << heuristicWeight;
                        openSet.push({ QPoint(newX, newY), fValue });
                    }
                }
            }
        }

        return path;
    }

    void setHeuristicWeight(double weight) {
        heuristicWeight = weight;
    }
    std::vector<QPoint> reconstructPath(const std::vector<QPoint>& parents, const QPoint& end) {
        std::vector<QPoint> path;
        QPoint current = end;
        while (current != QPoint(-1,-1)) {


            path.push_back(current);
            if (current == parents[current.y() * imageWidth + current.x()]) {

                break;
            }
            current = parents[current.y() * imageWidth + current.x()];

        }
        std::reverse(path.begin(), path.end());
        return path;
    }
    struct Node {
        QPoint point;
        int fValue;

        bool operator>(const Node& other) const {
            return fValue > other.fValue;
        }
    };
    int manhattanDistance(int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
    double octileDistance(int x1, int y1, int x2, int y2) {
        int dx = std::abs(x1 - x2);
        int dy = std::abs(y1 - y2);
        return std::sqrt(2) * std::min(dx, dy) + std::max(dx, dy) - std::min(dx, dy);
    }

private:
    std::vector<std::vector<int>> pixelWeights;
    std::vector<std::vector<bool>> passable;
    int imageWidth;
    int imageHeight;

    double heuristicWeight;






};

#endif // PATHFINDING_H
