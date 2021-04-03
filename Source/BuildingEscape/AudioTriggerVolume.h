// Copyright Mauricio Galvez 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "AudioTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AAudioTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

public:
	// constructor
	AAudioTriggerVolume();

	// Called when an actor overlap begins
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

protected:
	// Called when the game starts on when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	AActor* ActorWithAudio = nullptr;
};
