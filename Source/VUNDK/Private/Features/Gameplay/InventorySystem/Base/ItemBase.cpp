// Copyright VUNDK, Inc. All Rights Reserved.

#include "Features/Gameplay/InventorySystem/Base/ItemBase.h"
#include "Features/Gameplay/InventorySystem/Base/Data/ItemDataBase.h"
#include "Kismet/GameplayStatics.h"

void UItemBase::Init(UItemDataBase* Data, UInventoryBase* InventorySystem)
{
	RelatedInventory = InventorySystem;
	ItemData = Data;
	UE_LOG(LogInventorySystem, Display, TEXT("ItemBase::Init(), Item %s has been initialized in the inventory %s"), *ItemData->ItemName, *RelatedInventory->GetName());
	OnInit();
	OnItemAdded.Broadcast(); // Event when the item is added to the inventory
}

FItemSaveData UItemBase::CreateSaveData() const
{
	FItemSaveData ItemSaveData;
	return ItemSaveData;
}

void UItemBase::LoadSaveData(const FItemSaveData ItemSaveData)
{
}

UItemDataBase* UItemBase::GetItemData() const
{
	return ItemData;
}

void UItemBase::Use()
{
	UE_LOG(LogInventorySystem, Display, TEXT("ItemBase::Use(), Item %s has been used from the inventory %s"), *ItemData->ItemName, *RelatedInventory->GetName());
	
	OnItemUsed.Broadcast();
	RelatedInventory->OnAnyItemUsed.Broadcast(this);
	RelatedInventory->OnInventoryModified.Broadcast();
	OnUse();

	if (ItemData->bIsConsumable)
		Consume();
}

void UItemBase::Remove()
{
	if (RelatedInventory->RemoveItemOfType(ItemData))
	{
		// OnRemove is called in the InventoryBase -> RemoveItem
		// otherwise ONLY when calling Remove() from the ItemBase, it will trigger the OnRemove event
		UE_LOG(LogInventorySystem, Display, TEXT("ItemBase::Remove(), Item %s has been removed from the inventory %s"), *ItemData->ItemName, *RelatedInventory->GetName());
	}
}

void UItemBase::Consume()
{
	UE_LOG(LogInventorySystem, Display, TEXT("Item %s has been consumed from the inventory %s"), *ItemData->ItemName, *RelatedInventory->GetName());
	RelatedInventory->OnAnyItemConsumed.Broadcast(this);
	OnItemConsumed.Broadcast();
	OnConsume_Implementation();
}

void UItemBase::OnInit_Implementation()
{
}

void UItemBase::OnRemove_Implementation()
{
}

void UItemBase::OnUse_Implementation()
{
}

void UItemBase::OnConsume_Implementation()
{
	Remove();
}

AGameModeBase* UItemBase::GetGameMode() const
{
	return UGameplayStatics::GetGameMode(RelatedInventory);
}

APlayerController* UItemBase::GetPlayerController(const int PlayerIndex) const
{
	return UGameplayStatics::GetPlayerController(RelatedInventory, PlayerIndex);
}

APlayerState* UItemBase::GetPlayerState(const int PlayerStateIndex) const
{
	return UGameplayStatics::GetPlayerState(RelatedInventory, PlayerStateIndex);
}
