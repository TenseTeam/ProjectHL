// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryBase.h"
#include "Data/ItemSaveData.h"
#include "UObject/Object.h"
#include "ItemBase.generated.h"

class UClassicInventory;
class UItemDataBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnItemAdded
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnItemUsed
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnItemConsumed
	);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnItemRemoved
	);

UCLASS(Abstract, Blueprintable, BlueprintType)
class VUNDK_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory System|Item")
	FOnItemAdded OnItemAdded;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System|Item")
	FOnItemUsed OnItemUsed;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System|Item")
	FOnItemConsumed OnItemConsumed;
	UPROPERTY(BlueprintAssignable, Category = "Inventory System|Item")
	FOnItemRemoved OnItemRemoved;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory System|Item")
	UItemDataBase* ItemData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory System|Item")
	UInventoryBase* RelatedInventory;

public:
	void Init(UItemDataBase* Data, UInventoryBase* InventorySystem);

	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	virtual FItemSaveData CreateSaveData() const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	virtual void LoadSaveData(const FItemSaveData ItemSaveData);
	
	UFUNCTION(BlueprintPure, Category = "Inventory System|Item")
	UItemDataBase* GetItemData() const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	void Use();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	void Remove();

	UFUNCTION(BlueprintCallable, Category = "Inventory System|Item")
	void Consume();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System|Item")
	void OnRemove();
	
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System|Item")
	void OnInit();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System|Item")
	void OnUse();

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory System|Item")
	void OnConsume();
	
	UFUNCTION(BlueprintPure, Category = "Inventory System|Item")
	AGameModeBase* GetGameMode() const;

	UFUNCTION(BlueprintPure, Category = "Inventory System|Item")
	APlayerController* GetPlayerController(const int PlayerIndex) const;

	UFUNCTION(BlueprintPure, Category = "Inventory System|Item")
	APlayerState* GetPlayerState(const int PlayerStateIndex) const;
};
