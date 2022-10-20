#pragma once

#include "CoreMinimal.h"
#include "WeaponAbstract.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "WeaponProjectile.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API AWeaponProjectile : public AWeaponAbstract
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<class AProjectileBase> DefaultProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	bool UsePredictsProjectilePathParams = false;

	UPROPERTY(EditDefaultsOnly, Category="Settings", meta = (EditCondition = "UsePredictsProjectilePathParams"))
	FPredictProjectilePathParams PredictsProjectilePathParams;

private:
	UFUNCTION()
	void OnLaunchProjectile();

	void PerformProjectilePath(float DeltaTime);

protected:
	virtual void OnFire() override;

public:
	AWeaponProjectile();
	
	virtual void Tick(float DeltaTime) override;
};
