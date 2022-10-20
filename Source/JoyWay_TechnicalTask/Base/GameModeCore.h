#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeCore.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API AGameModeCore : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UActorPoolComponent* ProjectilePool;
	
public:
	AGameModeCore();

	UFUNCTION(BlueprintPure, Category=GameMode)
	UActorPoolComponent* GetProjectilePool() const;
};
