#include    "trajectory.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Trajectory::Trajectory()
    : name("")
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Trajectory::Trajectory(const std::vector<TrajectoryTrack *> &tracks)
{
    this->tracks = tracks;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Trajectory::~Trajectory()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::load(const QString &path) const
{
    return load(path.toStdString());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::save(const QString &path) const
{
    return save(path.toStdString());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 Trajectory::getPosition(float railway_coord)
{
    osg::Vec3 attitude;

    return getPosition(railway_coord, attitude);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 Trajectory::getPosition(float railway_coord, osg::Vec3 &attitude)
{
    basis_t basis;

    return getPosition(railway_coord, attitude, basis);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Vec3 Trajectory::getPosition(float railway_coord,
                                  osg::Vec3 &attitude,
                                  basis_t &basis)
{
    TrajectoryTrack *track = findTrack(railway_coord);

    if (track == nullptr)
        return osg::Vec3();

    attitude = track->getAttitude();
    basis = track->getBasis();

    return track->getPosition(railway_coord);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::load(const std::string &path) const
{
    if (path.empty())
        return false;

    std::ifstream stream(path.c_str(), std::ios::in);

    if (!stream)
        return false;

    return load(stream);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::load(std::ifstream &stream) const
{
    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::save(const std::string &path) const
{
    if (path.empty())
        return false;

    std::ofstream stream(path.c_str(), std::ios::out);

    if (!stream)
        return false;

    return save(stream);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::save(std::ofstream &stream) const
{
    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack *Trajectory::findTrack(float railway_coord)
{
    TrajectoryTrack *next_track = nullptr;

    return findTrack(railway_coord, next_track);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack *Trajectory::findTrack(float railway_coord,
                                       TrajectoryTrack *next_track)
{
    if (tracks.size() == 0)
        return nullptr;

    TrajectoryTrack *track = nullptr;

    size_t left_idx = 0;
    size_t right_idx = tracks.size() - 1;
    size_t idx = (left_idx + right_idx) / 2;

    while (idx != left_idx)
    {
        track = tracks.at(idx);

        if (railway_coord <= track->getRailwayCoord())
            right_idx = idx;
        else
            left_idx = idx;

        idx = (left_idx + right_idx) / 2;
    }

    if (idx < right_idx)
    {
        next_track = tracks.at(idx + 1);
    }
    else
    {
        next_track = tracks.at(idx + 1);
    }

    return tracks.at(idx);
}
