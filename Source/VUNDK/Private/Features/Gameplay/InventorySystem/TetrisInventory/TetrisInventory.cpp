// Copyright VUNDK, Inc. All Rights Reserved.

#include "Features/Gameplay/InventorySystem/TetrisInventory/TetrisInventory.h"
#include "Features/Gameplay/InventorySystem/TetrisInventory/TetrisItem.h"
#include "Features/Gameplay/InventorySystem/TetrisInventory/Data/TetrisItemData.h"
#include "Features/Gameplay/InventorySystem/Utility/ISFactory.h"

UTetrisInventory::UTetrisInventory(): GridSize()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UItemBase* UTetrisInventory::AddNewItemInternal_Implementation(UItemDataBase* ItemData)
{
	UTetrisItemData* TetrisItemData = Cast<UTetrisItemData>(ItemData);
	
	if(FIntPoint FoundSlot; FindSlotsForItem(TetrisItemData, FoundSlot)) // Find slots for the item
	{
		UTetrisItem* Item = Cast<UTetrisItem>(UISFactory::CreateItem(TetrisItemData, this)); // Create the item
		OccupySlotsWithItem(Item, FoundSlot); // Since we found the slots, occupy them with the item
		OnItemAddedToSlot.Broadcast(Item, FoundSlot);
		return Item;
	}

	return nullptr;
}

void UTetrisInventory::AddItemInternal_Implementation(UItemBase* Item)
{
	const UTetrisItemData* TetrisItemData = Cast<UTetrisItemData>(Item->GetItemData());
	UTetrisItem* TetrisItem = Cast<UTetrisItem>(Item);
	
	if(FIntPoint FoundSlot; FindSlotsForItem(TetrisItemData, FoundSlot))
	{
		OccupySlotsWithItem(TetrisItem, FoundSlot);
		OnItemAddedToSlot.Broadcast(TetrisItem, FoundSlot);
	}
}

bool UTetrisInventory::IsFull() const
{
	for (int32 x = 0; x < GridSize.X; x++)
	{
		for (int32 y = 0; y < GridSize.Y; y++)
		{
			if (!InvMatrix[x][y]->IsOccupied())
				return false;
		}
	}

	return true;
}

bool UTetrisInventory::IsEmpty() const
{
	for (int32 x = 0; x < GridSize.X; x++)
	{
		for (int32 y = 0; y < GridSize.Y; y++)
		{
			if (InvMatrix[x][y]->IsOccupied())
				return false;
		}
	}

	return true;
}

void UTetrisInventory::OnItemRemoved_Implementation(UItemBase* Item)
{
	UTetrisItem* TetrisItem = Cast<UTetrisItem>(Item);

	const int32 CurrX = TetrisItem->GetCurrentPosition().X;
	const int32 CurrY = TetrisItem->GetCurrentPosition().Y;

	FreeSlots(TetrisItem->GetCurrentPosition(), TetrisItem->GetTetrisItemData()->Size);
	OnItemRemovedFromSlot.Broadcast(TetrisItem, TetrisItem->GetCurrentPosition());
}

void UTetrisInventory::OnClearedInventory_Implementation()
{
	for (int32 x = 0; x < GridSize.X; x++)
	{
		for (int32 y = 0; y < GridSize.Y; y++)
			InvMatrix[x][y]->FreeSlot();
	}
}

void UTetrisInventory::ConstructGrid()
{
	int32 GridX = GridSize.X;
	int32 GridY = GridSize.Y;

	if (GridX + GridY >= Capacity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid has been resized to fit the capacity of the inventory."));
		const int Excess = GridX + GridY - Capacity;
		GridX -= Excess;
		GridSize = FIntPoint(GridX, GridY);
	}
	
	InvMatrix.SetNum(GridSize.X);
	for (int32 x = 0; x < GridSize.X; x++)
	{
		InvMatrix[x].SetNum(GridSize.Y);
		for (int32 y = 0; y < GridSize.Y; y++)
		{
			InvMatrix[x][y] = NewObject<UTetrisSlot>(this);
			InvMatrix[x][y]->Init(this, FIntPoint(x, y));
		}
	}
}

UTetrisSlot* UTetrisInventory::GetSlot(const FIntPoint SlotPosition) const
{
	if (!IsValidSlotPosition(SlotPosition))
		return nullptr;
	
	return InvMatrix[SlotPosition.X][SlotPosition.Y];
}

FIntPoint UTetrisInventory::GetGridSize() const
{
	return GridSize;
}

