#include "Board.h"
// #include "Piece.h"

void mCreateBoard()
{
    Serial.println("Creating Cells ... ");
    this->aCells = new List<List<Cell>>();
    for(int vY = 0; vY < cBoardSize; vY++)
    {
        Serial.print("Creating Row ");
        Serial.print(vY+1);
        Serial.print("... ");
        this->aCells->mAdd(new List<Cell>());
        Serial.println("Done !");
        for(int vX = 0; vX < cBoardSize; vX++)
        {
            Serial.print("Creating Cell ");
            Serial.print((vX+1) * (vY+1));
            Serial.print("... ");
            this->aCells->mGet(vY)->mAdd(new Cell(vX, vY));
            Serial.println("Done !");
        }
    }
    Serial.println("Done !");
    
    this->aPlayer1 = pPlayer1;    
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::King, this->mCell(4, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Queen, this->mCell(3, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Bishop, this->mCell(2, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Bishop, this->mCell(5, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Knight, this->mCell(1, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Knight, this->mCell(6, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Rook, this->mCell(0, 7)));
    this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Rook, this->mCell(7, 7)));

    for(int vIndex = 0; vIndex < 8; vIndex++)
    {
        this->mPlayer1()->mPieces()->mAdd(new Piece(this->mPlayer1()->mColor(), EPieceTypes::Pawn, this->mCell(vIndex, 6)));
    }

    this->aPlayer2 = pPlayer2;
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::King, this->mCell(4, 0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Queen, this->mCell(3,  0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Bishop, this->mCell(2, 0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Bishop, this->mCell(5, 0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Knight, this->mCell(1, 0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Knight, this->mCell(6, 0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Rook, this->mCell(0, 0)));
    this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Rook, this->mCell(7, 0)));
    
    for(int vIndex = 0; vIndex < 8; vIndex++)
    {
        this->mPlayer2()->mPieces()->mAdd(new Piece(this->mPlayer2()->mColor(), EPieceTypes::Pawn, this->mCell(vIndex, 1)));
    }
}

Board::~Board()
{

}

Player* Board::mPlayer1()
{
    return this->aPlayer1;
}

Player* Board::mPlayer2()
{
    return this->aPlayer2;
}

List<List<Cell>>* Board::mCells()
{    
    return this->aCells;
}

Cell* Board::mCell(int pX, int pY)
{
    return this->aCells->mGet(pY)->mGet(pX);
}

void Board::mPrint()
{
    for(int vY = 0; vY < 8; vY++)
    {    
        switch(vY)
        {
            case 0:
            {
                Serial.println("╔═╤═╤═╤═╤═╤═╤═╤═╗");
            }break;
            default:
            {
                Serial.println("╟─┼─┼─┼─┼─┼─┼─┼─╢");
            }break;
        }    
        for(int vX = 0; vX < 8; vX++)
        {
            switch(vX)
            {
                case 0:
                {
                    Serial.print("║");
                }break;
                default:
                {
                    Serial.print("│");
                }break;
            }
            this->aCells->mGet(vY)->mGet(vX)->mPrint();
        }
        Serial.println("║");      
    }
    Serial.println("╚═╧═╧═╧═╧═╧═╧═╧═╝");
} */
