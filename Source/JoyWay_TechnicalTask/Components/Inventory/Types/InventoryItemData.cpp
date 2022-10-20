#include "InventoryItemData.h"

// UInventoryItemData
UInventoryItemData::UInventoryItemData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FPrimaryAssetId UInventoryItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(InventoryItemsType, *(TEXT("Item_") + FString::FromInt(Id)));
}

bool UInventoryItemData::Consume_Implementation(AActor* Consumer)
{
	return false;
}

// FPrimaryInventoryItemId
FPrimaryInventoryItemId::FPrimaryInventoryItemId() : Super()
{
}

FPrimaryInventoryItemId::FPrimaryInventoryItemId(const FPrimaryAssetId& InId) : Super(InId.PrimaryAssetType, InId.PrimaryAssetName)
{
}

FPrimaryInventoryItemId::FPrimaryInventoryItemId(const FString& TypeAndName) : Super(TypeAndName)
{
}

// FInventoryItemSlot
FInventoryItemSlot::FInventoryItemSlot(const FPrimaryInventoryItemId& ItemId): ItemId(ItemId)
{
}

FInventoryItemSlot::FInventoryItemSlot(const FPrimaryInventoryItemId& ItemId, const int32& Count)
	: ItemId(ItemId), Count(Count)
{
}