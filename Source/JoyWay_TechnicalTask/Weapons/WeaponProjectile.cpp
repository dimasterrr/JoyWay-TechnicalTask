#include "WeaponProjectile.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JoyWay_TechnicalTask/Base/GameModeCore.h"
#include "JoyWay_TechnicalTask/Components/ActorPollComponent/ActorPoolComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectiles/ProjectileBase.h"

AWeaponProjectile::AWeaponProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformProjectilePath(DeltaTime);
}

void AWeaponProjectile::PerformProjectilePath(float DeltaTime)
{
	if (!UsePredictsProjectilePathParams && DefaultProjectileClass != nullptr) return;

	const auto DefaultProjectile = DefaultProjectileClass.GetDefaultObject();
	const auto DefaultProjectileMovement = DefaultProjectile->GetProjectileMovementComponent();

	PredictsProjectilePathParams.StartLocation = SpawnPoint->GetComponentLocation();
	PredictsProjectilePathParams.LaunchVelocity = SpawnPoint->GetForwardVector() *
		DefaultProjectileMovement->InitialSpeed;
	PredictsProjectilePathParams.OverrideGravityZ = GetWorld()->GetWorldSettings()->GetGravityZ() *
		DefaultProjectileMovement->ProjectileGravityScale;
	PredictsProjectilePathParams.ProjectileRadius = DefaultProjectile->GetSimpleCollisionRadius();

	FPredictProjectilePathResult PredictResult;
	UGameplayStatics::PredictProjectilePath(this, PredictsProjectilePathParams, PredictResult);
}

void AWeaponProjectile::OnFire()
{
	if (!HasAmmo()) return;

	Super::OnFire();
	OnLaunchProjectile();
	CurrentAmmoCount--;
}

void AWeaponProjectile::OnLaunchProjectile()
{
	const auto GameMode = Cast<AGameModeCore>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto ProjectilePool = GameMode->GetProjectilePool();
	if (!ProjectilePool) return;

	// Can use predict-camera for calculate direction
	if (const auto TargetWorld = GetWorld())
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnPoint->GetComponentLocation());
		SpawnTransform.SetRotation(SpawnPoint->GetComponentRotation().Quaternion());
	
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		ProjectilePool->GetOrCreate(DefaultProjectileClass, SpawnTransform, SpawnParameters);
	}
}
