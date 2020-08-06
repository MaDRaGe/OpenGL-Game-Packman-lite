#include "Portal.h"

Portal::Portal()
{
	leave = true;
	inPortal = false;
}
void Portal::add(ivec2 point)
{
    points.push_back(point);
}
ivec2 Portal::move(ivec2 point)
{
		vector<ivec2>::iterator IT;
		for (IT = points.begin(); IT != points.end(); IT++)
		{
			if (IT->x == point.x
				&& IT->y == point.y
				)
			{
				if (IT == points.end() - 1)
				{
					IT = points.begin();
				}
				else
				{
					IT += 1;
				}
                leave = false;
                return *IT;
			}
		}
		
}

void Portal::simulate(ivec2 heroPos)
{
	inPortal = playerInPortal(heroPos);
}

bool Portal::isInPortal()
{
	return inPortal;
}
bool Portal::isLeave()
{
    return leave;
}

bool Portal::playerInPortal(ivec2 heroPos)
{
    for (auto point : points)
    {
        if (heroPos == point)
        {
			return true;
        }
    }
    leave = true;
    return false;
}


