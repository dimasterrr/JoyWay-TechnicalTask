#include "InteractionComponent.h"

#include "Types/InteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickTraceHandler(DeltaTime);
}

void UInteractionComponent::TickTraceHandler(float DeltaTime)
{
	if (!GetWorld()) return;

	// Get direction from camera
	const auto CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	const auto CameraForwardVector = CameraManager->GetActorForwardVector();
	const auto StartLocation = CameraManager->GetCameraLocation();
	const auto EndLocation = StartLocation + CameraForwardVector * Distance;
	const auto ActorToIgnore = TArray<AActor*>{GetOwner()};
	const auto DrawType = DrawDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;

	FHitResult HitResult;
	const auto IsHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation,
															 UEngineTypes::ConvertToTraceType(ECC_Camera), false,
															 ActorToIgnore, DrawType, HitResult, true);

	const auto NewTargetActor = (IsHit && HitResult.GetActor()->Implements<UInteractionInterface>())
									? HitResult.GetActor()
									: nullptr;

	// Skip already given element
	if (NewTargetActor == TargetActor) return;
	
	TargetActor = NewTargetActor;
	TargetIsChanged.Broadcast(TargetActor);
}

void UInteractionComponent::Interact()
{
	if (!TargetActor) return;
	IInteractionInterface::Execute_Interaction(TargetActor, GetOwner());
}
