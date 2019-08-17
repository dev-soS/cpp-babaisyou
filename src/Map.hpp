#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include "Block.hpp"

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

    Map(Map&&) = delete;
    Map(const Map&) = delete;

    Map& operator=(Map&&) noexcept = delete;
    Map& operator=(const Map&) = delete;

    Block** operator[](size_t idx)
    {
        return map[idx];
    }

    const Block** operator[](size_t idx) const
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
		int count = 0;
		int tmp_x, tmp_y;
		for (int y = 0; y < height; ++y )
		{
			for (int x = 0; x < width; ++x )
			{
				if ( map[y][x] != nullptr )
				{
					tmp_x = x;
					tmp_y = y;
					count = updateInternalHorizonal(0, x, y);
					if ( count >= 3 )
					{
						update_blocks(map, std::make_tuple(tmp_x, tmp_y), MoveType::LEFT, count);
					}
				}
			}
		}

		for ( int x = 0; x < width; ++x )
		{
			for ( int y = 0; y < height; ++y )
			{
				if ( map[y][x] != nullptr )
				{
					tmp_x = x;
					tmp_y = y;
					count = updateInternalVertical(0, x, y);
					if ( count >= 3 )
					{
						update_blocks(map, std::make_tuple(tmp_x, tmp_y), MoveType::DOWN, count);
					}
				}
			}
		}
	}

private:
    Block* map[Height][Width];

	int updateInternalHorizonal(int count, int& x, int y)
	{
		if ( x < width || map[y][x]->getBlockType() == BlockType::TEXT)
		{
			count = updateInternalHorizonal(++count, ++x, y);
		}
		return count;
	}

	int updateInternalVertical(int count, int x, int& y)
	{
		if ( y < width || map[y][x]->getBlockType() == BlockType::TEXT )
		{
			count = updateInternalVertical(++count, x, ++y);
		}
		return count;
	}
};

#endif