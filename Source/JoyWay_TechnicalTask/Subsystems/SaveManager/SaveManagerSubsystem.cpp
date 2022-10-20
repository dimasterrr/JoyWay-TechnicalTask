#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Types/SaveGameInfo.h"

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSave = Cast<USaveGameInfo>(UGameplayStatics::CreateSaveGameObject(USaveGameInfo::StaticClass()));
}

void USaveManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UWorld* USaveManagerSubsystem::GetWorld() const
{
	return HasAnyFlags(RF_ClassDefaultObject) ? nullptr : Super::GetWorld();
}

bool USaveManagerSubsystem::IsSaveGameExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

USaveGameInfo* USaveManagerSubsystem::GetCurrentSave() const
{
	return CurrentSave;
}

void USaveManagerSubsystem::LoadGame(const FString& SlotName)
{
	if (!IsSaveGameExist(SlotName)) return;

	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &ThisClass::OnGameLoadedEvent);
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadDelegate);
}

void USaveManagerSubsystem::SaveGame(const FString& SlotName)
{
	CurrentSave->CollectData(GetWorld());

	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &ThisClass::OnGameSavedEvent);
	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, SaveDelegate);
}

void USaveManagerSubsystem::ResetGame(const FString& SlotName)
{
	if (!IsSaveGameExist(SlotName)) return;

	CurrentSave = nullptr;
	UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}

void USaveManagerSubsystem::OnGameLoadedEvent(const FString& SlotName, int Index, USaveGame* SaveGame)
{
	CurrentSave = Cast<USaveGameInfo>(SaveGame);
	CurrentSave->ApplyData(GetWorld());

	if (OnGameLoaded.IsBound()) { OnGameLoaded.Broadcast(SlotName); }
}

void USaveManagerSubsystem::OnGameSavedEvent(const FString& SlotName, int Index, bool Success)
{
	if (OnGameSaved.IsBound()) { OnGameSaved.Broadcast(SlotName); }
}
