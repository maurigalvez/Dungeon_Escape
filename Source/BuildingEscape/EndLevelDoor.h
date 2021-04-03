// Copyright Mauricio Galvez 2021

#pragma once

#include "CoreMinimal.h"
#include "OpenDoor.h"
#include "Containers/Array.h"
#include "PuzzleStatue_TriggerVolume.h"
#include "EndLevelDoor.generated.h"

/**
 * Defines end level door class
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UEndLevelDoor : public UOpenDoor
{
	GENERATED_BODY()
public:

	// constructor
	UEndLevelDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool ShouldOpenDoor();

	UPROPERTY(EditAnywhere)
	APuzzleStatue_TriggerVolume* SilverTrigger;

	UPROPERTY(EditAnywhere)
	APuzzleStatue_TriggerVolume* BronzeTrigger;
};
