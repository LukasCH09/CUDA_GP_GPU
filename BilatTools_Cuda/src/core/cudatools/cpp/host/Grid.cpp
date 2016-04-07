#include "Grid.h"

#include "Device.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Grid::Grid(const dim3& dg, const dim3& db) :
	dg(dg), db(db)
    {
    Device::gridAssert(dg, db);
    }

int Grid::threadCounts() const
    {
    return Device::nbThread(dg, db);
    }

int Grid::blockCounts() const
    {
    return dg.x*dg.y*dg.z;
    }

int Grid::threadByBlock() const
    {
    return db.x*db.y*db.z;
    }

ostream& operator<<(ostream& stream, const Grid& grid)
    {
    stream <<"dg x db = ("<< grid.dg.x <<","<<grid.dg.y<<","<<grid.dg.z<<")x("<<grid.db.x<<","<<grid.db.y<<","<<grid.db.z<<")";
    return stream;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

