#include    "track.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack::TrajectoryTrack()
    : railway_coord(0.0)
    , begin_point(osg::Vec3())
    , end_point(osg::Vec3())
    , length(0.0)
    , attitude(osg::Vec3())
    , basis(basis_t())

{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack::TrajectoryTrack(const osg::Vec3 &begin_point,
                                 const osg::Vec3 &end_point,
                                 const float railway_coord)
{
    this->railway_coord = railway_coord;
    this->begin_point = begin_point;
    this->end_point = end_point;

    osg::Vec3 len = end_point - begin_point;
    length = len.length();

    basis.front = len * (1 / length);
    osg::Vec3 travers = basis.front ^ basis.up;
    basis.right = travers * (1 / travers.length());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack::~TrajectoryTrack()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 TrajectoryTrack::getPosition(float railway_coord) const
{
    float delta_x = railway_coord - this->railway_coord;

    if (delta_x < 0)
        return osg::Vec3();

    osg::Vec3 pos = begin_point + basis.front * delta_x;

    return pos;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 TrajectoryTrack::getAttitude() const
{
    return  attitude;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
basis_t TrajectoryTrack::getBasis() const
{
    return basis;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float TrajectoryTrack::getRailwayCoord() const
{
    return railway_coord;
}
