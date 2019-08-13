#ifndef MAP_HPP
#define MAP_HPP

#include "Block.hpp"

#include <memory>

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

    Map(Map&& other) {
        for(size_t i = 0; i < Height; ++i){
            for(size_t j = 0; j < Width; ++j){
                map[i][j] = std::move(other[i][j]);
            }
        }
    }

    Map& operator=(Map&& other) {
        for(size_t i = 0; i < Height; ++i){
            for(size_t j = 0; j < Width; ++j){
                map[i][j] = std::move(other[i][j]);
            }
        }
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