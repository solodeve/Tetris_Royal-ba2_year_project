#include "TetrisGame.hpp"

TetrisGame::TetrisGame(const int gWidth, const int gHeight, const int gScore,
                       const int fc, const int lvl, const int totLinesCleared, const std::string &name)
    : gameMatrix(gWidth, gHeight), score(gScore), frameCount(fc), level(lvl),
      totalLinesCleared(totLinesCleared), playerName(name) {
    // this is the constructor of the TetrisGame class
    // might need to write some code here someday
    gameMode = GameMode::NONE;
}

GameMatrix &
TetrisGame::getGameMatrix() {
    return gameMatrix;
}

TetrisFactory &
TetrisGame::getFactory() {
    return factory;
}

Bag &
TetrisGame::getBag() {
    return bag;
}

int
TetrisGame::getScore() const noexcept {
    return score;
}

std::string
TetrisGame::getPlayerName() const noexcept {
    return playerName;
}

GameMode
TetrisGame::getGameMode() noexcept {
    return gameMode;
}

int
TetrisGame::getFrameCount() const noexcept {
    return frameCount;
}

int
TetrisGame::getLevel() const noexcept {
    return level;
}

int
TetrisGame::getLinesCleared() const noexcept {
    return totalLinesCleared;
}

bool
TetrisGame::isGameOver() const noexcept {
    return gameOver;
}

int
TetrisGame::getEnergy() const noexcept {
    return energy;
}

int
TetrisGame::getDarkModeTimer() const noexcept {
    return (darkModeTimer > 0) ? darkModeTimer : 0;
}

int
TetrisGame::getSpeedFactor() const noexcept {
    return speedFactor;
}

int
TetrisGame::getMalusCooldown() const noexcept {
    return malusCooldown;
}

bool
TetrisGame::getBlockControlsFlag() const noexcept {
    return blockControlsFlag;
}

bool
TetrisGame::getReverseControlsFlag() const noexcept {
    return reverseControlsFlag;
}

bool
TetrisGame::getDarkModeFlag() const noexcept {
    return darkModeFlag;
}

Tetromino &
TetrisGame::getNextPiece() {
    return factory.whatIsNextPiece();
}

const Tetromino *
TetrisGame::getHoldPiece() const {
    return bag.peekPiece();
}

std::vector<TetrisGame *>
TetrisGame::getOpponents() {
    // this function is used to get the opponents of the current game
    // it is used for power-ups features

    throw std::runtime_error("TetrisGame::getOpponents() is not implemented");
}

TetrisGame *
TetrisGame::getTarget() {
    // this function is used to get the target of the current game
    // it is used for power-ups features

    throw std::runtime_error("TetrisGame::getTarget() is not implemented");
}

int
TetrisGame::getTargetIndex() {
    // this function is used to get the target index of the current game
    // it is used for power-ups features

    throw std::runtime_error("TetrisGame::getTargetIndex() is not implemented");
}

void
TetrisGame::addOpponent(TetrisGame *opponent) {
    // this function is used to add an opponent to the current game
    // it is used for power-ups features

    (void) opponent;
    throw std::runtime_error("TetrisGame::addOpponent() is not implemented");
}

void
TetrisGame::removeOpponent(TetrisGame *opponent) {
    // this function is used to remove an opponent from the current game
    // it is used for power-ups features

    (void) opponent;
    throw std::runtime_error("TetrisGame::removeOpponent() is not implemented");
}

void
TetrisGame::changePlayerView(int idx) {
    // this function is used to change the player view of the current game
    // it is used for power-ups features

    (void) idx;
    throw std::runtime_error(
        "TetrisGame::changePlayerView() is not implemented");
}

void
TetrisGame::setScore(const int s) {
    score = s;
}

void
TetrisGame::setFrameCount(const int fc) {
    frameCount = fc;
}

void
TetrisGame::setLevel(const int lvl) {
    level = lvl;
}

void
TetrisGame::setTotalLinesCleared(const int lines) {
    totalLinesCleared = lines;
}

void
TetrisGame::setGameOver(const bool flag) {
    gameOver = flag;
}

void
TetrisGame::setPlayerName(const std::string &name) {
    playerName = name;
}

void
TetrisGame::setGameMode(const GameMode mode) {
    gameMode = mode;
}

void
TetrisGame::setEnergy(const int e) {
    energy = e;
}

void
TetrisGame::setDarkModeTimer(const int time) {
    darkModeTimer = time;
}

void
TetrisGame::setSpeedFactor(const int sf) {
    speedFactor = sf;
}

