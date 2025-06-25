#ifndef COMMON_HPP
#define COMMON_HPP

#include "Types.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// status codes for the server responses
enum class StatusCode
{

    // success codes
    SUCCESS,
    SUCCESS_REPLACED_SESSION,

    // error codes
    ERROR,
    ERROR_CREATING_SOCKET,
    ERROR_BINDING_SOCKET,
    ERROR_SETTING_SOCKET_OPTIONS,
    ERROR_NO_AVAILABLE_PORT,
    ERROR_INITIALIZING_SOCKET,
    ERROR_NOT_CONNECTED,
    ERROR_SENDING_REQUEST,
    ERROR_RECEIVING_RESPONSE,
    ERROR_INVALID_PORT,
    ERROR_RESTORING_PORT,
    ERROR_CHANGING_PORT,

    ERROR_CLIENT_NOT_IN_LOBBY,
    ERROR_CLIENT_ALREADY_IN_LOBBY,
    ERROR_LOBBY_FULL,
    ERROR_LOBBY_NOT_FOUND,
    ERROR_INVALID_LOBBY_SIZE,
    ERROR_MAX_PLAYERS_REACHED,
    ERROR_MAX_LOBBIES_REACHED,

    ERROR_CREATING_GAMES,
    ERROR_CREATING_ENGINE,
    ERROR_GETTING_GAME_STATE,

    ERROR_DESERIALIZING_REQUEST,
    ERROR_NOT_IMPLEMENTED,
    ERROR_UNKNOWN_METHOD,

    ERROR_SESSION_ALREADY_EXISTS,
    ERROR_SESSION_NOT_FOUND,
    ERROR_NO_SESSION_TOKEN,

    ERROR_SPECTATOR_CANNOT_READY,
    ERROR_PLAYER_ALREADY_READY,
    ERROR_PLAYER_NOT_READY,

    ERROR_SPECTATOR_CANNOT_INTERACT,
    ERROR_INVALID_TOKEN,

    ERROR_NOT_SUPPOSED_TO_HAPPEN,

    ERROR_LOGGING_IN,
    ERROR_USERNAME_TAKEN,
    ERROR_REGISTERING,

    ERROR_INVALID_MESSAGE,
    ERROR_SENDING_MESSAGE,
    ERROR_USER_NOT_FOUND,

    UNKNOWN_PLAYER_TRIED_TO_LEAVE,

};

// gamemode for the lobby
enum class GameMode
{
    CLASSIC,
    ROYALE,
    DUEL,
    ENDLESS,
    NONE, // default value
};

// status codes in string format
std::string getStatusCodeString(StatusCode code);

// malus things with the game

const std::unordered_map<Action, Action> REVERSE_ACTIONS_MAP = {
    {Action::MoveRight, Action::MoveLeft},
    {Action::MoveLeft, Action::MoveRight},
    {Action::RotateLeft, Action::RotateRight},
    {Action::RotateRight, Action::RotateLeft},
};

const std::vector BLOCKED_ACTIONS = {
    Action::MoveDown,   Action::MoveLeft,    Action::MoveRight,
    Action::RotateLeft, Action::RotateRight, Action::InstantFall,
    Action::UseBag,     Action::UseMalus,    Action::UseBonus,
};


const std::unordered_map<GameMode, std::string> GAMEMODE_DESCRIPTIONS = {
        {GameMode::CLASSIC,     "Play against others in classic Tetris mode. Clear lines to score points."},
        {GameMode::DUEL,        "Play against a single opponent in a head-to-head battle."},
        {GameMode::ROYALE,      "Battle royale mode with power-ups and special abilities."},
        {GameMode::ENDLESS,     "Play solo in endless mode. Clear lines to score points."},
        {GameMode::NONE,        "No description available."},
};


struct PlayerScore
{
    int rank;
    std::string name;
    int score;
};

struct ChatMessage
{
    std::string from;
    std::string text;
};



// message type for debugging
enum class MessageType
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
    NONE, // default value
};

// method type for the servers
enum class ServerMethods
{

    // status thing
    GET_CLIENT_STATUS,

    // Lobby methods
    GET_CURRENT_LOBBY,
    LEAVE_LOBBY,
    READY,
    UNREADY,

    // Game methods
    GET_GAME_STATE,
    KEY_STROKE,
    LEAVE_GAME,

    // Lobby server methods
    START_SESSION,
    END_SESSION,
    GET_LOBBY,
    GET_PUBLIC_LOBBIES,
    CREATE_LOBBY,
    JOIN_LOBBY,
    SPECTATE_LOBBY,

    NONE, // default value

};

enum class ClientStatus
{
    IN_MENU,
    IN_LOBBY,
    IN_GAME,
    OFFLINE,
    NONE, // default value
};

// method type in string format
std::string getServerMethodString(ServerMethods method);
std::string getClientStatusString(ClientStatus status);

// stuff for the request / response id
const int INVALID_ID = -1;
const int EMPTY_LOBBY_PORT = -1;

// Buffer size for the server
const int MAX_BUFFER_SIZE = 2048;

// Timeout values for the server / client
const int TIMEOUT_SEC = 5;
const int LOBBY_TIMEOUT_SEC = 1;
const int GAME_TIMEOUT_SEC = 1;
const int CLIENT_TIMEOUT_SEC = 3;
const int TIMEOUT_USEC = 0;
const int GAME_UPDATE_INTERVAL = 50;

// Port for the servers
const int LOBBY_SERVER_PORT = 5050;
const int DB_SERVER_PORT = 8080;
const int FIRST_LOBBY_PORT = 5051;
const int MAX_PORT = 65535;

// Error ret for some methods
const int NO_FILE_DESCRIPTOR = -1;
const int NO_PORT_AVAILABLE = -2;
const int NO_LOBBY_PORT_FOUND = -1;

// limits for the servers
const int MAX_SESSIONS = 200;
const int MAX_GAMES = 20;
const int MAX_LOBBIES = 20;

const int DUAL_LOBBY_SIZE = 2;
const int ENDLESS_LOBBY_SIZE = 1;
const int MIN_LOBBY_SIZE = 3;
const int MAX_LOBBY_SIZE = 9;

const int MAX_REQUEST_ID = 4096;

const int MAX_ENERGY = 200;

// rules for tokens
const int LOBBY_ID_LENGTH = 6;
const int TOKEN_LENGTH = 16;

// stuff idfk stop asking me
const int INDENT_SIZE_CONFIG = 4;

// IP address for the servers
const std::string MASTER_SERVER_IP =
    "0.0.0.0"; // all interfaces (was set to something prior but oh well)


// default values for the game
const std::string GAME_TITLE = "TETRIS ROYALE";
const std::string DEFAULT_NAME = "unknown";
const std::string CONFIG_FILE_NAME = "config.json";

#endif
