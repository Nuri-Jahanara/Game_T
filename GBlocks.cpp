#pragma once
#include "GBlocks.hpp"
#include "infoBlock.hpp"
#include<SFML/Graphics/RenderTarget.hpp>
#include<iostream>
/*Block Shape 4X4
[0 1 2 3]
[4 5 6 7 ]
[8 9 10 11]
[12 13 14 15]
*/

unsigned int Block4X4[7][4] = {
    {4, 5, 8,  9},     // square
    {5, 9, 13, 12},    //Reverse-L
    {5, 9, 10, 14},    //Z
    {5, 9, 8,  12},    //Reverse-Z
    {5, 8, 9,  10},    //T
    {5, 9, 13, 14},    //L
    {1, 5, 9,  13},    //I

};
GBlocks::GBlocks(sf::Texture& texture, int id) :
    tPosition(sf::Vector2i{ 3,0 }), currentRotation(0), tID(id), tBlock(), tSprite(texture, sf::IntRect{ (id % 7) * 18, 0, 18, 18 }) {
    tID = tID % 7; //restriction for it not to get out of bounce
    for (auto i = 0; i < 4; ++i) {
        tBlock[i].x = Block4X4[tID][i] % 4;
        tBlock[i].y = Block4X4[tID][i] / 4;
    }
}
void::GBlocks::rotate() {
    //Store state of Block in case rotation turns out to be invalid
    previousBlock == tBlock;
    if (tID == 0) { //Square does not need to rotate
        return;
    }
    if (tID == 6) {  // fo 'I' restrict rotation to two states: horizontal and vertical
        currentRotation++;
        for (auto i = 0; i < 4; ++i) {
            sf::Vector2i previousBlockPoint = tBlock[i];    //pivot
            sf::Vector2i localVector = previousBlockPoint - sf::Vector2i{ 1,2 };  //1, 1
            sf::Vector2i nextBlockPoint{};
            if (currentRotation % 2 == 1) {
                /* Rotation:counter clockwise
              * [0   -1]
              * [-1  0] */
                nextBlockPoint = sf::Vector2i{ (0 * localVector.x) + (-1 * localVector.y),
                             (1 * localVector.x) + (0 * localVector.y) };
            }
            else {
                nextBlockPoint = sf::Vector2i{ (0 * localVector.x) + (1 * localVector.y),
                               (-1 * localVector.x) + (0 * localVector.y) };
            }
            tBlock[i] = sf::Vector2i{ 1,2 } + nextBlockPoint;
        }return;
    }
    for (auto i = 0; i < 4; ++i) {
        sf::Vector2i previousBlockPoint = tBlock[i];      //Pivot
        sf::Vector2i localVector = previousBlockPoint - sf::Vector2i{ 1,2 }; //1,1
        /* Rotation Matrix:
        * [cos degree    -sin degree]
        * [sin degree    cos degree]
        * translates to clockwise
        * [0   -1]
        * [1  0]
        * */
        sf::Vector2i nextBlockPoint{ (0 * localVector.x) + (-1 * localVector.y),
                                    (1 * localVector.x) + (0 * localVector.y) };

        tBlock[i] = sf::Vector2i{ 1,2 } + nextBlockPoint;
    }
}


void GBlocks::motion(Direction direction) {
    if (direction == Direction::Left) {
        tPosition.x--;
    }
    else if (direction == Direction::Right) {
        tPosition.x++;
    }
    else {
        tPosition.y++;
    }
}

void GBlocks::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < 4; ++i) {
        tSprite.setPosition((tBlock[i].x * 18) + (tPosition.x * 18), (tBlock[i].y * 18) + (tPosition.y * 18));
        target.draw(tSprite);
    }
}


std::array<sf::Vector2i, 4> GBlocks::getBlockPositions() const {
    std::array<sf::Vector2i, 4>blockPositions;
    for (auto i = 0; i < 4; ++i) {
        blockPositions[i] = sf::Vector2i{ tBlock[i].x + tPosition.x, tBlock[i].y + tPosition.y };
    }
    return blockPositions;
}

std::array<sf::Vector2i, 4>GBlocks::getNextBlockPositions(Direction direction) const {
    std::array<sf::Vector2i, 4>blockPositions;
    sf::Vector2i tempBlockPosition{ tPosition };
    if (direction == Direction::Left) {
        tempBlockPosition.x--;
    }
    else if (direction == Direction::Right) {
        tempBlockPosition.x++;
    }
    else {
        tempBlockPosition.y++;
    }
    for (auto i = 0; i < 4; ++i) {
        blockPositions[i] = sf::Vector2i{ tBlock[i].x + tempBlockPosition.x, tBlock[i].y + tempBlockPosition.y };
    }
    return blockPositions;
}
void GBlocks::revertState() {
    tBlock = previousBlock;
}

int GBlocks::getID() const {
    return tID;
}

void GBlocks::setPosition(const sf::Vector2i& position) {
    tPosition = position;
}