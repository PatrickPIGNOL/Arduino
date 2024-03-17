#include "Piece.h"
#include "Cell.h"
#include "Move.h"
#include "EPieceTypes.h"

Piece* NewPiece(Player* pOwner, Cell* pCell, SPieceTypes::EPieceTypes pPieceType)
{
  Piece* vThis = (Piece*)malloc(sizeof(Piece));
  this->aPieceType = pPieceType;
  switch (this->aPieceType)
  {
    case SPieceTypes::EPieceTypes::King:
      {
        if (this->aColor == SColors::EColors::White) 
        {
          this->aSymbol = '♔';
          this->aLetter = 'K';
        } 
        else 
        {
          this->aSymbol = '♚';
          this->aLetter = 'k';
        }
      }
      break;
    case SPieceTypes::EPieceTypes::Queen:
      {
        if (this->aColor == SColors::EColors::White) 
        {
          this->aSymbol = '♕';
          this->aLetter = 'Q';
        } 
        else 
        {
          this->aSymbol = '♛';
          this->aLetter = 'q';
        }
      }
      break;
    case SPieceTypes::EPieceTypes::Bishop:
      {
        if (this->aColor == SColors::EColors::White) 
        {
          this->aSymbol = '♗';
          this->aLetter = 'B';
        } 
        else 
        {
          this->aSymbol = '♝';
          this->aLetter = 'b';
        }
      }
      break;
    case SPieceTypes::EPieceTypes::Knight:
      {
        if (this->aColor == SColors::EColors::White) 
        {
          this->aSymbol = '♘';
          this->aLetter = 'N';
        }
        else 
        {
          this->aSymbol = '♞';
          this->aLetter = 'N';
        }
      }
      break;
    case SPieceTypes::EPieceTypes::Rook:
      {
        if (this->aColor == SColors::EColors::White) 
        {
          this->aSymbol = '♖';
          this->aLetter = 'R';
        }
        else
        {
          this->aSymbol = '♜';
          this->aLetter = 'r';
        }
      }
      break;
    case SPieceTypes::EPieceTypes::Pawn:
      {
        if (this->aColor == SColors::EColors::White) 
        {
          this->aSymbol = '♙';
          this->aLetter = 'P';
        }
        else 
        {
          this->aSymbol = '♟';
          this->aLetter = 'p';
        }
      }
      break;
  };
  vThis->aSymbol = "";
  vThis->aPieceType = SPieceTypes::EPieceTypes::None;
  vThis->aOwner = pOwner;
  vThis->aColor = vThis->aOwner->aColor;
  vThis->aMoved = false;
  vThis->aJailed = false;
  vThis->aCell = pCell;
  vThis->aCell->aPiece = vThis;
  return vThis;
}

void FreePiece(Piece* pThis)
{
  if(pThis->aCell != NULL)
  {
    pThis->aCell->Piece = NULL;
    pThis->aCell = NULL
  }
  free(pThis);
}

void mPrintPiece(Piece* pThis)
{
    Serial.print(pThis->aSymbol);
}
