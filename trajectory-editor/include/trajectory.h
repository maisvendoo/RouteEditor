#ifndef     TRAJECTORY_H
#define     TRAJECTORY_H

#include    <QString>

#include    <vector>

#include    "track.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Trajectory
{
public:

    Trajectory();

    Trajectory(const std::vector<TrajectoryTrack *> &tracks);

    ~Trajectory();

    bool load(const QString &path) const;

    bool save(const QString &path) const;

    osg::Vec3 getPosition(float railway_coord);

    osg::Vec3 getPosition(float railway_coord, osg::Vec3 &attitude);

    osg::Vec3 getPosition(float railway_coord, osg::Vec3 &attitude, basis_t &basis);

private:

    QString     name;

    std::vector<TrajectoryTrack *>  tracks;

    bool load(const std::string &path) const;

    bool save(const std::string &path) const;

    TrajectoryTrack *findTrack(float railway_coord);

    TrajectoryTrack *findTrack(float railway_coord, TrajectoryTrack *next_track);
};

#endif // TRAJECTORY_H