#include "InventoryComponent.h"
#include "Helpers/InventoryHelper.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

const TArray<FInventoryItemSlot>& UInventoryComponent::GetItems() const
{
	return Items;
}

bool UInventoryComponent::AddItem(const FPrimaryInventoryItemId& ItemId, const int32 Count, int32& OutItemIndex)
{
	const auto ItemData = UInventoryHelper::GetInventoryItemData(ItemId, {"Data"});
	if (!ItemData) return false;

	if (!ItemData->IsStackable)
	{
		if (!HasFreeSlots()) return false;
		OutItemIndex = Items.Add(FInventoryItemSlot(ItemId, Count));
	}
	else
	{
		const auto FoundedItemIndex = Items.IndexOfByPredicate([=](const auto& Item) { return Item.ItemId == ItemId; });
		if (FoundedItemIndex == INDEX_NONE)
		{
			if (!HasFreeSlots()) return false;
			OutItemIndex = Items.Add(FInventoryItemSlot(ItemId, Count));
		}
		else
		{
			Items[FoundedItemIndex].Count += Count;
			OutItemIndex = FoundedItemIndex;
		}
	}

	InventoryItemsChanged.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(const FPrimaryInventoryItemId& ItemId, const int32 Count)
{
	auto TotalRemoveCounter = Count;
	auto ElementModifierMarker = TMap<int32 /* Index */, int32 /* Count */>();

	// Check for deletion.
	// Improvised transaction ;3
	for (auto i = 0; i < Items.Num(); ++i)
	{
		auto Item = Items[i];
		if (Item.ItemId != ItemId) continue;

		const auto ItemCountTemp = Item.Count - TotalRemoveCounter;
		ElementModifierMarker.Add(i, ItemCountTemp);

		TotalRemoveCounter = FMath::Abs(FMath::Min(0, ItemCountTemp));
		if (TotalRemoveCounter <= 0) break;
	}
	if (TotalRemoveCounter > 0) return false;

	for (const auto& Item : ElementModifierMarker)
	{
		if (Item.Value <= 0)
		{
			const auto TempItem = Items[Item.Key];
			Items.RemoveAt(Item.Key);
		}
		else
		{
			Items[Item.Key].Count = Item.Value;
		}
	}

	InventoryItemsChanged.Broadcast();
	return true;
}

bool UInventoryComponent::HasFreeSlots() const
{
	return Items.Num() < MaxSlots;
}