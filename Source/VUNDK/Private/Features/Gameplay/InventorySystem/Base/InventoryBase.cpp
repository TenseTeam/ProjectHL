// Copyright VUNDK, Inc. All Rights Reserved.

#include "Features/Gameplay/InventorySystem/Base/InventoryBase.h"
#include "Features/Gameplay/InventorySystem/Base/ItemBase.h"
#include "Features/Gameplay/InventorySystem/Base/Data/InventoryRegistry.h"
#include "Features/Gameplay/InventorySystem/Base/Data/InventorySaveData.h"
#include "Features/Gameplay/InventorySystem/Base/Data/ItemSaveData.h"
#include "Features/Gameplay/InventorySystem/Utility/ISFactory.h"

UInventoryBase::UInventoryBase(): InventoryRegistry(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

FSaveData UInventoryBase::CreateSaveData() const
{
	FInventorySaveData InventorySaveData;

	for (const UItemBase* Item : Items)
	{
		FItemSaveData ItemSaveData = Item->CreateSaveData();
		FName ItemID = Item->GetItemData()->GetItemID();
		InventorySaveData.SavedItems.Add(ItemID, ItemSaveData);
	}

	return static_cast<FSaveData>(InventorySaveData);
}

FInventorySaveData UInventoryBase::CreateInventorySaveData() const
{
	return static_cast<FInventorySaveData>(CreateSaveData());
}

void UInventoryBase::LoadSaveData(const FSaveData& SavedData)
{
	if (const FInventorySaveData* InventorySaveData = static_cast<const FInventorySaveData*>(&SavedData))
		LoadInventorySaveData(*InventorySaveData);
	else
		UE_LOG(LogInventorySystem, Error, TEXT("Invalid Save Data type for inventory %s"), *GetName());
}

void UInventoryBase::LoadInventorySaveData(const FInventorySaveData InventorySaveData)
{
	for (const TPair<FName, FItemSaveData>& LoadedItem : InventorySaveData.SavedItems)
	{
		const FName ItemID = LoadedItem.Key;
		const FItemSaveData ItemSaveData = LoadedItem.Value;

		if (UItemDataBase* ItemData = GetItemByID(ItemID))
		{
			UItemBase* CreatedItem = UISFactory::CreateItem(ItemData, this);
			CreatedItem->LoadSaveData(ItemSaveData);
			Items.Add(CreatedItem);
		}
		else
		{
			UE_LOG(LogInventorySystem, Warning, TEXT("Item with ID %s not found in the inventory registry %s"),
			       *ItemID.ToString(), *GetName());
		}
	}
}

UItemBase* UInventoryBase::AddNewItem(UItemDataBase* ItemData)
{
	if (ItemData == nullptr) return nullptr;
	if (!CanContainItem(ItemData)) return nullptr;

	UE_LOG(LogInventorySystem, Display, TEXT("Adding Item %s to inventory %s"), *ItemData->ItemName, *GetName())
	UItemBase* NewItem = AddNewItemInternal(ItemData);

	if (NewItem == nullptr)
	{
		UE_LOG(LogInventorySystem, Error, TEXT("Failed to add Item %s to inventory %s"), *ItemData->ItemName, *GetName());
		return nullptr;
	}
	
	OnAnyItemAdded.Broadcast(NewItem);
	OnInventoryModified.Broadcast();
	return NewItem;
}

void UInventoryBase::AddItem(UItemBase* Item)
{
	if (Item == nullptr) return;
	if (!CanContainItem(Item->GetItemData())) return;

	Items.Add(Item);
	AddItemInternal(Item);
	OnAnyItemAdded.Broadcast(Item);
	OnInventoryModified.Broadcast();
}

void UInventoryBase::AddItemInternal_Implementation(UItemBase* Item)
{
}

UItemBase* UInventoryBase::AddNewItemInternal_Implementation(UItemDataBase* ItemData)
{
	UItemBase* NewItem = UISFactory::CreateItem(ItemData, this);
	Items.Add(NewItem);
	return NewItem;
}

bool UInventoryBase::RemoveItemOfType(UItemDataBase* ItemData)
{
	if (UItemBase* FoundItem = Find(ItemData))
	{
		RemoveItem(FoundItem);
		return true;
	}

	return false;
}

void UInventoryBase::RemoveItem(UItemBase* Item)
{
	if (Item == nullptr || !Items.Contains(Item))
		return;
	
	OnItemRemoved_Implementation(Item);
	Item->OnRemove();
	Item->OnItemRemoved.Broadcast();
	OnAnyItemRemoved.Broadcast(Item);
	OnInventoryModified.Broadcast();
	Items.Remove(Item);
}

void UInventoryBase::OnItemRemoved_Implementation(UItemBase* Item)
{
}

void UInventoryBase::ClearInventory()
{
	Items.Empty();
	OnClearedInventory();
	OnInventoryModified.Broadcast();
	OnInventoryCleared.Broadcast();
}

UItemBase* UInventoryBase::Find(const UItemDataBase* ItemData) const
{
	for (UItemBase* Item : Items)
	{
		if (Item->GetItemData()->GetItemID() == ItemData->GetItemID())
			return Item;
	}

	return nullptr;
}

bool UInventoryBase::IsEmpty() const
{
	return Items.IsEmpty();
}

bool UInventoryBase::IsFull() const
{
	return Items.Num() >= Capacity;
}

bool UInventoryBase::CanContainItem(const UItemDataBase* ItemData) const
{
	if (!IsInRegistry(ItemData))
	{
		UE_LOG(LogInventorySystem, Warning, TEXT("Cannot add Item, %s is not registered in the inventory registry %s"),
		       *ItemData->ItemName, *GetName());
		return false;
	}

	if (IsFull())
	{
		UE_LOG(LogInventorySystem, Warning, TEXT("Cannot add Item, inventory %s is full."), *GetName());
		return false;
	}

	return true;
}

bool UInventoryBase::HasItemOfType(const UItemDataBase* ItemData) const
{
	for (const UItemBase* Item : Items)
	{
		if (Item->GetItemData()->GetItemID() == ItemData->GetItemID())
			return true;
	}

	return false;
}

bool UInventoryBase::IsInRegistry(const UItemDataBase* ItemData) const
{
	if (!Check()) return false;
	return InventoryRegistry->RegisteredItems.Contains(ItemData);
}

UItemDataBase* UInventoryBase::GetItemByID(const FName ItemID) const
{
	if (!Check()) return nullptr;

	for (UItemDataBase* ItemData : InventoryRegistry->RegisteredItems)
	{
		if (ItemData == nullptr)
		{
			UE_LOG(LogInventorySystem, Warning, TEXT("An ItemData in the inventory registry %s is null."), *GetName());
			continue;
		}

		if (ItemData->GetItemID() == ItemID)
			return ItemData;
	}

	return nullptr;
}

bool UInventoryBase::Check() const
{
	if (InventoryRegistry == nullptr)
	{
		UE_LOG(LogInventorySystem, Error, TEXT("Inventory Registry is not set for inventory %s"), *GetName());
		return false;
	}

	return true;
}

void UInventoryBase::BeginPlay()
{
	Super::BeginPlay();
	Check();
}

void UInventoryBase::OnClearedInventory_Implementation()
{
}
