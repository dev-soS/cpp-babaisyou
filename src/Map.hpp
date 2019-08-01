#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

class Block;

template <size_t Width, size_t Height>
class Map
{
public:
    Map() : width(Width), height(Height) {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                map[i][j] = nullptr;
            }
        }
    }

    ~Map();

    Map(const Map& other);
    Map(Map&& other);

    Map& operator=(const Map& other);
    Map& operator=(Map&& other);

    std::unique_ptr<Block>* operator[](size_t idx) {
        return map[idx];
    }

    const std::unique_ptr<Block>* operator[](size_t idx) const {
        
    }

    size_t getWidth() const {

    }

    size_t getHeight() const {

    }

private:
    size_t width;
    size_t height;

    std::unique_ptr<Block> map[Height][Width];
};

#endif