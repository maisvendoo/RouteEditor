#ifndef     TRAJECTORY_H
#define     TRAJECTORY_H

#include    <QString>

#include    <vector>
#include    <fstream>

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

    bool load(const QString &path);

    bool save(const QString &path) const;

    osg::Vec3 getPosition(float railway_coord);

    osg::Vec3 getPosition(float railway_coord, osg::Vec3 &attitude);

    osg::Vec3 getPosition(float railway_coord, osg::Vec3 &attitude, basis_t &basis);

private:

    QString     name;

    std::vector<TrajectoryTrack *>  tracks;
    std::vector<osg::Vec3 *>        nodes;

    bool load(const std::string &path);

    bool load(std::ifstream &stream);

    std::string getLine(std::istream &stream) const;

    bool save(const std::string &path) const;

    bool save(std::ofstream &stream) const;

    TrajectoryTrack *findTrack(float railway_coord);

    TrajectoryTrack *findTrack(float railway_coord, TrajectoryTrack *next_track);
};

#endif // TRAJECTORY_H
