#include "ovr_system_wrapper.h"

namespace ovr_system_wrapper
{
SystemError handleTrackedPropertyErrors( vr::TrackedDeviceProperty tdp,
                                         vr::ETrackedPropertyError error,
                                         std::string customErrorMsg )
{
    if ( error != vr::TrackedProp_Success )
    {
        LOG( ERROR ) << "Could not get Property with error \""
                     << vr::VRSystem()->GetPropErrorNameFromEnum( error )
                     << "\" property: "
                     << "todo"
                     << " " << customErrorMsg;
        if ( tdp == vr::Prop_TrackedDeviceProperty_Max )
        {
            // Just for Error OPPS todo
        }
        return SystemError::UndefinedError;
    }
    return SystemError::NoError;
}

std::string getPropertyFromTrackedEnum( vr::TrackedDeviceProperty )
{
    return "TODO";
}

std::pair<SystemError, bool>
    getBoolTrackedProperty( int deviceIndex,
                            vr::TrackedDeviceProperty property,
                            std::string customErrorMsg )

{
    uint32_t unIndex = static_cast<uint32_t>( deviceIndex );
    vr::ETrackedPropertyError error;
    bool value;
    value = vr::VRSystem()->GetBoolTrackedDeviceProperty(
        unIndex, property, &error );
    SystemError e
        = handleTrackedPropertyErrors( property, error, customErrorMsg );
    std::pair<SystemError, bool> p( e, value );
    return p;
}

std::pair<SystemError, int>
    getInt32TrackedProperty( int deviceIndex,
                             vr::TrackedDeviceProperty property,
                             std::string customErrorMsg )

{
    uint32_t unIndex = static_cast<uint32_t>( deviceIndex );
    int value;
    vr::ETrackedPropertyError error;
    value = static_cast<int>( vr::VRSystem()->GetInt32TrackedDeviceProperty(
        unIndex, property, &error ) );
    SystemError e
        = handleTrackedPropertyErrors( property, error, customErrorMsg );
    std::pair<SystemError, int> p( e, value );
    return p;
}

std::pair<SystemError, float>
    getFloatTrackedProperty( int deviceIndex,
                             vr::TrackedDeviceProperty property,
                             std::string customErrorMsg )

{
    uint32_t unIndex = static_cast<uint32_t>( deviceIndex );
    vr::ETrackedPropertyError error;
    float value;
    value = vr::VRSystem()->GetFloatTrackedDeviceProperty(
        unIndex, property, &error );
    SystemError e
        = handleTrackedPropertyErrors( property, error, customErrorMsg );
    std::pair<SystemError, float> p( e, value );
    return p;
}

std::pair<SystemError, std::string>
    getStringTrackedProperty( int deviceIndex,
                              vr::TrackedDeviceProperty property,
                              std::string customErrorMsg )

{
    // This appears to be correct value as set in CVRSettingHelper as of
    // ovr 1.11.11
    const uint32_t bufferMax = 4096;
    char cStringOut[bufferMax];
    uint32_t unIndex = static_cast<uint32_t>( deviceIndex );
    vr::VRSystem()->GetStringTrackedDeviceProperty(
        unIndex, property, cStringOut, bufferMax );
    std::string value = cStringOut;
    SystemError e = handleTrackedPropertyErrors(
        property, vr::TrackedProp_Success, customErrorMsg );
    std::pair<SystemError, std::string> p( e, value );
    return p;
}

bool deviceConnected( int index )
{
    uint32_t unIndex = static_cast<uint32_t>( index );
    return vr::VRSystem()->IsTrackedDeviceConnected( unIndex );
}

vr::ETrackedDeviceClass getDeviceClass( int index )
{
    uint32_t unIndex = static_cast<uint32_t>( index );
    return vr::VRSystem()->GetTrackedDeviceClass( unIndex );
}

std::string getDeviceName( int index )
{
    uint32_t unIndex = static_cast<uint32_t>( index );
    // checks if connected returns unknown if not
    if ( !vr::VRSystem()->IsTrackedDeviceConnected( unIndex ) )
    {
        return "No Device Connected";
    }
    // arbitary max size OVR specifies 32*1024 but that's unrealistic
    auto controllerNamePair
        = getStringTrackedProperty( index, vr::Prop_ControllerType_String );
    if ( controllerNamePair.first != SystemError::NoError )
    {
        return "Error";
    }
    std::string cn = controllerNamePair.second;
    if ( strcmp( cn.c_str(), "oculus_touch" ) == 0 )
    {
        return "Touch";
    }
    if ( strcmp( cn.c_str(), "knuckles" ) == 0 )
    {
        return "Knuckles";
    }
    if ( strcmp( cn.c_str(), "vive_controller" ) == 0 )
    {
        return "Wand";
    }
    if ( strcmp( cn.c_str(), "hpmotioncontroller" ) == 0 )
    {
        return "Reverb G2 WMR";
    }
    if ( strcmp( cn.c_str(), "holographic_controller" ) == 0 )
    {
        return "WMR";
    }
    if ( strcmp( cn.c_str(), "vive_cosmos_controller" ) == 0 )
    {
        return "Cosmos";
    }
    if ( strcmp( cn.c_str(), "vive_tracker" ) == 0 )
    {
        return "Tracker";
    }
    if ( strcmp( cn.c_str(), "indexhmd" ) == 0 )
    {
        return "Index Headset";
    }
    if ( cn.find( "vive_tracker_" ) != std::string::npos )
    {
        std::string side = "";
        if ( cn.find( "_left" ) != std::string::npos )
        {
            side = "left ";
        }
        else if ( cn.find( "_right" ) != std::string::npos )
        {
            side = "right ";
        }
        std::string part = "";
        if ( cn.find( "handed" ) != std::string::npos )
        {
            part = " hand";
        }
        else if ( cn.find( "shoulder" ) != std::string::npos )
        {
            part = "shoulder";
        }
        else if ( cn.find( "knee" ) != std::string::npos )
        {
            part = "knee";
        }
        else if ( cn.find( "elbow" ) != std::string::npos )
        {
            part = "elbow";
        }
        else if ( cn.find( "foot" ) != std::string::npos )
        {
            part = "foot";
        }
        else if ( cn.find( "camera" ) != std::string::npos )
        {
            part = "camera";
        }
        else if ( cn.find( "waist" ) != std::string::npos )
        {
            part = "waist";
        }
        return "Tracker " + side + part;
    }
    // TODO add HMD's
    return std::string( controllerNamePair.second );
}

std::vector<int> getAllConnectedDevices( bool onlyWearable )
{
    std::vector<int> output;
    for ( int i = 0; i < static_cast<int>( vr::k_unMaxTrackedDeviceCount );
          i++ )
    {
        if ( deviceConnected( i ) )
        {
            auto deviceClass = getDeviceClass( i );
            if ( onlyWearable )
            {
                if ( deviceClass == vr::TrackedDeviceClass_Controller
                     || deviceClass == vr::TrackedDeviceClass_GenericTracker
                     || deviceClass == vr::TrackedDeviceClass_HMD )
                {
                    output.push_back( i );
                }
            }
            else
            {
                output.push_back( i );
            }
        }
    }
    return output;
}

} // namespace ovr_system_wrapper
