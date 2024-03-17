#ifndef EStates_H
#define EStates_H
namespace SStates
{
    typedef enum
    {
        ChooseMode = 0,
        ChooseDifficulty,
        InitBoard,
        StartPlaying,
        WhitePlayerTurn,
        BlackPlayerTurn,
        EndGame
    }EStates;
}
#endif
