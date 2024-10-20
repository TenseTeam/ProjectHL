// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/InventorySaveData.h"
#include "Features/Generic/SaveSystem/Interfaces/Saveable.h"
#include "InventoryBase.generated.h"

class UInventoryRegistry;
class UItemBase;
class UItemDataBase;

DEFINE_LOG_CATEGORY_STATIC(LogInventorySystem, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnAnyItemAdded,
	UItemBase*, Item
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnAnyItemConsumed,
	UItemBase*, Item
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnAnyItemUsed,
	UItemBase*, Item
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnAnyItemRemoved,
	UItemBase*, Item
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnInventoryCleared
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnInventoryModified
	);

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom))
class VUNDK_API UInventoryBase : public UActorComponent, public ISaveable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory System")
	UInventoryRegistry* InventoryRegistry;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory System", meta = (ClampMin = "1", UIMin = "1"))
	int32 Capacity = 16;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory System")
	TSet<UItemBase*> Items;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnInventoryCleared OnInventoryCleared;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnInventoryModified OnInventoryModified;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnAnyItemAdded OnAnyItemAdded;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnAnyItemUsed OnAnyItemUsed;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnAnyItemConsumed OnAnyItemConsumed;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnAnyItemRemoved OnAnyItemRemoved;

public:
	UInventoryBase();

	/**
	 * \defgroup InventorySave
	 * @{
	 */
	
	virtual FSaveData CreateSaveData() const override;
	
	virtual void LoadInventorySaveData(const FInventorySaveData InventorySaveData);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	virtual FInventorySaveData CreateInventorySaveData() const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	virtual void LoadSaveData(const FSaveData& SavedData) override;
	
	/** @} */
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	UItemBase* AddNewItem(UItemDataBase* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	void AddItem(UItemBase* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	bool RemoveItemOfType(UItemDataBase* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	void RemoveItem(UItemBase* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	void ClearInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	UItemBase* Find(const UItemDataBase* ItemData) const;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	virtual bool IsEmpty() const;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	virtual bool IsFull() const;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	virtual bool CanContainItem(const UItemDataBase* ItemData) const;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	bool HasItemOfType(const UItemDataBase* ItemData) const;

	UFUNCTION(BlueprintPure, Category = "Inventory System")
	bool IsInRegistry(const UItemDataBase* ItemData) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory System")
	UItemDataBase* GetItemByID(const FName ItemID) const;

	bool Check() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System")
	UItemBase* AddNewItemInternal(UItemDataBase* ItemData);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System")
	void AddItemInternal(UItemBase* Item);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System")
	void OnItemRemoved(UItemBase* Item);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System")
	void OnClearedInventory();
};
