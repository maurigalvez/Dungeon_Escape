// Copyright Mauricio Galvez 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "PuzzleStatue.h"
#include "PuzzleStatue_TriggerVolume.generated.h"

/**
 * Trigger volume to detect a specific type of statue
 */
UCLASS()
class BUILDINGESCAPE_API APuzzleStatue_TriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts on when spawned
	virtual void BeginPlay() override;

public :
	// Constructor for this trigger volume
	APuzzleStatue_TriggerVolume();

	// Called when an actor overlap begins
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	// Called when an actor overlap ends
	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor,  AActor* OtherActor);

	// Check whether this is activated
	UFUNCTION()
	bool CheckIfActivated();

private:
	// Activate multiple events when valid statue overlaps
	UFUNCTION()
	void ActivateEvents();

	// Deactive multiple events when valid statue overlaps
	UFUNCTION()
	void DeactivateEvents();

private:
	// Statue type that will trigger this event
	UPROPERTY(EditAnywhere)
	TEnumAsByte<StatueType> SpecificStatueType = StatueType::NONE;

	// Torch to activate when the statue has been placed over correct trigger
	UPROPERTY(EditAnywhere)
	AActor* TorchToActivate = nullptr;

	// Whether this volume is activated or not
	bool IsActivated = false;
};
