#pragma once

#include "CoreMinimal.h"

class GameUtils
{
public:
    // Logs a message with time, color, and an optional key (default -1, which means no specific key)
    static void LogMessage(const FString& Message, FColor Color = FColor::Red, float Time = 5.0f,  int32 Key = -1);

    // Overloaded function to include a key for the message, with optional time and color
    static void LogMessage(const FString& Message, FColor Color, float Time);

    // Overloaded function that defaults color and time but uses a key
    static void LogMessage(const FString& Message, FColor Color, int key);


};