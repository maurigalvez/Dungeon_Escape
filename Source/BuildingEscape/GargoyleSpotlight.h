// Copyright Mauricio Galvez 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SpotLightComponent.h"
#include "PuzzleStatue_TriggerVolume.h"
#include "GargoyleSpotlight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGargoyleSpotlight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGargoyleSpotlight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	int32 LightsActivated = 0;
	USpotLightComponent* SpotLightToActivate = nullptr; 

	UPROPERTY(EditAnywhere)
	APuzzleStatue_TriggerVolume* SilverTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	APuzzleStatue_TriggerVolume* BronzeTrigger = nullptr;
};
