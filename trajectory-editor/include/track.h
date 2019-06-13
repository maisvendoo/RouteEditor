#ifndef     TRACK_H
#define     TRACK_H

#include    <osg/Vec3>

#include    "basis.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class TrajectoryTrack
{
public:

    TrajectoryTrack();

    TrajectoryTrack(const osg::Vec3 &begin_point,
                    const osg::Vec3 &end_point,
                    const float railway_coord = 0.0);

    ~TrajectoryTrack();

    osg::Vec3 getPosition(float railway_coord) const;

    osg::Vec3 getAttitude() const;

    basis_t getBasis() const;

    float getRailwayCoord() const;

private:

    float       railway_coord;

    osg::Vec3   begin_point;
    osg::Vec3   end_point;

    float       length;

    osg::Vec3   attitude;
    basis_t     basis;
};

#endif // TRACK_H
