#include "SteamVRTabController.h"
#include <QQuickWindow>
#include "../overlaycontroller.h"
#include "../utils/update_rate.h"

QT_USE_NAMESPACE

// application namespace
namespace advsettings
{
void SteamVRTabController::initStage1()
{
    dashboardLoopTick();
}

void SteamVRTabController::initStage2( OverlayController* var_parent )
{
    this->parent = var_parent;
    synchSteamVR();
}

void SteamVRTabController::dashboardLoopTick()
{
    if ( updateRate.shouldSubjectNotRun( UpdateSubject::SteamVrTabController ) )
    {
        return;
    }
    synchSteamVR();
}

void SteamVRTabController::synchSteamVR()
{
    // Un-comment these if other Apps make heavy use OR ADDED to STEAMVR
    // officially
    setPerformanceGraph( performanceGraph() );
    // setSystemButton(systemButton());
    setMultipleDriver( multipleDriver() );
    setDND( dnd() );
    setNoFadeToGrid( noFadeToGrid() );
    setCameraActive( cameraActive() );
    setCameraRoom( cameraRoom() );
    setCameraDashboard( cameraDashboard() );
    setCameraBounds( cameraBounds() );
}

bool SteamVRTabController::performanceGraph() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_Perf_Section, vr::k_pch_Perf_PerfGraphInHMD_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_performanceGraphToggle;
}

void SteamVRTabController::setPerformanceGraph( const bool value,
                                                const bool notify )
{
    if ( m_performanceGraphToggle != value )
    {
        m_performanceGraphToggle = value;
        ovr_settings_wrapper::setBool( vr::k_pch_Perf_Section,
                                       vr::k_pch_Perf_PerfGraphInHMD_Bool,
                                       m_performanceGraphToggle );
        if ( notify )
        {
            emit performanceGraphChanged( m_performanceGraphToggle );
        }
    }
}

bool SteamVRTabController::multipleDriver() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_SteamVR_Section,
        vr::k_pch_SteamVR_ActivateMultipleDrivers_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_multipleDriverToggle;
}

void SteamVRTabController::setMultipleDriver( const bool value,
                                              const bool notify )
{
    if ( m_multipleDriverToggle != value )
    {
        m_multipleDriverToggle = value;
        ovr_settings_wrapper::setBool(
            vr::k_pch_SteamVR_Section,
            vr::k_pch_SteamVR_ActivateMultipleDrivers_Bool,
            m_multipleDriverToggle );
        if ( notify )
        {
            emit multipleDriverChanged( m_multipleDriverToggle );
        }
    }
}

bool SteamVRTabController::noFadeToGrid() const
{
    auto p = ovr_settings_wrapper::getBool( vr::k_pch_SteamVR_Section,
                                            vr::k_pch_SteamVR_DoNotFadeToGrid );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_noFadeToGridToggle;
}

void SteamVRTabController::setNoFadeToGrid( const bool value,
                                            const bool notify )
{
    if ( m_noFadeToGridToggle != value )
    {
        m_noFadeToGridToggle = value;
        ovr_settings_wrapper::setBool( vr::k_pch_SteamVR_Section,
                                       vr::k_pch_SteamVR_DoNotFadeToGrid,
                                       m_noFadeToGridToggle );
        if ( notify )
        {
            emit noFadeToGridChanged( m_noFadeToGridToggle );
        }
    }
}

bool SteamVRTabController::systemButton() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_SteamVR_Section,
        vr::k_pch_SteamVR_SendSystemButtonToAllApps_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_systemButtonToggle;
}

void SteamVRTabController::setSystemButton( const bool value,
                                            const bool notify )
{
    if ( m_systemButtonToggle != value )
    {
        m_systemButtonToggle = value;
        ovr_settings_wrapper::setBool(
            vr::k_pch_SteamVR_Section,
            vr::k_pch_SteamVR_SendSystemButtonToAllApps_Bool,
            m_systemButtonToggle );
        if ( notify )
        {
            emit systemButtonChanged( m_systemButtonToggle );
        }
    }
}

bool SteamVRTabController::dnd() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_Notifications_Section,
        vr::k_pch_Notifications_DoNotDisturb_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_dnd;
}

