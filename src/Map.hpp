#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include "Block.hpp"

class Block {};

template <size_t Width, size_t Height>
class Map
{
public:
    Map()
    {
        for (size_t i = 0; i < Height; ++i)
        {
            for (size_t j = 0; j < Width; ++j)
            {
                map[i][j] = nullptr;
            }
        }
    }

    ~Map() = default;

    Map(Map&& other)
    {
        for(size_t i = 0; i < Height; ++i)
        {
            for(size_t j = 0; j < Width; ++j)
            {
                map[i][j] = std::move(other[i][j]);
            }
        }
    }

    Map& operator=(Map&& other)
    {
        for(size_t i = 0; i < Height; ++i)
        {
            for(size_t j = 0; j < Width; ++j)
            {
                map[i][j] = std::move(other[i][j]);
            }
        }
        return *this;
    }

    std::unique_ptr<Block>* operator[](size_t idx)
    {
        return map[idx];
    }

    const std::unique_ptr<Block>* operator[](size_t idx) const
    {
        return map[idx];
    }

    size_t getWidth() const
    {
        return Width;
    }

    size_t getHeight() const 
    {
        return Height;
    }

	void update()
	{
		std::vector<Block>
		for (int y = 0; y < height; ++y )
		{
			for (int x = 0; x < width; ++x )
			{
				if ( map[y][x] != nullptr )
				{
					updateInternalHorizonal(0, MoveType::NONE, make_tuple(x, y));
					updateInternalVertical(0, MoveType::NONE, make_tuple(x, y));
				}
			}
		}
	}

private:
    std::unique_ptr<Block> map[Height][Width];

	int updateInternalHorizonal(int count, MoveType direction, std::tuple<int, int> pos)
	{
		int x, y;
		std::tie(x, y) = pos;
		if ( count == 0 )
		{
			count = updateInternalHorizonal(++count, MoveType::LEFT, std::make_tuple(x - 1, y)) + updateInternalHorizonal(++count, MoveType::RIGHT, std::make_tuple(x + 1, y));
		}
		else if ( x < 0 || x > width || y < 0 || y > height );
		else if ( map[y][x] == nullptr );
		else
		{
			if ( direction == MoveType::LEFT )
			{
				count = updateInternalHorizonal(++count, MoveType::LEFT, make_tuple(x - 1, y));
			}
			else if ( direction == MoveType::RIGHT )
			{
				count = updateInternalHorizonal(++count, MoveType::RIGHT, make_tuple(x + 1, y));
			}
		}
		return count;
	}

	int updateInternalVertical(int count, MoveType direction, std::tuple<int, int> pos)
	{
		int x, y;
		std::tie(x, y) = pos;
		if ( count == 0 )
		{
			count = updateInternalVertical(++count, MoveType::UP, std::make_tuple(x, y - 1)) + updateInternalVertical(++count, MoveType::DOWN, std::make_tuple(x, y + 1));
		}
		else if ( x < 0 || x > width || y < 0 || y > height );
		else if ( map[y][x] == nullptr );
		else
		{
			if ( direction == MoveType::UP )
			{
				count = updateInternalVertical(++count, MoveType::UP, make_tuple(x, y - 1));
			}
			else if ( direction == MoveType::DOWN )
			{
				count = updateInternalVertical(++count, MoveType::DOWN, make_tuple(x, y + 1));
			}
		}
		return count;
	}
};

#endif