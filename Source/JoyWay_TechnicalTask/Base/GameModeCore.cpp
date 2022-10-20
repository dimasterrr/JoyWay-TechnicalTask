#include "GameModeCore.h"

#include "PlayerHudBase.h"
#include "JoyWay_TechnicalTask/Components/ActorPollComponent/ActorPoolComponent.h"
#include "JoyWay_TechnicalTask/Pawns/PlayerCharacter.h"

AGameModeCore::AGameModeCore()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	HUDClass = APlayerHudBase::StaticClass();

	// Components
	ProjectilePool = CreateDefaultSubobject<UActorPoolComponent>("ProjectilePoolComponent");
}

UActorPoolComponent* AGameModeCore::GetProjectilePool() const
{
	return ProjectilePool;
}
