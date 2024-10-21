// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Features/Generic/SaveSystem/Data/Structs/SaveData.h"
#include "UObject/Object.h"
#include "Saveable.generated.h"

UINTERFACE(BlueprintType)
class VUNDK_API USaveable : public UInterface
{
	GENERATED_BODY()

	
};

class ISaveable
{
	GENERATED_BODY()

public:
	virtual FSaveData CreateSaveData() const = 0;
    
	virtual void LoadSaveData(const FSaveData& SavedData) = 0;
};
