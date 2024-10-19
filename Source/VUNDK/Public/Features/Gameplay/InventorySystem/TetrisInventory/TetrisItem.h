// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/TetrisItemData.h"
#include "Features/Gameplay/InventorySystem/Base/ItemBase.h"
#include "TetrisItem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class VUNDK_API UTetrisItem : public UItemBase
{
	GENERATED_BODY()

private:
	// Current position of the item's top-left corner in the inventory grid
	FIntPoint CurrentPosition;
	
public:
	UFUNCTION(BlueprintPure)
	UTetrisItemData* GetTetrisItemData() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentPosition(const FIntPoint NewPosition);

	UFUNCTION(BlueprintPure)
	FIntPoint GetCurrentPosition() const;
};