bool UTetrisInventory::CanOccupySlots(const UTetrisItemData* ItemData, const FIntPoint StartSlotPosition) const
{
	if (!IsValidSlotPosition(StartSlotPosition))
		return false;

	if (StartSlotPosition.X + ItemData->Size.X > GridSize.X || StartSlotPosition.Y + ItemData->Size.Y > GridSize.Y)
	{
		UE_LOG(LogTemp, Display, TEXT("Item size exceeds the inventory grid size."));
		return false;
	}
	
	for (int32 x = StartSlotPosition.X; x < StartSlotPosition.X + ItemData->Size.X; x++)
	{
		for (int32 y = StartSlotPosition.Y; y < StartSlotPosition.Y + ItemData->Size.Y; y++)
		{
			if (InvMatrix[x][y]->IsOccupied())
				return false;
		}
	}
	
	return true;
}

bool UTetrisInventory::TryAddNewItemAtSlots(UTetrisItemData* ItemData, const FIntPoint StartSlotPosition)
{
	if (ItemData == nullptr || !CanContainItem(ItemData))
		return false;

	UTetrisItem* Item = Cast<UTetrisItem>(UISFactory::CreateItem(ItemData, this));
	
	if (TryOccupySlotsWithItem(Item, StartSlotPosition))
	{
		OnItemAddedToSlot.Broadcast(Item, StartSlotPosition);
		return true;
	}

	return false;
}

bool UTetrisInventory::TryAddItemAtSlots(UTetrisItem* Item, const FIntPoint StartSlotPosition)
{
	if (Item == nullptr || !CanContainItem(Item->GetItemData()))
		return false;
	
	if (TryOccupySlotsWithItem(Item, StartSlotPosition))
	{
		OnItemAddedToSlot.Broadcast(Item, StartSlotPosition);
		return true;
	}

	return false;
}

bool UTetrisInventory::TryMoveItem(UTetrisItem* Item, const FIntPoint NewPosition)
{
	if (!Find(Item->GetItemData()) || !IsValidSlotPosition(NewPosition))
		return false;

	const FIntPoint OldPosition = Item->GetCurrentPosition();
	FreeSlots(Item->GetCurrentPosition(), Item->GetTetrisItemData()->Size);

	if (!TryOccupySlotsWithItem(Item, NewPosition)) // Try to occupy the new slots
	{
		TryOccupySlotsWithItem(Item, Item->GetCurrentPosition()); // Re-occupy the old slots
		return false;
	}

	OnItemMoved.Broadcast(Item, OldPosition, NewPosition);
	return true;
}

void UTetrisInventory::BeginPlay()
{
	Super::BeginPlay();
	ConstructGrid();
}

void UTetrisInventory::FreeSlots(const FIntPoint StartPosition, const FIntPoint Size)
{
	for (int32 x = StartPosition.X; x < StartPosition.X + Size.X; x++)
	{
		for (int32 y = StartPosition.Y; y < StartPosition.Y + Size.Y; y++)
			InvMatrix[x][y]->FreeSlot();
	}
}

bool UTetrisInventory::IsValidSlotPosition(const FIntPoint SlotPosition) const
{
	return InvMatrix.IsValidIndex(SlotPosition.X) && InvMatrix[SlotPosition.X].IsValidIndex(SlotPosition.Y);
}

void UTetrisInventory::OccupySlotsWithItem(UTetrisItem* Item, const FIntPoint StartSlotPosition)
{
	const UTetrisItemData* ItemData = Item->GetTetrisItemData();
	
	for (int32 x = StartSlotPosition.X; x < StartSlotPosition.X + ItemData->Size.X; x++)
	{
		for (int32 y = StartSlotPosition.Y; y < StartSlotPosition.Y + ItemData->Size.Y; y++)
			InvMatrix[x][y]->OccupySlot(Item);
	}

	Item->SetCurrentPosition(StartSlotPosition);
	Items.Add(Item);
}

bool UTetrisInventory::TryOccupySlotsWithItem(UTetrisItem* Item, const FIntPoint StartSlotPosition)
{
	const UTetrisItemData* ItemData = Item->GetTetrisItemData();

	if (!CanOccupySlots(ItemData, StartSlotPosition))
		return false;
	
	OccupySlotsWithItem(Item, StartSlotPosition);
	return true;
}

bool UTetrisInventory::FindSlotsForItem(const UTetrisItemData* ItemData, FIntPoint& OutStartSlotPosition) const
{
	const FIntPoint ItemSize = ItemData->Size;
	
	for (int32 x = 0; x <= GridSize.X - ItemSize.X; x++)
	{
		for (int32 y = 0; y <= GridSize.Y - ItemSize.Y; y++)
		{
			if (CanOccupySlots(ItemData, FIntPoint(x, y)))
			{
				OutStartSlotPosition = FIntPoint(x, y);
				return true;
			}
		}
	}

	return false;
}
