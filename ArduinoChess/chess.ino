#include <Arduino.h>
#include "Game.h"

Game* vGame;

void setup() 
{
    Serial.begin(9600);
    mInit();
}

void loop() 
{
    Serial.println("Loop:");
    Serial.println("Update:");
    mUpdate();
    Serial.println("Render:");
    mRender();
}

void mInit()
{   
    vGame = (Game*)malloc(sizeof(Game));
    vGame->aState = EStates::ChooseMode;
}

void mUpdate()
{
    switch(vGame->aState)
    {
        case EStates::ChooseMode:
        {
            vGame->aBoard = (Board*)malloc(sizeof(Board));
            vGame->aBoard->aPlayer1 = (Player*)malloc(sizeof(Player));
            vGame->aBoard->aPlayer2 = (Player*)malloc(sizeof(Player));
            Serial.println("Choose game mode :");
            Serial.println("1 - Human vs Human");
            Serial.println("2 - Human vs Computer");
            Serial.println("3 - Computer vs Human");
            Serial.println("4 - Computer vs Computer");
            char vInput = 0;
            while(vInput < '1' || vInput > '4')
            {
                if(Serial.available())
                {
                    vInput = Serial.read();
                    Serial.flush();
                }
            }
            switch(vInput)
            {
                case '1':
                {
                    mBuildPlayer(vGame->aBoard->aPlayer1, EPlayerType::Human, EColors::White);
                    mBuildPlayer(vGame->aBoard->aPlayer2, EPlayerType::Human, EColors::Black);
                    vGame->aState = EStates::InitBoard;
                }break;
                case '2':
                {
                    mBuildPlayer(vGame->aBoard->aPlayer1, EPlayerType::Human, EColors::White);
                    mBuildPlayer(vGame->aBoard->aPlayer2, EPlayerType::Computer, EColors::Black);
                    vGame->aState = EStates::ChooseDifficulty;
                }break;
                case '3':
                {
                    mBuildPlayer(vGame->aBoard->aPlayer1, EPlayerType::Computer, EColors::White);
                    mBuildPlayer(vGame->aBoard->aPlayer2, EPlayerType::Human, EColors::Black);
                    vGame->aState = EStates::ChooseDifficulty;
                }break;
                case '4':
                {
                    mBuildPlayer(vGame->aBoard->aPlayer1, EPlayerType::Computer, EColors::White);
                    mBuildPlayer(vGame->aBoard->aPlayer2, EPlayerType::Computer, EColors::Black);
                    vGame->aState = EStates::ChooseDifficulty;                    
                }break;
            };
        }break;
        case EStates::ChooseDifficulty:
        {
            Serial.println("Choose difficuty :");
            Serial.println("0 - Idiot");
            Serial.println("1 - Basic");
            Serial.println("2 - Childish");
            Serial.println("3 - Practice");
            Serial.println("4 - Knowledge");               
            Serial.println("5 - Average");
            Serial.println("6 - Good");
            Serial.println("7 - Great");
            Serial.println("8 - Grand Master");
            Serial.println("9 - God");
            char vInput = 0;
            while(vInput < '1' || vInput > '9')
            {
                if(Serial.available())
                {
                    vInput = Serial.read();
                    Serial.flush();
                }
            }
            Serial.print("Choosen difficuty : ");
            switch(vInput)
            {
                case '0':
                {
                    vGame->aDifficulty = 0;
                    vGame->aDepht = 0;
                    Serial.println("Idiot");                
                    vGame->aState = EStates::InitBoard;
                }break;
                case '1':
                {
                    vGame->aDifficulty = 10;
                    vGame->aDepht = 1;
                    Serial.println("Basic");                
                    vGame->aState = EStates::InitBoard;
                }break;
                case '2':
                {
                    vGame->aDifficulty = 20;
                    vGame->aDepht = 2;
                    Serial.println("Childish");                
                    vGame->aState = EStates::InitBoard;
                }break;
                case '3':
                {
                    vGame->aDifficulty = 30;
                    vGame->aDepht = 3;
                    Serial.println("Practice");                
                    vGame->aState = EStates::InitBoard;
                }break;
                case '4':
                {
                    vGame->aDifficulty = 40;
                    vGame->aDepht = 4;
                    Serial.println("Knowledge");                
                    vGame->aState = EStates::InitBoard;
                }break;
                case '5':
                {
                    vGame->aDifficulty = 50;
                    vGame->aDepht = 5;
                    Serial.println("Average");                
                    vGame->aState = EStates::InitBoard;
                }break;                    
                case '6':
                {
                    vGame->aDifficulty = 60;                        
                    vGame->aDepht = 6;
                    Serial.println("Good");                
                    vGame->aState = EStates::InitBoard;
                }break;                    
                case '7':
                {
                    vGame->aDifficulty = 70;                        
                    vGame->aDepht = 7;
                    Serial.println("Great");                
                    vGame->aState = EStates::InitBoard;
                }break;
                case '8':
                {
                    vGame->aDifficulty = 80;                        
                    vGame->aDepht = 8;
                    Serial.println("Grand Master");                
                    vGame->aState = EStates::InitBoard;
                }break;                    
                case '9':
                {
                    vGame->aDifficulty = 100;       
                    vGame->aDepht = 10;
                    Serial.println("God");                
                    vGame->aState = EStates::InitBoard;
                }break;
            };
        }break;
        case EStates::InitBoard:
        {
            vGame->aBoard->aCells = (Cell***)malloc(sizeof(Cell**[8]));
            EColors vColor;
            for(int vY = 0; vY < 8; vY++)
            {
                vGame->aBoard->aCells[vY] = (Cell**)malloc(sizeof(Cell*[8]));
                for(int vX = 0; vX < 8; vX++)
                {            
                    vGame->aBoard->aCells[vY][vX] = (Cell*)malloc(sizeof(Cell));
                    mBuildCell(vGame->aBoard->aCells[vY][vX], vX, vY);
                    if(vY < 5)
                    {
                        vColor = EColors::Black;
                    }
                    else
                    {
                        vColor = EColors::White;
                    }            
                    if(vY == 0 || vY == 7)
                    {                              
                        vGame->aBoard->aCells[vY][vX]->aPiece = (Piece*)malloc(sizeof(Piece));
                        if(vColor == EColors::White)
                        {
                            mAddPiece(vGame->aBoard->aPlayer1, vGame->aBoard->aCells[vY][vX]->aPiece);
                        }
                        else
                        {
                            mAddPiece(vGame->aBoard->aPlayer2, vGame->aBoard->aCells[vY][vX]->aPiece);
                        }
                        if((vX == 0) || (vX == 7))
                        {                
                            mBuildPiece(vGame->aBoard->aCells[vY][vX]->aPiece, vColor, EPieceTypes::Rook);
                        }
                        if((vX == 1) || (vX == 6))
                        {
                            mBuildPiece(vGame->aBoard->aCells[vY][vX]->aPiece, vColor, EPieceTypes::Knight);
                        }
                        if((vX == 2) || (vX == 5))
                        {
                            mBuildPiece(vGame->aBoard->aCells[vY][vX]->aPiece, vColor, EPieceTypes::Bishop);
                        }
                        if(vX == 3)
                        {
                            mBuildPiece(vGame->aBoard->aCells[vY][vX]->aPiece, vColor, EPieceTypes::Queen);
                        }
                        if(vX == 4)
                        {
                            mBuildPiece(vGame->aBoard->aCells[vY][vX]->aPiece, vColor, EPieceTypes::King);
                        }               
                    }
                    if((vY == 1) || (vY == 6))
                    {
                        vGame->aBoard->aCells[vY][vX]->aPiece = (Piece*)malloc(sizeof(Piece));
                        if(vColor == EColors::White)
                        {
                            mAddPiece(vGame->aBoard->aPlayer1, vGame->aBoard->aCells[vY][vX]->aPiece);
                        }
                        else
                        {
                            mAddPiece(vGame->aBoard->aPlayer2, vGame->aBoard->aCells[vY][vX]->aPiece);
                        }
                        mBuildPiece(vGame->aBoard->aCells[vY][vX]->aPiece, vColor, EPieceTypes::Pawn);
                    }
                }
            }
            vGame->aState = EStates::StartPlaying;
        }break;
        case EStates::StartPlaying:
        {
            vGame->aState = EStates::WhitePlayerTurn;
        }break;        
        case EStates::WhitePlayerTurn:
        {
            switch(vGame->aBoard->aPlayer1->aPlayerType)
            {
                case EPlayerType::Human:
                {                    
                    bool vPlayed = false;
                    String vInput = "";
                    while(! vPlayed)
                    {
                        Serial.println("Witch Piece to move ? (ex: e2-e4)");
                        while(!Serial.available()){}
                        vInput = Serial.readString();
                        vInput.toLowerCase();
                        int vStartX = vInput.charAt(0) - 'a';
                        int vStartY = 8 - (vInput.charAt(1) - '0');
                        if(vInput.charAt(2) != '-')
                        {
                            Serial.println("/!\\ Bad format /!\\");
                            continue;
                        }
                        int vEndX = vInput.charAt(3) - 'a';
                        int vEndY = 8 - (vInput.charAt(4) - '0');
                        if(vInput.length() > 6)
                        {
                            Serial.println("/!\\ Bad format /!\\");
                            continue;
                        }
                        if(!(vStartX >= 0 && vStartX < 8))
                        {
                            Serial.println("/!\\ Start X out of board /!\\");
                            continue;
                        }
                        if(!(vStartY >= 0 && vStartY < 8))
                        {
                            Serial.println("/!\\ Start Y out of board /!\\");
                            continue;
                        }
                        if(!(vEndX >= 0 && vEndX < 8))
                        {
                            Serial.println("/!\\ End X out of board /!\\");
                            continue;
                        }                        
                        if(!(vEndY >= 0 && vEndY < 8))
                        {
                            Serial.println("/!\\ End Y out of board /!\\");
                            continue;
                        }
                        if(vGame->aBoard->aCells[vStartY][vStartX]->aPiece == NULL)
                        {
                            Serial.println("/!\\ No piece at start /!\\");
                            continue;
                        }
                        Piece* vStartPiece = vGame->aBoard->aCells[vStartY][vStartX]->aPiece; 
                        if(vStartPiece->aColor == EColors::Black)
                        {
                            Serial.println("/!\\ The piece at start is not white /!\\");
                            continue;
                        }
                        switch(vStartPiece->aPieceType)
                        {
                            case EPieceTypes::Pawn:
                            {
                                if(vEndX == vStartX)
                                {
                                    if(vStartPiece->aMoved == false)
                                    {
                                        if(vStartY - vEndY > 2)
                                        {
                                            Serial.println("/!\\ Illegal Move /!\\");
                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        if(vStartY - vEndY > 1)
                                        {
                                            Serial.println("/!\\ Illegal Move /!\\");
                                            continue;
                                        }                                        
                                    }
                                    if(vGame->aBoard->aCells[vStartY - 1][vStartX]->aPiece != NULL)
                                    {
                                        Serial.println("/!\\ Illegal Move /!\\");
                                        continue;
                                    }
                                    if(vStartY - vEndY > 2)
                                    {
                                        if(vGame->aBoard->aCells[vStartY - 2][vStartX]->aPiece != NULL)
                                        {
                                            Serial.println("/!\\ Illegal Move /!\\");
                                            continue;
                                        }
                                    }
                                    vGame->aBoard->aCells[vStartY][vStartX]->aPiece = NULL;
                                    vGame->aBoard->aCells[vEndY][vEndX]->aPiece = vStartPiece;
                                    vStartPiece->aMoved = true;
                                    vStartPiece->aLastMoved = true;
                                    vStartPiece->aMovedFrom = vGame->aBoard->aCells[vStartY][vStartX];
                                    vPlayed = true;
                                }
                                else
                                {
                                    if(vStartX - vEndX > 1 || vStartX - vEndX < -1)
                                    {
                                        Serial.println("/!\\ Illegal Move /!\\");
                                        continue;
                                    }
                                    if(vStartY - vEndY > 1 || vStartY - vEndY < 1)
                                    {
                                        Serial.println("/!\\ Illegal Move /!\\");
                                        continue;
                                    }
                                    Piece* vEndPiece = vGame->aBoard->aCells[vEndY][vEndX]->aPiece;
                                    if(vEndPiece == NULL)
                                    {
                                        Serial.println("/!\\ Illegal Move /!\\");
                                        continue;
                                    }
                                    if(vEndPiece->aColor == EColors::White)
                                    {
                                        Serial.println("/!\\ Illegal Move /!\\");
                                        continue;
                                    }
                                    mCapture(vGame->aBoard->aPlayer1, vEndPiece);
                                    vGame->aBoard->aCells[vStartY][vStartX]->aPiece = NULL;
                                    vGame->aBoard->aCells[vEndY][vEndX]->aPiece = vStartPiece;
                                    vStartPiece->aMoved = true;
                                    vStartPiece->aLastMoved = true;
                                    vStartPiece->aMovedFrom = vGame->aBoard->aCells[vStartY][vStartX];
                                    vPlayed = true;
                                }
                            }break;
                        };
                    }
                }break;
                case EPlayerType::Computer:
                {
                    
                }break;
            };
            vGame->aState = EStates::WhitePlayerTurn;
        }break;
    }
    
    
    String vString = Serial.readString();
    vString.trim();


}

void mRender()
{
    Player* vPlayer1 = vGame->aBoard->aPlayer1;
    Player* vPlayer2 = vGame->aBoard->aPlayer2; 
    for(int vY = 0; vY < 8; vY++)
    {
        if(vY == 0)
        {
            for(int vIndex = 0; vIndex < 16; vIndex++)
            {
                if(vPlayer2->aJail[vIndex] != NULL)
                {
                    mPrintPiece(vPlayer2->aJail[vIndex]);
                }
            }
            Serial.println();
            Serial.println("  a b c d e f g h");
            Serial.print(" +");
            for(int vIndex = 0; vIndex < 8; vIndex++)
            {
                Serial.print("-+");
            }
            Serial.println("");
        }
        else
        {
            Serial.print(" +");
            for(int vIndex = 0; vIndex < 8; vIndex++)
            {
                Serial.print("-+");
            }
            Serial.println("");
        }
        for(int vX = 0; vX < 8; vX++)
        {
            if(vX == 0)
            {
                Serial.print((8-vY));
                Serial.print("|");
            }
            else
            {
                Serial.print("|");
            }
            mPrintCell(vGame->aBoard->aCells[vY][vX]);
        }
        Serial.println("|");
    }
    Serial.print(" +");
    for(int vIndex = 0; vIndex < 8; vIndex++)
    {
        Serial.print("-+");
    }
    Serial.println("");

    Serial.println("  a b c d e f g h ");
    
    for(int vIndex = 0; vIndex < 16; vIndex++)
    {
        if(vPlayer1->aJail[vIndex] != NULL)
        {
            mPrintPiece(vPlayer1->aJail[vIndex]);
        }
    }
    Serial.println();
}

void mBuildCell(Cell* pCell, int pX, int pY)
{
    pCell->aPiece = NULL;
    pCell->aX = pX;
    pCell->aY = pY;
    if((pCell->aX + pCell->aY) % 2 == 0)
    {
        pCell->aColor = EColors::White;
    }
    else
    {
        pCell->aColor = EColors::Black;      
    }
    pCell->aLetter = 'a' + pCell->aX;
    pCell->aDigit = '8' - pCell->aY;
}

void mPrintCell(Cell* pCell)
{
    if(pCell->aPiece != NULL)
    {
        mPrintPiece(pCell->aPiece);
    }
    else
    {
        if(pCell->aColor == EColors::White)
        {
            Serial.print(" ");
        }
        else
        {                
            Serial.print("#");
        }
    }
}

void mBuildPiece(Piece* pPiece, EColors pColor, EPieceTypes pPieceType) 
{
    pPiece->aColor = pColor;
    pPiece->aPieceType = pPieceType;
    switch (pPiece->aPieceType) 
    {
        case EPieceTypes::King:
        {
            if (pPiece->aColor == EColors::White)
            {
                pPiece->aSymbol = 'K';
            }
            else 
            {
                pPiece->aSymbol = 'k';
            }
        }break;
        case EPieceTypes::Queen:
        {
            if (pPiece->aColor == EColors::White) 
            {
                pPiece->aSymbol = 'Q';
            } 
            else 
            {
                pPiece->aSymbol = 'q';
            }
        }break;
        case EPieceTypes::Bishop:
        {
            if (pPiece->aColor == EColors::White) 
            {
                pPiece->aSymbol = 'B';
            } 
            else 
            {
                pPiece->aSymbol = 'b';
            }
        }break;
        case EPieceTypes::Knight:
        {
            if (pPiece->aColor == EColors::White) 
            {
                pPiece->aSymbol = 'N';
            } 
            else 
            {
                pPiece->aSymbol = 'n';
            }
        }break;
        case EPieceTypes::Rook:
        {
            if (pPiece->aColor == EColors::White) 
            {
                pPiece->aSymbol = 'R';
            } 
            else 
            {
                pPiece->aSymbol = 'r';
            }
        }break;
        case EPieceTypes::Pawn:
        {
            if (pPiece->aColor == EColors::White) 
            {
                pPiece->aSymbol = 'P';
            }
            else
            {
                pPiece->aSymbol = 'p';
            }
        }break;
    };
    pPiece->aMoved = false;
    pPiece->aLastMoved = false;
    pPiece->aJailed = false;
    pPiece->aMovedFrom = NULL;
}

void mPrintPiece(Piece* pPiece)
{
    Serial.print(pPiece->aSymbol);
}

void mBuildPlayer(Player* pPlayer, EPlayerType pPlayerType, EColors pColor)
{
    pPlayer->aPlayerType = pPlayerType;
    pPlayer->aColor = pColor;
    pPlayer->aPieces = (Piece**)malloc(sizeof(Piece*[16]));
    pPlayer->aPiecesCount = 0;
    pPlayer->aJail = (Piece**)malloc(sizeof(Piece*[16]));
    pPlayer->aJailCount = 0;
    for(int vIndex = 0; vIndex < 16; vIndex++)
    {
        pPlayer->aPieces[vIndex] = NULL;
        pPlayer->aJail[vIndex] = NULL;
    }
}

void mAddPiece(Player* pPlayer, Piece* pPiece)
{
    pPlayer->aPieces[pPlayer->aPiecesCount] = pPiece;
    pPlayer->aPiecesCount++;
}

void mCapture(Player* pPlayer, Piece* pPiece)
{
    pPlayer->aJail[pPlayer->aJailCount] = pPiece;
    pPiece->aJailed = true;
    pPlayer->aJailCount++;    
}