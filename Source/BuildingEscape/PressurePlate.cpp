// Copyright Mauricio Galvez 2021


#include "PressurePlate.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPressurePlate::UPressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPressurePlate::BeginPlay()
{
	Super::BeginPlay();
	// setup start location
	this->StartLocation = this->GetOwner()->GetActorLocation();	
	
	this->CurrentLocation = this->StartLocation;
}


// Called every frame
void UPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// get weight percentage based on weight
	float totalMass = this->TotalMassOfActors();
	// if there's any mass on top press
	if (totalMass > 0)
	{
		float weightPercentage = this->TotalMassOfActors() / this->MassNeededToPress;
		if (weightPercentage > 1)
		{
			weightPercentage = 1;
		}
		this->PressPlate(DeltaTime, weightPercentage);
	}
	else
	{
		this->UnpressPlate(DeltaTime);
	}
}

float UPressurePlate::TotalMassOfActors() const
{
	float totalMass = 0.f;
	if (this->TriggerVolume == nullptr)
	{
		return totalMass;
	}
	//iterate through actors overlapping and add mass
	TArray<AActor*> actorsOverlapping;
	this->TriggerVolume->GetOverlappingActors(OUT actorsOverlapping);
	// iterate through overlapping actors
	for (int aIndex = 0; aIndex < actorsOverlapping.Num(); aIndex++)
	{
		totalMass += actorsOverlapping[aIndex]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}

void UPressurePlate::PressPlate(float DeltaTime, float PressPercentage)
{
	// make sure you only press down based on percentage
	this->EndLocation = this->StartLocation + -FVector::UpVector * (this->PressDistance * PressPercentage);
	// move from current to percentage
	this->CurrentLocation = FMath::Lerp(this->CurrentLocation, this->EndLocation, DeltaTime * this->PressSpeed);
	this->GetOwner()->SetActorLocation(this->CurrentLocation);
}

void UPressurePlate::UnpressPlate(float DeltaTime) 
{
	// move from current to start position
	this->CurrentLocation = FMath::Lerp(this->CurrentLocation, this->StartLocation, DeltaTime * this->PressSpeed);
	this->GetOwner()->SetActorLocation(this->CurrentLocation);
}
