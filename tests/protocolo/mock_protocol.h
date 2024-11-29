#include <gmock/gmock.h>

#include "../../client/comunication/client_protocol.h"
#include "../../common/protocolo-common.h"
#include "../../server/comunication/server_protocol.h"

class MockProtocoloCommon: public ProtocoloCommon {
public:
    explicit MockProtocoloCommon(Socket& socket): ProtocoloCommon(socket) {}
    // Métodos de HandlerSender
    MOCK_METHOD(void, handle_send, (const InfoLobbyMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const CustomizedPlayerInfoMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const ViewLobbiesMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const ChooseLobbyMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const CreateLobbyMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const GoBackMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const ExitFromLobbyMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const StartGameMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const PlayerInfoMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const PickupDropMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const StartActionMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const StopActionMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const SendLobbiesListMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const EverythingOkMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const ErrorMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const SendMapMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const GameEndedMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const WinnerMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const UpdatedPlayerInfoMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const ProjectileInfoMsg& msg), (override));
    MOCK_METHOD(void, handle_send, (const NotProyectileInfo& msg), (override));
    MOCK_METHOD(void, handle_send, (const ShootMsg& msg), (override));

    // Métodos de HandlerReceiver
    MOCK_METHOD(void, handle_recv, (InfoLobbyMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (CustomizedPlayerInfoMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (ViewLobbiesMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (ChooseLobbyMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (CreateLobbyMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (GoBackMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (ExitFromLobbyMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (StartGameMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (PlayerInfoMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (PickupDropMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (StartActionMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (StopActionMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (SendLobbiesListMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (EverythingOkMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (ErrorMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (SendMapMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (GameEndedMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (WinnerMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (UpdatedPlayerInfoMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (ProjectileInfoMsg & msg), (override));
    MOCK_METHOD(void, handle_recv, (NotProyectileInfo & msg), (override));
    MOCK_METHOD(void, handle_recv, (ShootMsg & msg), (override));
};
