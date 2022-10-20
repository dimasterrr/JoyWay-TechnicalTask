#pragma once
#include "CoreMinimal.h"
#include "JoyWay_TechnicalTask/Components/Inventory/InventoryComponent.h"
#include "UObject/Interface.h"
#include "InventoryComponentInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UInventoryComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class JOYWAY_TECHNICALTASK_API IInventoryComponentInterface
{
	GENERATED_BODY()

public:
	virtual UInventoryComponent* GetInventoryComponent() const = 0;
};
