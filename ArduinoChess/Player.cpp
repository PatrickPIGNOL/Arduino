#include "Player.h"
#include "Piece.h"

Player* NewPlayer(Board* pBoard, SColors::EColors pColor, SPlayerType::EPlayerType pPlayerType)
{
    Player* vThis = (Player*)malloc(sizeof(Player));
    vThis->aBoard = pBoard;
    vThis->aColor = pColor;
    vThis->aPlayerType = pPlayerType;
    vThis->aPieces = (Piece**)malloc(16 * sizeof(Piece*));
    for(int vIndex = 0; vIndex < 16; vIndex++)
    {
      if(vThis->aColor == SColors::EColors::Black)
      {
        if((vIndex == 0)|| (vIndex == 7))
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[vIndex / 8][vIndex % 8], SPieceType::EPieceType::Rook);
        }
        else if((vIndex == 1) || (vIndex == 6))
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[vIndex / 8][vIndex % 8], SPieceType::EPieceType::Knight);
        }
        else if((vIndex == 2) || (vIndex == 5))
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[vIndex / 8][vIndex % 8], SPieceType::EPieceType::Bishop);
        }
        else if(vIndex == 3)
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[vIndex / 8][vIndex % 8], SPieceType::EPieceType::Queen);
        }
        else if(vIndex == 4)
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[vIndex / 8][vIndex % 8], SPieceType::EPieceType::King);
        }
        else if(vIndex > 7)
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[vIndex / 8][vIndex % 8], SPieceType::EPieceType::Pawn);
        }
      }
      else if(vThis->aColor == SColors::EColors::White)
      {
        if(vIndex < 8)
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[7 + vIndex / 8][vIndex % 8], SPieceType::EPieceType::Pawn);
        }
        else if((vIndex == 8) || (vIndex == 15))
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[7 + vIndex / 8][vIndex % 8], SPieceType::EPieceType::Rook);
        }
        else if((vIndex == 9) || (vIndex == 14))
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[7 + vIndex / 8][vIndex % 8], SPieceType::EPieceType::Knight);
        }
        else if((vIndex == 10) || (vIndex == 13))
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[7 + vIndex / 8][vIndex % 8], SPieceType::EPieceType::Bishop);
        }
        else if(vIndex == 11)
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[7 + vIndex / 8][vIndex % 8], SPieceType::EPieceType::Queen);
        }
        else if(vIndex == 12)
        {
          vThis->aPieces[vIndex] = NewPiece(vThis, vThis->aBoard->aCells[7 + vIndex / 8][vIndex % 8], SPieceType::EPieceType::King);
        }
      }
    }
    return vThis;
}

void FreePlayer(Player* pThis)
{
    for(int vIndex = 0; vIndex < 16; vIndex++)
    {
      FreePiece(pThis->aPieces[vIndex]);
    }
    free(pThis->aPieces);
    free(pThis);
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
