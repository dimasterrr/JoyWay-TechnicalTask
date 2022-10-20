#pragma once
#include "CoreMinimal.h"
#include "SaveManagerSubsystem.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveEvent, const FString&, SlotName);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SaveManager)
	class USaveGameInfo* CurrentSave;

public:
	UPROPERTY(BlueprintAssignable, Category=SaveManager)
	FOnSaveEvent OnGameSaved;

	UPROPERTY(BlueprintAssignable, Category=SaveManager)
	FOnSaveEvent OnGameLoaded;
	
private:
	void OnGameLoadedEvent(const FString& SlotName, int Index, class USaveGame* SaveGame);
	void OnGameSavedEvent(const FString& SlotName, int Index, bool Success);
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintPure, Category=SaveManager)
	static bool IsSaveGameExist(const FString& SlotName);

	UFUNCTION(BlueprintPure, Category=SaveManager)
	USaveGameInfo* GetCurrentSave() const;

	UFUNCTION(BlueprintCallable, Category=SaveManager)
	void LoadGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category=SaveManager)
	void SaveGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category=SaveManager)
	void ResetGame(const FString& SlotName);
};
