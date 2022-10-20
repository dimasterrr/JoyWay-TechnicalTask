#pragma once

#include "CoreMinimal.h"
#include "GeneralHelper.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API UGeneralHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static class APlayerHudBase* GetBasePlayerHud(const UObject* WorldContextObject);
};
