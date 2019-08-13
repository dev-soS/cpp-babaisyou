#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

class Block;

template <size_t Width, size_t Height>
class Map
{
public:
    Map() {
        for (size_t i = 0; i < Height; ++i) {
            for (size_t j = 0; j < Width; ++j) {
                map[i][j] = nullptr;
            }
        }
    }

    ~Map() = default;

    Map(const Map& other) {
        for(size_t i = 0; i < Height; ++i){
            for(size_t j = 0; j < Width; ++j){
                map[i][j] = other[i][j];
            }
        }
    }

    Map(Map&& other) {
        for(size_t i = 0; i < Height; ++i){
            for(size_t j = 0; j < Width; ++j){
                map[i][j] = other[i][j];
                other[i][j] = nullptr;
            }
        }


    }

    Map& operator=(const Map& other) {
        map = other.map
        return *this;
    }

    Map& operator=(Map&& other) {
        map = other.map
        return *this;
    }

    std::unique_ptr<Block>* operator[](size_t idx) {
        return map[idx];
    }

    const std::unique_ptr<Block>* operator[](size_t idx) const {
        return map[idx];
    }

    size_t getWidth() const {
        return Width;
    }

    size_t getHeight() const {
        return Height;
    }

private:
    std::unique_ptr<Block> map[Height][Width];
};

#endif