#pragma once

#include "CoreMinimal.h"
#include "WeaponAbstract.h"
#include "WeaponTrace.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API AWeaponTrace : public AWeaponAbstract
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float TraceDistance = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
	
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	int32 BulletsPerShot = 1;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float BulletSpread = 0.f;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Debug")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Debug")
	bool DrawTrace = false;

private:
	void OnLaunchTrace();

protected:
	virtual void OnFire() override;

public:
	AWeaponTrace();
};
