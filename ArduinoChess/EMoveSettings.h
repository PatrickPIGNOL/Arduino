#ifndef EMoveSettings_H
#define EMoveSettings_H
namespace SMoveSettings
{
    typedef enum
    {
        Nothing = 0,
        CanCapture = 1,
        MustCapture = 2,
        Repeat = 4,
        EnPassant = 8,
        FirstMove = 16,
        Castle = 32
    }EMoveSettings;
}
#endif
