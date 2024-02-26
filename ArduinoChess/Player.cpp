/* #include "Player.h"
#include "Piece.h"

Player::Player(EColors pColor, EPlayerType pPlayerType)
{
    this->aColor = pColor;
    this->aPlayerType = pPlayerType;
    this->aPieces = new List<Piece>();
}

Player::~Player()
{
    this->aPieces->mClear();
    delete this->aPieces;
}

EColors Player::mColor()
{
    return this->aColor;
}

List<Piece>* Player::mPieces()
{
    return this->aPieces;
}

List<Piece>* Player::mJail()
{
    return this->aJail;
}

 */