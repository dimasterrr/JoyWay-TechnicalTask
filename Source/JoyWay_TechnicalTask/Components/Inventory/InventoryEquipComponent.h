#pragma once
#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryEquipComponent.generated.h"

enum class EInventoryEquipSlot : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_TECHNICALTASK_API UInventoryEquipComponent : public UInventoryComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventorySlotOperation,
	                                             EInventoryEquipSlot, Slot,
	                                             FPrimaryInventoryItemId, Item);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Equip)
	TMap<EInventoryEquipSlot, int32> EquipSlots;

public:
	UPROPERTY(BlueprintAssignable, Category=Equip)
	FInventorySlotOperation InventorySlotEquipped;
	
	UPROPERTY(BlueprintAssignable, Category=Equip)
	FInventorySlotOperation InventorySlotUnEquipped;
	
public:
	UInventoryEquipComponent();

	virtual bool AddItem(const FPrimaryInventoryItemId& ItemId, const int32 Count, int32& OutItemIndex) override;
	virtual bool RemoveItem(const FPrimaryInventoryItemId& ItemId, const int32 Count) override;
};
