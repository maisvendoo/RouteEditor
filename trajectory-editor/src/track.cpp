#include    "track.h"

#include    <sstream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack::TrajectoryTrack()
    : railway_coord(0.0)
    , uid(0)
    , ordinate(0)
    , voltage(0)
    , arrows("")
    , begin_point(osg::Vec3())
    , end_point(osg::Vec3())
    , prev_uid(-1)
    , next_uid(-2)
    , length(0.0)
    , attitude(osg::Vec3())
    , basis(basis_t())

{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float arg(float cos_x, float sin_x)
{
    float angle = 0;

    if (sin_x >= 0.0f)
        angle = acosf(cos_x);
    else
        angle = -acosf(cos_x);

    return angle;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TrajectoryTrack::TrajectoryTrack(const zds_track_data_t &zds_track_data,
                                 const float railway_coord)
{
    this->railway_coord = railway_coord;
    this->begin_point = zds_track_data.begin_point;
    this->end_point = zds_track_data.end_point;
    this->ordinate = zds_track_data.ordinate;
    this->voltage = zds_track_data.voltage;
    this->arrows = zds_track_data.arrows;
    this->prev_uid = zds_track_data.prev_uid;
    this->next_uid = zds_track_data.next_uid;

    osg::Vec3 len = end_point - begin_point;
    length = len.length();

    basis.front = len * (1 / length);
    osg::Vec3 travers = basis.front ^ basis.up;
    basis.right = travers * (1 / travers.length());

    float yaw = arg(basis.front.y(), basis.front.x());
    float pitch = asinf(basis.front.z());

    attitude = osg::Vec3(pitch, 0.0, yaw);
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
float TrajectoryTrack::getLength() const
{
    return length;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string TrajectoryTrack::serialize() const
{
    std::string line;

    std::ostringstream ss(line);

    ss << begin_point.x() << " "
       << begin_point.y() << " "
       << begin_point.z() << " "
       << end_point.x() << " "
       << end_point.y() << " "
       << end_point.z() << " "
       << prev_uid << " "
       << next_uid << " "
       << arrows << " "
       << voltage << " "
       << ordinate;

    return line;
}

osg::Vec3 *TrajectoryTrack::getEndPointPtr()
{
    return &end_point;
}

osg::Vec3 *TrajectoryTrack::getBeginPointPtr()
{
    return &begin_point;
}
