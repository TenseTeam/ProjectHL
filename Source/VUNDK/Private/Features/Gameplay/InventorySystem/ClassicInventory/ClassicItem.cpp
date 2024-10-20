// Fill out your copyright notice in the Description page of Project Settings.

#include "Features/Gameplay/InventorySystem/ClassicInventory/ClassicItem.h"

#include "Features/Gameplay/InventorySystem/ClassicInventory/Data/ClassicItemData.h"
#include "Features/Gameplay/InventorySystem/ClassicInventory/Data/ClassicItemSaveData.h"
#include "Features/Gameplay/InventorySystem/ClassicInventory/Data/ClassicItemSlotData.h"
#include "Kismet/GameplayStatics.h"

void UClassicItem::OnInit_Implementation()
{
	Super::OnInit_Implementation();
	ClassicItemData = Cast<UClassicItemData>(ItemData);
	CurrentQuantity = 1;
}

FItemSaveData UClassicItem::CreateSaveData() const
{
	FClassicItemSaveData ItemSaveData;
	ItemSaveData.Quantity = CurrentQuantity;
	return static_cast<FItemSaveData>(ItemSaveData);
}

void UClassicItem::LoadSaveData(const FItemSaveData ItemSaveData)
{
	const FClassicItemSaveData ClassicItemSaveData = static_cast<FClassicItemSaveData>(ItemSaveData);
	CurrentQuantity = ClassicItemSaveData.Quantity;
}

TArray<FClassicItemSlotData> UClassicItem::GetRequiredSlots() const
{
	const int32 ItemMaxStack = GetMaxStackSize();
	const int32 NeededSlots = GetMinRequiredSlots();

	TArray<FClassicItemSlotData> Slots;
	for (int32 i = 0; i < NeededSlots; i++)
	{
		FClassicItemSlotData Slot;
		Slot.StackSize = ItemMaxStack;
		Slot.SlotQuantity = FMath::Min(CurrentQuantity - (i * ItemMaxStack), ItemMaxStack);
		Slots.Add(Slot);
	}

	return Slots;
}

int32 UClassicItem::GetMinRequiredSlots() const
{
	const int32 ItemMaxStack = GetMaxStackSize();
	int32 NeededSlotsCount = CurrentQuantity / ItemMaxStack;
	if (CurrentQuantity % ItemMaxStack > 0) NeededSlotsCount++;

	return NeededSlotsCount;
}

int32 UClassicItem::GetMaxStackSize() const
{
	return ClassicItemData->MaxStackSize;
}

int32 UClassicItem::GetCurrentQuantity() const
{
	return CurrentQuantity;
}

void UClassicItem::IncreaseQuantity()
{
	CurrentQuantity++;
	OnItemIncreased.Broadcast(CurrentQuantity);
}

void UClassicItem::DecreaseQuantity()
{
	if (CurrentQuantity - 1 > 0)
		CurrentQuantity--;
	else
		CurrentQuantity = 0;

	OnItemDecreased.Broadcast(CurrentQuantity);
}

void UClassicItem::OnConsume_Implementation()
{
	DecreaseQuantity();

	if (CurrentQuantity <= 0)
		Remove();
}