void SteamVRTabController::setDND( const bool value, const bool notify )
{
    if ( m_dnd != value )
    {
        m_dnd = value;
        ovr_settings_wrapper::setBool(
            vr::k_pch_Notifications_Section,
            vr::k_pch_Notifications_DoNotDisturb_Bool,
            m_dnd );
        if ( notify )
        {
            emit dNDChanged( m_dnd );
        }
    }
}

/*------------------------------------------*/
/* -----------Camera Setting----------------*/

bool SteamVRTabController::cameraActive() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_Camera_Section, vr::k_pch_Camera_EnableCamera_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_cameraActive;
}

void SteamVRTabController::setCameraActive( const bool value,
                                            const bool notify )
{
    if ( m_cameraActive != value )
    {
        m_cameraActive = value;
        ovr_settings_wrapper::setBool( vr::k_pch_Camera_Section,
                                       vr::k_pch_Camera_EnableCamera_Bool,
                                       m_cameraActive );
        if ( notify )
        {
            emit cameraActiveChanged( m_cameraActive );
        }
    }
}

bool SteamVRTabController::cameraBounds() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_Camera_Section,
        vr::k_pch_Camera_EnableCameraForCollisionBounds_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_cameraBounds;
}

void SteamVRTabController::setCameraBounds( const bool value,
                                            const bool notify )
{
    if ( m_cameraBounds != value )
    {
        m_cameraBounds = value;
        ovr_settings_wrapper::setBool(
            vr::k_pch_Camera_Section,
            vr::k_pch_Camera_EnableCameraForCollisionBounds_Bool,
            m_cameraBounds );
        if ( notify )
        {
            emit cameraBoundsChanged( m_cameraBounds );
        }
    }
}

bool SteamVRTabController::cameraRoom() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_Camera_Section,
        vr::k_pch_Camera_EnableCameraForRoomView_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_cameraRoom;
}

void SteamVRTabController::setCameraRoom( const bool value, const bool notify )
{
    if ( m_cameraRoom != value )
    {
        m_cameraRoom = value;
        ovr_settings_wrapper::setBool(
            vr::k_pch_Camera_Section,
            vr::k_pch_Camera_EnableCameraForRoomView_Bool,
            m_cameraRoom );
        if ( notify )
        {
            emit cameraRoomChanged( m_cameraRoom );
        }
    }
}

bool SteamVRTabController::cameraDashboard() const
{
    auto p = ovr_settings_wrapper::getBool(
        vr::k_pch_Camera_Section,
        vr::k_pch_Camera_EnableCameraInDashboard_Bool );

    if ( p.first == ovr_settings_wrapper::SettingsError::NoError )
    {
        return p.second;
    }
    return m_cameraDashboard;
}

void SteamVRTabController::updateRXTXList()
{
    emit updateRXTX( true );
}

void SteamVRTabController::searchRXTX()
{
    m_deviceList.clear();
    int hmdIndex = -1;
    auto indexList = ovr_system_wrapper::getAllConnectedDevices( true );
    m_dongleCountCur = 0;
    for ( auto device : indexList )
    {
        if ( vr::TrackedDeviceClass_HMD
             == ovr_system_wrapper::getDeviceClass( device ) )
        {
            hmdIndex = device;
            continue;
        }
        m_deviceList.push_back( DeviceInfo{ device } );
        GatherDeviceInfo( m_deviceList.back() );
    }

    if ( hmdIndex != -1 )
    {
        auto dongleList
            = ovr_system_wrapper::getStringTrackedProperty(
                  hmdIndex, vr::Prop_AllWirelessDongleDescriptions_String )
                  .second;
        m_unparsedDongleString = QString::fromStdString( dongleList );
        int count = 0;
        if ( !dongleList.empty() )
        {
            count++;
        }
        for ( auto c : dongleList )
        {
            if ( c == ';' )
            {
                count++;
            }
        }
        m_dongleCountMax = count;
        if ( static_cast<int>( m_deviceList.size() ) < m_dongleCountMax )
        {
            auto DSNFullList = getDongleSerialList( dongleList );
            for ( auto dSN : DSNFullList )
            {
                bool isPaired = false;
                for ( auto pairedDev : m_deviceList )
                {
                    if ( QString::fromStdString( pairedDev.conDongle ) == dSN )
                    {
                        isPaired = true;
                        break;
                    }
                }
                if ( isPaired )
                {
                    continue;
                }
                m_deviceList.push_back( DeviceInfo{} );
                AddUnPairedDevice( m_deviceList.back(), dSN.toStdString() );
                // TODO create
            }
        }
    }
    return;
}

