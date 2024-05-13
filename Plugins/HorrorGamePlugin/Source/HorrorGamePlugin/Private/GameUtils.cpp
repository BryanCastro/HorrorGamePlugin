#include "GameUtils.h"
#include "Engine/Engine.h"

void GameUtils::LogMessage(const FString& Message,  FColor Color, float Time, int32 Key)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(Key, Time, Color, Message);
    }
    UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
}

// Overloaded function to include a key for the message, with optional time and color
void GameUtils::LogMessage(const FString& Message, FColor Color, float Time) {
    LogMessage(Message, Color, Time, -1);
}

// Overloaded function that defaults color and time but uses a key
void GameUtils::LogMessage(const FString& Message, FColor Color, int Key) {
    LogMessage(Message, Color, 5.0f, Key);
}
