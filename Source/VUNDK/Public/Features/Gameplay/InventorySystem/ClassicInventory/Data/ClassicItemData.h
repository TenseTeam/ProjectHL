// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/Gameplay/InventorySystem/Base/Data/ItemDataBase.h"
#include "UObject/Object.h"
#include "ClassicItemData.generated.h"

UCLASS(NotBlueprintable, BlueprintType)
class VUNDK_API UClassicItemData : public UItemDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data", meta=(ClampMin="1", UIMin="1"))
	int32 MaxStackSize = 1;
};
