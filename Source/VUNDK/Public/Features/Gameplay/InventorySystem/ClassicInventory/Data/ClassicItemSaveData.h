// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/Gameplay/InventorySystem/Base/Data/ItemSaveData.h"
#include "ClassicItemSaveData.generated.h"

USTRUCT(BlueprintType)
struct VUNDK_API FClassicItemSaveData : public FItemSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory System|Item")
	int32 Quantity;
};