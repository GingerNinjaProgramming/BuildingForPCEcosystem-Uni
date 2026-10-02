// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ControllerHardwareLibrary.generated.h"

UENUM(BlueprintType)
enum class EMyControllerType : uint8
{
    Unknown,
    Xbox,
    PlayStation4,
    PlayStation5,
    Switch
};

UCLASS()
class PCECOSYSTEM_API UControllerHardwareLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

    public:

        UFUNCTION(BlueprintCallable, Category = "Controller")
        static EMyControllerType GetControllerType(int32 PlayerIndex);

        UFUNCTION(BlueprintCallable, Category = "Controller")
        static FString GetControllerVIDPID(int32 PlayerIndex);
	
};
