// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ClassicItemData.h"
#include "Features/Gameplay/InventorySystem/Base/ItemBase.h"
#include "UObject/Object.h"
#include "ClassicItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnItemIncreased,
	int32, CurrentQuantity
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnItemDecreased,
	int32, CurrentQuantity
);

UCLASS(Blueprintable, BlueprintType)
class VUNDK_API UClassicItem : public UItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory System|Item")
	FOnItemIncreased OnItemIncreased;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System|Item")
	FOnItemDecreased OnItemDecreased;

private:
	int32 CurrentQuantity;
	UPROPERTY()
	UClassicItemData* ClassicItemData;

public:
	void OnInit_Implementation() override;

	virtual FItemSaveData CreateSaveData() const override;

	virtual void LoadSaveData(const FItemSaveData ItemSaveData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	TArray<FClassicItemSlotData> GetRequiredSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	int32 GetMinRequiredSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	int32 GetMaxStackSize() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	int32 GetCurrentQuantity() const;
	
	void IncreaseQuantity();

	void DecreaseQuantity();

protected:
	virtual void OnConsume_Implementation() override;
};