void SteamVRTabController::AddUnPairedDevice( DeviceInfo& device,
                                              std::string donSN )
{
    device.conDongle = donSN;
    if ( donSN.find( "-RYB" ) != std::string::npos
         || donSN.find( "-LYM" ) != std::string::npos )
    {
        device.dongleType = "Headset";
    }
    // TODO 1yx SN
    else if ( std::regex_match( donSN, std::regex( "(.*)(-[0-9]YX)" ) ) )
    {
        device.dongleType = "Tundra Dongle";
    }
    else
    {
        device.dongleType = "Standard Dongle";
    }
    device.index = -1;
    device.txName = "No Connection";
    device.serialNumber = "n/a";
    device.deviceName = "No Connection";
}

void SteamVRTabController::GatherDeviceInfo( DeviceInfo& device )
{
    std::string cd = ovr_system_wrapper::getStringTrackedProperty(
                         device.index, vr::Prop_ConnectedWirelessDongle_String )
                         .second;
    if ( cd.empty() || cd == " " )
    {
        cd = "n/a";
        device.dongleType = "n/a";
    }
    else
    {
        m_dongleCountCur++;
        if ( cd.find( "-RYB" ) != std::string::npos
             || cd.find( "-LYM" ) != std::string::npos )
        {
            device.dongleType = "Headset";
        }
        // TODO 1yx SN
        else if ( std::regex_match( cd, std::regex( "(.*)(-[0-9]YX)" ) ) )
        {
            device.dongleType = "Tundra Dongle";
        }
        else
        {
            device.dongleType = "Standard Dongle";
        }
    }
    device.conDongle = cd;

    std::string dd = ovr_system_wrapper::getStringTrackedProperty(
                         device.index, vr::Prop_SerialNumber_String )
                         .second;
    if ( dd.empty() || dd == " " )
    {
        dd = "n/a";
    }
    device.txName = dd;

    auto devClass = ovr_system_wrapper::getDeviceClass( device.index );
    if ( devClass == vr::TrackedDeviceClass_HMD
         || devClass == vr::TrackedDeviceClass_Controller
         || devClass == vr::TrackedDeviceClass_GenericTracker )
    {
        device.hasName = true;
        device.deviceName = ovr_system_wrapper::getDeviceName( device.index );
    }
    else
    {
        if ( device.txName.find( "LHB-" ) != std::string::npos )
        {
            device.deviceName = "Lighthouse";
        }
    }
    int role = ovr_system_wrapper::getInt32TrackedProperty(
                   device.index, vr::Prop_ControllerRoleHint_Int32 )
                   .second;
    if ( role == 1 )
    {
        device.deviceName += " (L)";
    }
    else if ( role == 2 )
    {
        device.deviceName += " (R)";
    }
}

void SteamVRTabController::launchBindingUI()
{
    vr::VRActionSetHandle_t actionHandle = 0;
    vr::VRInputValueHandle_t inputHandle = 0;

    auto error2 = vr::VRInput()->GetInputSourceHandle( "/user/hand/right",
                                                       &inputHandle );
    if ( error2 != vr::VRInputError_None )
    {
        LOG( ERROR )
            << "failed to get input handle? is your right controller on?";
    }
    auto error = vr::VRInput()->OpenBindingUI(
        application_strings::applicationKey, actionHandle, inputHandle, false );
    if ( error != vr::VRInputError_None )
    {
        LOG( ERROR ) << "Input Error: " << error;
    }
}

void SteamVRTabController::setCameraDashboard( const bool value,
                                               const bool notify )
{
    if ( m_cameraDashboard != value )
    {
        m_cameraDashboard = value;
        ovr_settings_wrapper::setBool(
            vr::k_pch_Camera_Section,
            vr::k_pch_Camera_EnableCameraInDashboard_Bool,
            m_cameraDashboard );
        if ( notify )
        {
            emit cameraDashboardChanged( m_cameraDashboard );
        }
    }
}

void SteamVRTabController::restartSteamVR()
{
    QString cmd = QString( "cmd.exe /C restartvrserver.bat \"" )
                  + parent->getVRRuntimePathUrl().toLocalFile()
                  + QString( "\"" );
    LOG( INFO ) << "SteamVR Restart Command: " << cmd;
    QProcess::startDetached( cmd );
}

