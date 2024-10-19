// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TetrisSlot.h"
#include "Features/Gameplay/InventorySystem/Base/InventoryBase.h"
#include "TetrisInventory.generated.h"

class UTetrisItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnItemAddedToSlot,
	UTetrisItem*, Item,
	FIntPoint, SlotPosition
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnItemRemovedFromSlot,
	UTetrisItem*, Item,
	FIntPoint, SlotPosition
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnItemMoved,
	UTetrisItem*, Item,
	FIntPoint, OldPosition,
	FIntPoint, NewPosition
	);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VUNDK_API UTetrisInventory : public UInventoryBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnItemAddedToSlot OnItemAddedToSlot;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnItemRemovedFromSlot OnItemRemovedFromSlot;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnItemMoved OnItemMoved;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory System")
	FIntPoint GridSize;
	
private:
	TArray<TArray<UTetrisSlot*>> InvMatrix;
	
public:
	UTetrisInventory();

	virtual UItemBase* AddNewItemInternal_Implementation(UItemDataBase* ItemData) override;

	virtual void AddItemInternal_Implementation(UItemBase* Item) override;

	virtual bool IsFull() const override;

	virtual bool IsEmpty() const override; 

	virtual void OnItemRemoved_Implementation(UItemBase* Item) override;

	virtual void OnClearedInventory_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void ConstructGrid();

	UFUNCTION(BlueprintPure)
	UTetrisSlot* GetSlot(const FIntPoint SlotPosition) const;

	UFUNCTION(BlueprintPure)
	FIntPoint GetGridSize() const;

	UFUNCTION(BlueprintPure)
	bool CanOccupySlots(const UTetrisItemData* ItemData, const FIntPoint StartSlotPosition) const;

	UFUNCTION(BlueprintCallable)
	bool TryAddNewItemAtSlots(UTetrisItemData* ItemData, const FIntPoint StartSlotPosition);

	UFUNCTION(BlueprintCallable)
	bool TryAddItemAtSlots(UTetrisItem* Item, const FIntPoint StartSlotPosition);

	UFUNCTION(BlueprintCallable)
	bool TryMoveItem(UTetrisItem* Item, const FIntPoint NewPosition);
	
protected:
	virtual void BeginPlay() override;

private:
	bool IsValidSlotPosition(const FIntPoint SlotPosition) const;
	void FreeSlots(const FIntPoint StartPosition, const FIntPoint Size);
	void OccupySlotsWithItem(UTetrisItem* Item, FIntPoint StartSlotPosition);
	bool TryOccupySlotsWithItem(UTetrisItem* Item, const FIntPoint StartSlotPosition);
	bool FindSlotsForItem(const UTetrisItemData* ItemData, FIntPoint& OutStartSlotPosition) const;
};
