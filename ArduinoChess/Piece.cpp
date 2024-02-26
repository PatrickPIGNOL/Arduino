/* #include "Piece.h"
#include "Cell.h"
#include "Move.h"
#include "EPieceTypes.h"

void mBuildPiece(Piece* this, EColors pColor, EPieceTypes pPieceType, Cell* pCell) 
{
  this->aCell = pCell;
  this->aCell->mPiece(this);
  this->aColor = pColor;
  this->aPieceType = pPieceType;
  switch (this->aPieceType) {
    case EPieceTypes::King:
      {
        if (this->aColor == EColors::White) {
          this->aSymbol = (char*)"♚";
        } else {
          this->aSymbol = (char*)"♔";
        }
      }
      break;
    case EPieceTypes::Queen:
      {
        if (this->aColor == EColors::White) {
          this->aSymbol = (char*)"♛";
        } else {
          this->aSymbol = (char*)"♕";
        }
      }
      break;
    case EPieceTypes::Bishop:
      {
        if (this->aColor == EColors::White) {
          this->aSymbol = (char*)"♝";
        } else {
          this->aSymbol = (char*)"♗";
        }
      }
      break;
    case EPieceTypes::Knight:
      {
        if (this->aColor == EColors::White) {
          this->aSymbol = (char*)"♞";
        } else {
          this->aSymbol = (char*)"♘";
        }
      }
      break;
    case EPieceTypes::Rook:
      {
        if (this->aColor == EColors::White) {
          this->aSymbol = (char*)"♜";
        } else {
          this->aSymbol = (char*)"♖";
        }
      }
      break;
    case EPieceTypes::Pawn:
      {
        if (this->aColor == EColors::White) {
          this->aSymbol = (char*)"♟";
        } else {
          this->aSymbol = (char*)"♙";
        }
      }
      break;
  };
  this->aMoved = false;
  //this->aAvailableMoves = new List<Move>();
}

void mPrintPiece(Piece* this)
{
    Serial.print(this->aSymbol);
} */