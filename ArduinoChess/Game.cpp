/*

#include "Game.h"

void mBuildGame(Game* pGame)
{
    pGame->aCells = malloc(sizeof(Cell**[8]));
    for(int vY = 0; vY < 8; vY++)
    {
        pGame->aCell[vY] = malloc(sizeof(Cell*[8]));
        for(int vX = 0; vX < 8; vX++)
        {
            pGame->aCell[vY][vX] = malloc(sizeof(Cell));
            mBuildCell( pGame->aCells[vY][vX], vX, vY);
        }
    }
    pGame->aState = EStates::ChooseMode;
    pGame->aGameMode = EGameModes::None;
}

void mDestroyGame(Game* pGame)
{
    for(int vY = 0; vY < 8; vY++)
    {
        for(int vX = 0; vX < 8; vX++)
        {
            free(pGame->aCells[vY][vX]);
        }
        free(pGame->aCells[vY]);
    }
    free(pGame->aCells);
}

void mGameUpdate(Game* pGame)
{
    Serial.print("State : ");
    Serial.println(pGame->aState);
    switch(pGame->aState)
    {
        case EStates::ChooseMode :
        {
            pGame->aGameMode = EGameModes::None;
            if (Serial )
            {

                Serial.println("Choose a mode :");
                Serial.println("1 - Human vs Human");
                Serial.println("2 - Human vs Computer");
                Serial.println("3 - Computer vs Human");
                Serial.println("4 - Computer vs Computer");
                pGame->aIncomingByte = 0;
                while(pGame->aIncomingByte < '1' || pGame->aIncomingByte > '4')
                {
                    if(Serial.available())
                    {
                        pGame->aIncomingByte = Serial.read();
                        Serial.flush();
                    }
                }
                Serial.print("Choosen mode : ");
                switch(pGame->aIncomingByte)
                {
                    case '1': 
                    {
                        pGame->aGameMode = EGameModes::HumanVsHuman;
                        Serial.println("Human vs Human");
                        pGame->aState = EStates::ChooseDifficulty;
                    }break;
                    case '2':
                    {
                        pGame->aGameMode = EGameModes::HumanVsComputer;
                        Serial.println("Human vs Computer");
                        pGame->aState = EStates::ChooseDifficulty;
                    }break;
                    case '3':
                    {
                        pGame->aGameMode = EGameModes::ComputerVsHuman;
                        Serial.println("Computer vs Human");
                        pGame->aState = EStates::ChooseDifficulty;
                    }break;
                    case '4':
                    {
                        pGame->aGameMode = EGameModes::ComputerVsComputer;
                        Serial.println("Computer vs Computer");
                        pGame->aState = EStates::ChooseDifficulty;
                    }break;
                    default:
                    {
                        pGame->aIncomingByte = 0;
                        Serial.println("Error.");
                    }break;
                };
            }
        }break;
        case EStates::ChooseDifficulty:
        {            
            Serial.println("ChooseDifficulty...");
            if(pGame->aGameMode == EGameModes::HumanVsHuman)
            {
                pGame->aState = EStates::InitBoard;
            }
            else
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
                pGame->aIncomingByte = 0;            
                while(pGame->aIncomingByte < '0' || pGame->aIncomingByte > '9')
                {
                    pGame->aIncomingByte = 0;
                    if(Serial.available())
                    {
                        pGame->aIncomingByte = Serial.read();
                        Serial.flush();
                    }
                }
                Serial.print("Choosen difficuty : ");
                switch(pGame->aIncomingByte)
                {
                    case '0':
                    {
                        pGame->aDifficulty = 0;
                        pGame->aDepht = 0;
                        Serial.println("Idiot");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    case '1':
                    {
                        pGame->aDifficulty = 10;
                        pGame->aDepht = 1;
                        Serial.println("Basic");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    case '2':
                    {
                        pGame->aDifficulty = 20;
                        pGame->aDepht = 2;
                        Serial.println("Childish");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    case '3':
                    {
                        pGame->aDifficulty = 30;
                        pGame->aDepht = 3;
                        Serial.println("Practice");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    case '4':
                    {
                        pGame->aDifficulty = 40;
                        pGame->aDepht = 4;
                        Serial.println("Knowledge");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    case '5':
                    {
                        pGame->aDifficulty = 50;
                        pGame->aDepht = 5;
                        Serial.println("Average");                
                        pGame->aState = EStates::InitBoard;
                    }break;                    
                    case '6':
                    {
                        pGame->aDifficulty = 60;                        
                        pGame->aDepht = 6;
                        Serial.println("Good");                
                        pGame->aState = EStates::InitBoard;
                    }break;                    
                    case '7':
                    {
                        pGame->aDifficulty = 70;                        
                        pGame->aDepht = 7;
                        Serial.println("Great");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    case '8':
                    {
                        pGame->aDifficulty = 80;                        
                        pGame->aDepht = 8;
                        Serial.println("Grand Master");                
                        pGame->aState = EStates::InitBoard;
                    }break;                    
                    case '9':
                    {
                        pGame->aDifficulty = 100;       
                        pGame->aDepht = 10;
                        Serial.println("God");                
                        pGame->aState = EStates::InitBoard;
                    }break;
                    default:
                    {
                        pGame->aIncomingByte = 0;
                        Serial.println("Error.");
                    }break;
                };
            }
        }break;
        case EStates::InitBoard:
        {
            Serial.println("InitBoard...");
            if(pGame->aBoard != NULL)
            {
                Serial.print("Deleting old game... ");
                free(pGame->aBoard);
                Serial.print("Done !");
            }
            
            Serial.println("Creating game...");
            switch(pGame->aGameMode)
            {
                case EGameModes::HumanVsHuman:
                {
                    Serial.println("Creating game Human vs Human... ");
                    Serial.println("Creating Board... ");                    
                    pGame->aBoard = malloc(sizeof(Board));
                    Serial.print("Creating Player1... ");
                    pGame->aBoard->aPlayer1 = malloc(sizeof(Player));
                    Serial.println("Done !");
                    Serial.print("Creating Player2... ");
                    pGame->aBoard->aPlayer2 = malloc(sizeof(Player));
                    Serial.println("Done !");
                    Serial.println("Done !");
                    Serial.println("Done !");
                }break;
                case EGameModes::HumanVsComputer:
                {
                    Serial.print("Creating game Human vs Computer... ");
                    //pGame->aBoard = new Board(new Player(EColors::White, EPlayerType::Human), new Player(EColors::Black, EPlayerType::Computer));
                    Serial.println("Done !");
                }break;
                case EGameModes::ComputerVsHuman:
                {
                    Serial.print("Creating game Computer vs Human... ");
                    //pGame->aBoard = new Board(new Player(EColors::White, EPlayerType::Computer), new Player(EColors::Black, EPlayerType::Human));
                    Serial.println("Done !");
                }break;
                case EGameModes::ComputerVsComputer:
                {                    
                    Serial.print("Creating game Computer vs Computer... ");
                    //pGame->aBoard = new Board(new Player(EColors::White, EPlayerType::Computer), new Player(EColors::Black, EPlayerType::Computer));
                    Serial.println("Done !");
                }break;
            };            
            Serial.println("Printing board:");
            pGame->aBoard->mPrint();
            
            Serial.println("changing state...");
            pGame->aState = EStates::StartPlaying;
            pGame->aIncomingByte = 0;            
            while(pGame->aIncomingByte < '0' || pGame->aIncomingByte > '9')
            {
                pGame->aIncomingByte = 0;
                if(Serial.available())
                {
                    pGame->aIncomingByte = Serial.read();
                    Serial.flush();
                }
            }
        }break;
        case EStates::StartPlaying:
        {
            Serial.println("StartPlaying...");
            pGame->aBoard->mPrint();
            pGame->aState = EStates::StartPlaying;
            pGame->aIncomingByte = 0;            
            while(pGame->aIncomingByte < '0' || pGame->aIncomingByte > '9')
            {
                pGame->aIncomingByte = 0;
                if(Serial.available())
                {
                    pGame->aIncomingByte = Serial.read();
                    Serial.flush();
                }
            }
        }break;
        default:
        {
            Serial.println("default...");
        }break;
    };
}

void mGameRender()
{
    switch pGame->aState)
    {
        case EStates::ChooseMode :
        {

        }break;
    };
}
*/