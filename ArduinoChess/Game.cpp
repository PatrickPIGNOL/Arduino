#include "Game.h"
#include "Board.h"
Game* NewGame()
{
  Game* vThis = (Game*)malloc(sizeof(Game));
  vThis->aBoard = NULL;
  return vThis;
}

void FreeGame(Game* pThis)
{
  FreeBoard(pThis->aBoard);
  free(pThis);
}

void mGameUpdate(Game* pGame)
{
    Serial.print("State : ");
    Serial.println(pGame->aState);
    switch(pGame->aState)
    {
        case SStates::EStates::ChooseMode :
        {
            pGame->aGameMode = SGameModes::EGameModes::None;
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
                        pGame->aGameMode = SGameModes::EGameModes::HumanVsHuman;
                        Serial.println("Human vs Human");
                        pGame->aState = SStates::EStates::ChooseDifficulty;
                    }break;
                    case '2':
                    {
                        pGame->aGameMode = SGameModes::EGameModes::HumanVsComputer;
                        Serial.println("Human vs Computer");
                        pGame->aState = SStates::EStates::ChooseDifficulty;
                    }break;
                    case '3':
                    {
                        pGame->aGameMode = SGameModes::EGameModes::ComputerVsHuman;
                        Serial.println("Computer vs Human");
                        pGame->aState = SStates::EStates::ChooseDifficulty;
                    }break;
                    case '4':
                    {
                        pGame->aGameMode = SGameModes::EGameModes::ComputerVsComputer;
                        Serial.println("Computer vs Computer");
                        pGame->aState = SStates::EStates::ChooseDifficulty;
                    }break;
                    default:
                    {
                        pGame->aIncomingByte = 0;
                        Serial.println("Error.");
                    }break;
                };
            }
        }break;
        case SStates::EStates::ChooseDifficulty:
        {            
            Serial.println("ChooseDifficulty...");
            if(pGame->aGameMode == SGameModes::EGameModes::HumanVsHuman)
            {
                pGame->aState = SStates::EStates::InitBoard;
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
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    case '1':
                    {
                        pGame->aDifficulty = 10;
                        pGame->aDepht = 1;
                        Serial.println("Basic");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    case '2':
                    {
                        pGame->aDifficulty = 20;
                        pGame->aDepht = 2;
                        Serial.println("Childish");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    case '3':
                    {
                        pGame->aDifficulty = 30;
                        pGame->aDepht = 3;
                        Serial.println("Practice");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    case '4':
                    {
                        pGame->aDifficulty = 40;
                        pGame->aDepht = 4;
                        Serial.println("Knowledge");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    case '5':
                    {
                        pGame->aDifficulty = 50;
                        pGame->aDepht = 5;
                        Serial.println("Average");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;                    
                    case '6':
                    {
                        pGame->aDifficulty = 60;                        
                        pGame->aDepht = 6;
                        Serial.println("Good");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;                    
                    case '7':
                    {
                        pGame->aDifficulty = 70;                        
                        pGame->aDepht = 7;
                        Serial.println("Great");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    case '8':
                    {
                        pGame->aDifficulty = 80;                        
                        pGame->aDepht = 8;
                        Serial.println("Grand Master");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;                    
                    case '9':
                    {
                        pGame->aDifficulty = 100;       
                        pGame->aDepht = 10;
                        Serial.println("God");                
                        pGame->aState = SStates::EStates::InitBoard;
                    }break;
                    default:
                    {
                        pGame->aIncomingByte = 0;
                        Serial.println("Error.");
                    }break;
                };
            }
        }break;
        case SStates::EStates::InitBoard:
        {
            Serial.println("InitBoard...");
            if(pGame->aBoard != NULL)
            {
                Serial.print("Deleting old game... ");
                if(pGame->aBoard != NULL)
                {
                  FreeGame(pGame->aBoard);
                }
                Serial.println("Done !");
            }
            
            Serial.println("Creating game...");
            switch(pGame->aGameMode)
            {
                case SGameModes::EGameModes::HumanVsHuman:
                {
                    Serial.println("Creating game Human vs Human... ");
                    Serial.println("Creating Board... ");                    
                    pGame->aBoard = NewBoard();
                    Serial.print("Creating Player1... ");
                    pGame->aBoard->aPlayer1 = NewPlayer(pGame->aBoard, SColors::EColors::White, EPlayerType::Human);
                    Serial.println("Done !");
                    Serial.print("Creating Player2... ");
                    pGame->aBoard->aPlayer2 = NewPlayer(pGame->aBoard, SColors::EColors::Black, EPlayerType::Human);
                    Serial.println("Done !");
                    Serial.println("Done !");
                }break;
                case SGameModes::EGameModes::HumanVsComputer:
                {
                    Serial.print("Creating game Human vs Computer... ");
                    //pGame->aBoard = new Board(new Player(EColors::White, EPlayerType::Human), new Player(EColors::Black, EPlayerType::Computer));
                    Serial.println("Done !");
                }break;
                case SGameModes::EGameModes::ComputerVsHuman:
                {
                    Serial.print("Creating game Computer vs Human... ");
                    //pGame->aBoard = new Board(new Player(EColors::White, EPlayerType::Computer), new Player(EColors::Black, EPlayerType::Human));
                    Serial.println("Done !");
                }break;
                case SGameModes::EGameModes::ComputerVsComputer:
                {                    
                    Serial.print("Creating game Computer vs Computer... ");
                    //pGame->aBoard = new Board(new Player(EColors::White, EPlayerType::Computer), new Player(EColors::Black, EPlayerType::Computer));
                    Serial.println("Done !");
                }break;
            };            
            Serial.println("Done !");
            Serial.println("Printing board:");
            mBoardPrint(pGame->aBoard);
            
            Serial.println("changing state...");
            pGame->aState = SStates::EStates::StartPlaying;
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
        case SStates::EStates::StartPlaying:
        {
            Serial.println("StartPlaying...");
            mBoardPrint(pGame->aBoard);
            pGame->aState = SStates::EStates::StartPlaying;
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

void mGameRender(Game* pGame)
{
    switch (pGame->aState)
    {
        case SStates::EStates::ChooseMode :
        {

        }break;
    };
}
