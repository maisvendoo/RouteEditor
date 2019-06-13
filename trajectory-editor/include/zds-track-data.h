#ifndef     ZDS_TRACK_DATA_H
#define     ZDS_TRACK_DATA_H

#include    <osg/Vec3>
#include    <string>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct zds_track_data_t
{
    int         ordinate;
    int         voltage;
    std::string arrows;
    osg::Vec3   begin_point;
    osg::Vec3   end_point;
    int         prev_uid;
    int         next_uid;

    zds_track_data_t()
        : ordinate(0)
        , voltage(0)
        , arrows("")
        , begin_point(osg::Vec3())
        , end_point(osg::Vec3())
        , prev_uid(-1)
        , next_uid(-2)
    {

    }
};

#endif // ZDSTRACKDATA_H
