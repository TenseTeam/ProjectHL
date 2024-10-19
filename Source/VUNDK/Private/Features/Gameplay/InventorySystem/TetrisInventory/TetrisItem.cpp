// Copyright VUNDK, Inc. All Rights Reserved.


#include "Features/Gameplay/InventorySystem/TetrisInventory/TetrisItem.h"

UTetrisItemData* UTetrisItem::GetTetrisItemData() const
{
	return Cast<UTetrisItemData>(ItemData);
}

void UTetrisItem::SetCurrentPosition(const FIntPoint NewPosition)
{
	CurrentPosition = NewPosition;
}

FIntPoint UTetrisItem::GetCurrentPosition() const
{
	return CurrentPosition;
}
