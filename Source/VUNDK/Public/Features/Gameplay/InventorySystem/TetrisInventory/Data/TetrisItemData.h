// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/Gameplay/InventorySystem/Base/Data/ItemDataBase.h"
#include "TetrisItemData.generated.h"

UCLASS(NotBlueprintType, Blueprintable)
class VUNDK_API UTetrisItemData : public UItemDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data", meta = (ClampMin = "1", UIMin = "1"))
	FIntPoint Size;
};
