// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemSaveData.h"
#include "Features/Generic/SaveSystem/Data/Structs/SaveData.h"
#include "InventorySaveData.generated.h"

USTRUCT(BlueprintType)
struct FInventorySaveData : public FSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FItemSaveData> SavedItems;
};
