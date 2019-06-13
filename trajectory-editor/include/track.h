#ifndef     TRACK_H
#define     TRACK_H

#include    <osg/Vec3>
#include    <string>

#include    "basis.h"
#include    "zds-track-data.h"

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

    std::string serialize() const;

private:

    float       railway_coord;

    int         ordinate;
    int         voltage;
    std::string arrows;
    osg::Vec3   begin_point;
    osg::Vec3   end_point;
    int         prev_uid;
    int         next_uid;

    float       length;

    osg::Vec3   attitude;
    basis_t     basis;
};

#endif // TRACK_H
