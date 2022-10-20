#include "ActorPoolable.h"

#include "JoyWay_TechnicalTask/Components/ActorPollComponent/ActorPoolComponent.h"

void AActorPoolable::BeginPlay()
{
	Super::BeginPlay();

	if (AutoDestroyable)
		GetWorldTimerManager().SetTimer(AutoDestroyHandler, this, &AActorPoolable::Release, TimeToAutoDestroy);
}

void AActorPoolable::OnActivated()
{
}

void AActorPoolable::OnReleased()
{
}

void AActorPoolable::SetPool(UActorPoolComponent* Value)
{
	if (Pool == Value) return;
	Pool = Value;
}

void AActorPoolable::Active()
{
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	OnActivated();
}

void AActorPoolable::Release()
{
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	Pool->Release(this);
	OnReleased();
}
