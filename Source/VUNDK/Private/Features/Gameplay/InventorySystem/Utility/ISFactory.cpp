// Copyright VUNDK, Inc. All Rights Reserved.

#include "Features/Gameplay/InventorySystem/Utility/ISFactory.h"
#include "Features/Gameplay/InventorySystem/Base/ItemBase.h"
#include "Features/Gameplay/InventorySystem/Base/Data/ItemDataBase.h"

UItemBase* UISFactory::CreateItem(UItemDataBase* Data, UInventoryBase* Inventory)
{
	UItemBase* Item = NewObject<UItemBase>(GetTransientPackage(), Data->ItemClass);
	Item->Init(Data, Inventory);
	return Item;
}