void
TetrisGame::setMalusCooldown(const int mc) {
    malusCooldown = mc;
}

void
TetrisGame::setBlockControlsFlag(const bool flag) {
    blockControlsFlag = flag;
}

void
TetrisGame::setReverseControlsFlag(const bool flag) {
    reverseControlsFlag = flag;
}

void
TetrisGame::setDarkModeFlag(const bool flag) {
    darkModeFlag = flag;
}

void
TetrisGame::incrementScore(const int q) {
    setScore(getScore() + q);
}

void
TetrisGame::incrementFrameCount(const int q) {
    setFrameCount(getFrameCount() + q);
}

void
TetrisGame::incrementLevel(const int q) {
    setLevel(getLevel() + q);
}

void
TetrisGame::incrementLinesCleared(const int q) {
    setTotalLinesCleared(getLinesCleared() + q);
}

void
TetrisGame::incrementEnergy(const int q) {
    int newEnergy = getEnergy() + q;
    setEnergy((newEnergy <= MAX_ENERGY) ? newEnergy : MAX_ENERGY);
}

void
TetrisGame::incrementMalusCooldown(const int q) {
    setMalusCooldown(getMalusCooldown() + q);
}

void
TetrisGame::updateScore(const int linesCleared) {
    int dScore = (linesCleared <= MAX_LINES_CLEARABLE_AT_ONCE)
                     ? ScoreRewardTab[linesCleared]
                     : 0;
    incrementScore(dScore);
}

void
TetrisGame::updateEnergy(const int linesCleared) {
    int dEnergy = (linesCleared <= MAX_LINES_CLEARABLE_AT_ONCE)
                      ? EnergyRewardTab[linesCleared]
                      : 0;
    incrementEnergy(dEnergy);
}

bool
TetrisGame::shouldApplyGravity() const {
    // this function is used to determine if the current piece should fall down
    // it is based on the current frame count and the current level of the game

    const int frame = getFrameCount();
    const int level = getLevel();
    int frame_quantum = 1; // default value

    // if the level is in the speed table, we use the value of the table
    // note that we use the level + speedFactor to get the correct value
    // (speedFactor is used for power-ups)
    if (const auto it = SPEED_TABLE.find(level + speedFactor);
        it != SPEED_TABLE.end()) {
        frame_quantum = it->second;
    }

    // if the frame count is a multiple of the frame quantum, the piece should
    // fall down weird way of doing this, but anyway kekw
    return frame % frame_quantum == 0 && frame >= frame_quantum;
}

bool
TetrisGame::shouldLevelUp() const {
    // this function is used to determine if the level of the game should be
    // incremented it is based on the number of lines cleared and the current
    // level of the game

    // if the number of lines cleared is a multiple of the number of lines to
    // level up, we should level up
    return getLinesCleared() % LINES_TO_LEVELUP == 0 &&
           getLinesCleared() >= LINES_TO_LEVELUP;
}

void
TetrisGame::updateLevelAfterLineClear() {
    // this function is used to update the level of the game after a line clear
    // it is based on the number of lines cleared and the current level of the
    // game

    if (shouldLevelUp()) {
        const int newLineBasedLevel = getLinesCleared() / LINES_TO_LEVELUP;
        const int diff = newLineBasedLevel - getLevel();

        if (diff > 0) {
            incrementLevel(diff);
        }
    }
}

// abstract methods (for power-ups features)

void
TetrisGame::addPenaltyLines(int linesToAdd) {
    (void) linesToAdd;
    throw std::runtime_error(
        "TetrisGame::addPenaltyLines() is not implemented");
}

void
TetrisGame::spawnThunderStrike() {
    throw std::runtime_error(
        "TetrisGame::spawnThunderStrike() is not implemented");
}

void
TetrisGame::increaseFallingSpeed() {
    throw std::runtime_error(
        "TetrisGame::increaseFallingSpeed() is not implemented");
}

void
TetrisGame::decreaseFallingSpeed() {
    throw std::runtime_error(
        "TetrisGame::decreaseFallingSpeed() is not implemented");
}

void
TetrisGame::startDarkMode() {
    throw std::runtime_error("TetrisGame::startDarkMode() is not implemented");
}

void
TetrisGame::startBlockControls() {
    throw std::runtime_error(
        "TetrisGame::startBlockControls() is not implemented");
}

void
TetrisGame::startInvertedControls() {
    throw std::runtime_error(
        "TetrisGame::startInvertedControls() is not implemented");
}

void
TetrisGame::pushSingleBlock() {
    throw std::runtime_error(
        "TetrisGame::pushSingleBlock() is not implemented");
}
