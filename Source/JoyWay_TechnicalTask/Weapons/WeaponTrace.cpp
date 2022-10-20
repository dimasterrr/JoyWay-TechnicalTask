#include "WeaponTrace.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponTrace::AWeaponTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponTrace::OnFire()
{
	if (!HasAmmo()) return;

	Super::OnFire();
	OnLaunchTrace();
	--CurrentAmmoCount;
}

void AWeaponTrace::OnLaunchTrace()
{
	const auto CameraManagerRaw = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	const auto CameraForwardVector = CameraManagerRaw->GetActorForwardVector();
	const auto CameraStartVector = CameraManagerRaw->GetCameraLocation();
	const auto StartVector = SpawnPoint->GetComponentLocation();

	const auto DrawType = DrawTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	for (auto i = 0; i < BulletsPerShot; ++i)
	{
		const auto SpreadForwardVector =
			UKismetMathLibrary::RandomUnitVectorInConeInDegrees(CameraForwardVector, BulletSpread);
		const auto EndVector = SpreadForwardVector * TraceDistance + CameraStartVector;

		FHitResult HitResult;
		UKismetSystemLibrary::LineTraceSingle(this, StartVector, EndVector, TraceChannel, false, {}, DrawType,
		                                      HitResult, true);

		if (const auto TargetActor = HitResult.GetActor())
			TargetActor->TakeDamage(Damage, FDamageEvent(DamageType), GetInstigatorController(), this);
	}
}
