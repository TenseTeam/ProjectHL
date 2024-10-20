// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Features/Gameplay/InventorySystem/Base/InventoryBase.h"
#include "ClassicInventory.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VUNDK_API UClassicInventory : public UInventoryBase
{
	GENERATED_BODY()

public:
	UClassicInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	virtual UItemBase* AddNewItemInternal_Implementation(UItemDataBase* ItemData) override;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	int32 GetTotalMinRequiredSlotsCount() const;

	virtual bool IsFull() const override;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	bool IsSatisfyingAllRequiredSlots() const;

	virtual bool CanContainItem(const UItemDataBase* ItemData) const override;
};
