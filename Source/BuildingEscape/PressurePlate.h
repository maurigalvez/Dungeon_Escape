// Copyright Mauricio Galvez 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "PressurePlate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPressurePlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float TotalMassOfActors() const;
	void PressPlate(float DeltaTime, float PressPercentage);
	void UnpressPlate(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector StartLocation = FVector::ZeroVector;
	FVector EndLocation = FVector::ZeroVector;
	FVector CurrentLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float PressDistance = .5f;

	UPROPERTY(EditAnywhere)
	float MassNeededToPress = 50.f;

	UPROPERTY(EditAnywhere)
	float PressSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerVolume = nullptr;
		
};
