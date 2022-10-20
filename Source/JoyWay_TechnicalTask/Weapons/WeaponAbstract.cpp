#include "WeaponAbstract.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AWeaponAbstract::AWeaponAbstract()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow point"));
	SpawnPoint->SetupAttachment(Mesh);
}

void AWeaponAbstract::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DelayBetweenTimeHandle.Invalidate();
	ReloadFireTimeHandle.Invalidate();

	Super::EndPlay(EndPlayReason);
}


void AWeaponAbstract::OnFireReload()
{
	GetWorldTimerManager().ClearTimer(ReloadFireTimeHandle);
}

bool AWeaponAbstract::CanReload()
{
	return false;
}

bool AWeaponAbstract::CanFire() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(ReloadFireTimeHandle) && HasAmmo();
}

bool AWeaponAbstract::HasAmmo() const
{
	return CurrentAmmoCount > 0;
}

void AWeaponAbstract::OnReload()
{
	OnReloadEvent();
}

void AWeaponAbstract::OnFire()
{
	if (const auto Character = Cast<ACharacter>(GetOwner()))
		Character->GetMesh()->GetAnimInstance()->Montage_Play(OwnerFireAnimMontage);

	UGameplayStatics::SpawnEmitterAttached(FireEmitterTemplate, SpawnPoint);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSoundTemplate, SpawnPoint->GetComponentLocation());

	OnFireEvent();
}

void AWeaponAbstract::FireStart()
{
	if (!CanFire()) return;
	GetWorldTimerManager().SetTimer(DelayBetweenTimeHandle, this, &AWeaponAbstract::OnFire, FireRate, true, 0.f);
}

void AWeaponAbstract::FireStop()
{
	if (!GetWorldTimerManager().IsTimerActive(DelayBetweenTimeHandle)) return;
	GetWorldTimerManager().ClearTimer(DelayBetweenTimeHandle);

	if (GetWorldTimerManager().IsTimerActive(ReloadFireTimeHandle)) return;
	GetWorldTimerManager().SetTimer(ReloadFireTimeHandle, this, &AWeaponAbstract::OnFireReload, FireRate);
}

void AWeaponAbstract::Reload()
{
	if (!CanReload()) return;
	OnReload();
}

void AWeaponAbstract::AddAmmo(int Value)
{
	CurrentAmmoCount = FMath::Clamp(CurrentAmmoCount + Value, 0, MaxAmmoCount);
}