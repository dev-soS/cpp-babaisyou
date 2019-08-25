#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Block.hpp"
#include "MapWrapper.hpp"

template <size_t Width, size_t Height>
class Map
{
public:

    Map() = default;
    ~Map() = default;

    Map(Map&&) = delete;
    Map(const Map&) = delete;

    Map& operator=(Map&&) noexcept = delete;
    Map& operator=(const Map&) = delete;

    std::vector<Block*>* operator[](size_t idx)
    {
        return map[idx];
    }

    const std::vector<Block*>* operator[](size_t idx) const
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

	bool update()
	{
		int count = 0;
		int tmp_x, tmp_y;
		bool change_property = false;
		for (int y = 0; y < Height; ++y )
		{
			for (int x = 0; x < Width; ++x )
			{
				if ( map[y][x].empty() )
				{
					tmp_x = x;
					tmp_y = y;
					count = updateInternalHorizonal(0, x, y);
					if ( count >= 3 )
					{
						if ( wrapper.updateBlocks(std::make_tuple(tmp_x, tmp_y), MoveType::LEFT, count) ) change_property = true;
					}
				}
			}
		}

		for ( int x = 0; x < Width; ++x )
		{
			for ( int y = 0; y < Height; ++y )
			{
				if ( map[y][x] != nullptr )
				{
					tmp_x = x;
					tmp_y = y;
					count = updateInternalVertical(0, x, y);
					if ( count >= 3 )
					{
						if ( wrapper.updateBlocks(std::make_tuple(tmp_x, tmp_y), MoveType::DOWN, count) ) change_property = true;
					}
				}
			}
		}

		return change_property;
	}

private:

	std::vector<Block*> map[Height][Width];
	MapWrapper<Width, Height> wrapper;

	int updateInternalHorizonal(int count, int& x, int y)
	{
		for ( Block* block : map[y][x] )
		{
			if ( x < Width && !map[y][x].empty() && block->getBlockType() == BlockType::TEXT )
			{
				count = updateInternalHorizonal(++count, ++x, y);
				break;
			}
		}
		return count;
	}

	int updateInternalVertical(int count, int x, int& y)
	{
		for ( Block* block : map[y][x] ){
			if ( y < Height && !map[y][x].empty() && map[y][x]->getBlockType() == BlockType::TEXT )
			{
				count = updateInternalVertical(++count, x, ++y);
				break;
			}
		}
		return count;
	}
};

#endif