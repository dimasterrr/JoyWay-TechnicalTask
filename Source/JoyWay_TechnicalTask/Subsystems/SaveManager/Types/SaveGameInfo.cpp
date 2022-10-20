#include "SaveGameInfo.h"

#include "JoyWay_TechnicalTask/Components/Health/HealthComponent.h"
#include "JoyWay_TechnicalTask/Components/Inventory/InventoryEquipComponent.h"
#include "JoyWay_TechnicalTask/Helpers/GeneralHelper.h"
#include "JoyWay_TechnicalTask/Pawns/PlayerCharacter.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveGameInfo::CollectData(const UWorld* World)
{
	// Can use pawn serialization

	if (const auto Pawn = Cast<APlayerCharacter>(World->GetFirstPlayerController()->GetPawn()))
	{
		// Health
		{
			const auto Component = Cast<UHealthComponent>(Pawn->GetComponentByClass(UHealthComponent::StaticClass()));
			Health = Component->GetHealth();
		}
		
		// Inventory
		{
			const auto Component = Cast<UInventoryComponent>(
				Pawn->GetComponentByClass(UInventoryComponent::StaticClass()));
			InventorySlots = Component->GetItems();
		}

		// Equip
		{
			const auto Component = Cast<UInventoryEquipComponent>(
				Pawn->GetComponentByClass(UInventoryEquipComponent::StaticClass()));
			EquipSlots = Component->GetItems();
		}
	}
}

void USaveGameInfo::ApplyData(const UWorld* World)
{
	if (const auto Pawn = Cast<APlayerCharacter>(World->GetFirstPlayerController()->GetPawn()))
	{
		// Health
		{
			const auto Component = Cast<UHealthComponent>(Pawn->GetComponentByClass(UHealthComponent::StaticClass()));
			Component->SetHealth(Health, true);
		}
		
		// Inventory
		{
			const auto Component = Cast<UInventoryComponent>(
				Pawn->GetComponentByClass(UInventoryComponent::StaticClass()));
			for (const auto& Item : InventorySlots)
			{
				int32 OutIndex = INDEX_NONE;
				Component->AddItem(Item.ItemId, Item.Count, OutIndex);
			}
		}

		// Equip
		{
			const auto Component = Cast<UInventoryEquipComponent>(
				Pawn->GetComponentByClass(UInventoryEquipComponent::StaticClass()));
			for (const auto& Item : EquipSlots)
			{
				int32 OutIndex = INDEX_NONE;
				Component->AddItem(Item.ItemId, Item.Count, OutIndex);
			}
		}
	}
}
