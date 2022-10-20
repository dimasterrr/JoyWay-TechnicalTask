#include "InventoryEquipComponent.h"
#include "Helpers/InventoryHelper.h"

UInventoryEquipComponent::UInventoryEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// PreSetup slots
	EquipSlots.Add(EInventoryEquipSlot::PrimaryWeapon, INDEX_NONE);
	EquipSlots.Add(EInventoryEquipSlot::SpecialWeapon, INDEX_NONE);
}

bool UInventoryEquipComponent::AddItem(const FPrimaryInventoryItemId& ItemId, const int32 Count, int32& OutItemIndex)
{
	const auto ItemData = UInventoryHelper::GetInventoryItemData(ItemId, {"Data"});
	if (!ItemData) return false;

	const auto FindSlotIndex = EquipSlots.Find(ItemData->EquipSlot);
	if (!FindSlotIndex) return false; // Can't add unsupported item to slot

	// Move to local inventory array
	const auto IsItemAdded = Super::AddItem(ItemId, Count, OutItemIndex);
	if (!IsItemAdded) return false;

	if (*FindSlotIndex != INDEX_NONE)
	{
		// TODO: UnEquip PREV item and move them in main inventory
	}

	// Set inventory item to slot
	*FindSlotIndex = OutItemIndex;
	InventorySlotEquipped.Broadcast(ItemData->EquipSlot, ItemId);
	
	return true;
}

bool UInventoryEquipComponent::RemoveItem(const FPrimaryInventoryItemId& ItemId, const int32 Count)
{
	const auto ItemData = UInventoryHelper::GetInventoryItemData(ItemId, {"Data"});
	if (!ItemData) return false;

	const auto FindSlotIndex = EquipSlots.Find(ItemData->EquipSlot);
	if (FindSlotIndex) return false; // Can't remove unsupported item to slot

	if (*FindSlotIndex != INDEX_NONE)
	{
		// TODO: UnEquip PREV item and move them in main inventory
	}
	
	// Clear slot item
	*FindSlotIndex = INDEX_NONE;
	InventorySlotUnEquipped.Broadcast(ItemData->EquipSlot, FPrimaryInventoryItemId());
	
	return Super::RemoveItem(ItemId, Count);
}