Q_INVOKABLE unsigned SteamVRTabController::getRXTXCount()
{
    return static_cast<unsigned>( m_deviceList.size() );
}

Q_INVOKABLE QString SteamVRTabController::getTXList( int i )
{
    return QString::fromStdString( m_deviceList[i].txName );
}

Q_INVOKABLE QString SteamVRTabController::getDeviceName( int i )
{
    return QString::fromStdString( m_deviceList[i].deviceName );
}

Q_INVOKABLE QString SteamVRTabController::getRXList( int i )
{
    return QString::fromStdString( m_deviceList[i].conDongle );
}
Q_INVOKABLE QString SteamVRTabController::getDongleType( int i )
{
    return QString::fromStdString( m_deviceList[i].dongleType );
}
Q_INVOKABLE QString SteamVRTabController::getDongleUsage()
{
    return QString::fromStdString( std::to_string( m_dongleCountCur ) + "/"
                                   + std::to_string( m_dongleCountMax ) );
}
Q_INVOKABLE void SteamVRTabController::pairDevice( QString sn )
{
    if ( !isSteamVRTracked( sn ) )
    {
        LOG( WARNING ) << sn.toStdString()
                       << " Is Not a SteamVR Dongle, skipping Pair";
        return;
    }
    m_last_pair_sn = sn;
    auto req = QNetworkRequest();
    req.setUrl( QUrl( "ws://127.0.0.1:27062" ) );
    req.setRawHeader(
        QByteArray( "Referer" ),
        QByteArray(
            "http://localhost:27062/lighthouse/webinterface/pairing.html" ) );
    m_webSocket.open( req );
    connect( &m_webSocket,
             &QWebSocket::connected,
             this,
             &SteamVRTabController::onConnected );
    connect( &m_webSocket,
             &QWebSocket::disconnected,
             this,
             &SteamVRTabController::onDisconnect );
    connect( &m_webSocket,
             &QWebSocket::textMessageReceived,
             this,
             &SteamVRTabController::onMsgRec );
    return;
}
bool SteamVRTabController::isSteamVRTracked( QString sn )
{
    return m_unparsedDongleString.contains( sn );
}
void SteamVRTabController::onConnected()
{
    m_webSocket.sendTextMessage( QStringLiteral( "mailbox_open OVRAS_pair" ) );
    QString messageout = "mailbox_send lighthouse_pairing "
                         "{\"type\":\"start_pairing\", "
                         "\"returnAddress\":\"OVRAS_pair\", "
                         "\"serial\":\"";
    messageout.append( m_last_pair_sn );
    messageout.append( QString::fromStdString( "\", \"timeoutSeconds\":15}" ) );
    emit pairStatusChanged( QString( "Pairing..." ) );
    if ( m_last_pair_sn == "" )
    {
        LOG( ERROR ) << "No Last SN to pair, this shouldn't happen";
    }
    m_webSocket.sendTextMessage( messageout );
    // m_webSocket.close();
}
void SteamVRTabController::onDisconnect()
{
    LOG( INFO ) << "Pair WS disconnect";
    m_webSocket.close();
}
void SteamVRTabController::onMsgRec( QString Msg )
{
    if ( Msg.contains( "success" ) )
    {
        LOG( INFO ) << "Pair Success";
        emit pairStatusChanged( QString( "Success" ) );
    }
    if ( Msg.contains( "timeout" ) )
    {
        LOG( INFO ) << "Pair Timeout";
        emit pairStatusChanged( QString( "Timeout" ) );
    }
    m_webSocket.close();
}
std::vector<QString>
    SteamVRTabController::getDongleSerialList( std::string deviceString )
{
    std::vector<QString> dongleList;
    size_t pos = 0;

    while ( ( pos = deviceString.find( ',' ) ) != std::string::npos )
    {
        dongleList.push_back(
            QString::fromStdString( deviceString.substr( 0, pos ) ) );
        pos = deviceString.find( ';' );
        if ( pos != std::string::npos )
        {
            deviceString.erase( 0, pos + 1 );
            continue;
        }
        else
        {
            pos = deviceString.find( ',' );
            if ( pos == std::string::npos )
            {
                break;
            }
            dongleList.push_back(
                QString::fromStdString( deviceString.substr( 0, pos ) ) );
            break;
        }
        break;
    }
    return dongleList;
}

} // namespace advsettings
