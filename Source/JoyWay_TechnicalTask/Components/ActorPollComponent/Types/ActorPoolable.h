#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPoolable.generated.h"

class UActorPoolComponent;

UCLASS()
class JOYWAY_TECHNICALTASK_API AActorPoolable : public AActor
{
	GENERATED_BODY()

	friend class ObjectPoolComponent;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	UActorPoolComponent* Pool = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Handlers, meta=(AllowPrivateAccess=true))
	FTimerHandle AutoDestroyHandler;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Pool")
	bool AutoDestroyable = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Pool", meta=(EditCondition=AutoDestroyable))
	float TimeToAutoDestroy = 10.f;

protected:
	virtual void BeginPlay() override;
	virtual void OnActivated();
	virtual void OnReleased();
	
public:
	UFUNCTION(BlueprintCallable)
	void SetPool(UActorPoolComponent* Value);

	UFUNCTION(BlueprintCallable)
	void Active();

	UFUNCTION(BlueprintCallable)
	void Release();
};
