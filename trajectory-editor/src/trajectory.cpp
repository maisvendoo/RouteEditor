#include    "trajectory.h"
#include    "string-funcs.h"

#include    <sstream>

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
    nodes.clear();

    for (auto it = tracks.begin(); it != tracks.end(); ++it)
    {
        TrajectoryTrack *track = *it;
        delete track;
        track = Q_NULLPTR;
    }

    tracks.clear();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Trajectory::load(const QString &path)
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
bool Trajectory::load(const std::string &path)
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
bool Trajectory::load(std::ifstream &stream)
{
    zds_track_data_t zds_track;
    std::vector<zds_track_data_t> tmp_tracks;

    while (!stream.eof())
    {
        std::string line = getLine(stream);

        std::istringstream ss(line);

        ss >> zds_track.begin_point.x()
           >> zds_track.begin_point.y()
           >> zds_track.begin_point.z()
           >> zds_track.end_point.x()
           >> zds_track.end_point.y()
           >> zds_track.end_point.z()
           >> zds_track.prev_uid
           >> zds_track.next_uid
           >> zds_track.arrows
           >> zds_track.voltage
           >> zds_track.ordinate;        

        tmp_tracks.push_back(zds_track);
    }

    if (tmp_tracks.empty())
        return false;

    float railway_coord = 0.0f;
    auto it = tmp_tracks.begin();

    for (; (*it).next_uid != -2; ++it)
    {
        zds_track_data_t cur_track = *it;
        zds_track_data_t next_track = tmp_tracks.at(static_cast<size_t>(cur_track.next_uid - 1));
        cur_track.end_point = next_track.begin_point;

        TrajectoryTrack *track = new TrajectoryTrack(cur_track, railway_coord);
        railway_coord += track->getLength();

        tracks.push_back(track);
        nodes.push_back(track->getBeginPointPtr());
    }

    TrajectoryTrack *track = new TrajectoryTrack(*it, railway_coord);
    tracks.push_back(track);
    nodes.push_back(track->getBeginPointPtr());
    nodes.push_back(track->getEndPointPtr());

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string Trajectory::getLine(std::istream &stream) const
{
    std::string line = "";
    std::getline(stream, line);
    std::string tmp = delete_symbol(line, '\r');
    tmp = delete_symbol(tmp, ';');
    std::replace(tmp.begin(), tmp.end(), ',', ' ');

    return tmp;
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
    if (tracks.empty())
        return false;

    for (auto it = tracks.begin(); it != tracks.end(); ++it)
    {
        stream << (*it)->serialize() << std::endl;
    }

    return true;
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
