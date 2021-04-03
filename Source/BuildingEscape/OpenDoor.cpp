// Copyright Mauricio Galvez 2021


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	FindPressurePlate();
	FindAudioComponent();
	
	// hook trigger volume
	this->m_StartYaw = this->GetOwner()->GetActorRotation().Yaw;
	this->m_CurrentYaw = this->m_StartYaw;
	this->OpenAngle += this->m_StartYaw;
	
	// we don't call getOwner in constructor!
	//FRotator currentRotation = GetOwner()->GetActorRotation();
	// solution 1:
	// currentRotation.Yaw = 90.f;
	// GetOwner()->SetActorRelativeRotation(currentRotation);
	// solution 2: 
	// FRotator newRotation = FRotator(currentRotation.Pitch, 90.f,currentRotation.Roll);
	// GetOwner()->SetActorRelativeRotation(newRotation);
	// solution 3:
	// FRotator openDoor(0.f,90.f,0.f);
	// GetOwner()->SetActorRelativeRotation(openDoor);
	// FRotator is in Pitch(Y), Yaw (Z) , Roll (X)
	// RelativeRotation is LocalRotation;
}

void UOpenDoor::FindPressurePlate()
{
	if (this->m_TriggerVolume == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("No trigger volume was assigned"));
	}
}

void UOpenDoor::FindAudioComponent()
{
	this->AudioComponent = this->GetOwner()->FindComponentByClass<UAudioComponent>();
	if (this->AudioComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component found in %s"), *this->GetOwner()->GetName());
	}
}

// Called every frames
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// check if trigger actor is not at the door
	if (this->TotalMassOfActors() > this->MassNeededToOpen)
	{
		this->OpenDoor(DeltaTime);
		this->m_DoorLastOpened = this->GetWorld()->GetTimeSeconds();
		if (this->CloseDoorIsPlaying)
		{
			this->CloseDoorIsPlaying = false;
		}
	}	
	else
	{
		float timePassed = this->GetWorld()->GetTimeSeconds() - this->m_DoorLastOpened;
		if (timePassed > this->DelayBeforeClosing)
		{
			if (this->OpenDoorIsPlaying)
			{
				this->OpenDoorIsPlaying = false;
			}
			this->CloseDoor(DeltaTime);
		}
	}

}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// ---
	// LERP START TO END
	// -----
	/*
	if (m_TimeElapsed < 1)
	{
		m_TimeElapsed += DeltaTime;
	}
	// Lerp
	FRotator newRotation(0.f, FMath::Lerp(this->m_StartYaw, this->m_TargetYaw, m_TimeElapsed), 0.f);*/

	// -----
	// LERP OVER TIME
	// ------
	//this->m_CurrentYaw = this->GetOwner()->GetActorRotation().Yaw;
	// FRotator newRotation(0.f, this->m_TargetYaw, 0.f);
	// InterSpeed is degrees per sec in this case, this moves in constant motion
	//newRotation.Yaw = FMath::FInterpConstantTo(currentYaw, this->m_TargetYaw, DeltaTime, 45);
	// adds nice slow effect in the end
	// newRotation.Yaw = FMath::FInterpTo(this->m_CurrentYaw, this->m_TargetYaw, DeltaTime, 2.f);
	// this->GetOwner()->SetActorRotation(newRotation);
	// -----
	// Set actor Rotation
	// ------
	FRotator doorRotation = this->GetOwner()->GetActorRotation();
	this->m_CurrentYaw = FMath::Lerp(this->m_CurrentYaw, this->OpenAngle, DeltaTime * this->OpenSpeed);
	doorRotation.Yaw = this->m_CurrentYaw;
	this->GetOwner()->SetActorRotation(doorRotation);
	if (!this->OpenDoorIsPlaying && this->AudioComponent != nullptr)
	{
		this->AudioComponent->Play();
		this->OpenDoorIsPlaying = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// -----
	// Set actor Rotation
	// ------
	FRotator doorRotation = this->GetOwner()->GetActorRotation();
	this->m_CurrentYaw = FMath::Lerp(this->m_CurrentYaw, this->m_StartYaw, DeltaTime * this->CloseSpeed);
	doorRotation.Yaw = this->m_CurrentYaw;
	this->GetOwner()->SetActorRotation(doorRotation);
	if (!this->CloseDoorIsPlaying && this->AudioComponent != nullptr)
	{
		this->AudioComponent->Play();
		this->CloseDoorIsPlaying = true;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float totalMass = 0.f;
	if (this->m_TriggerVolume == nullptr)
	{
		return totalMass;
	}
	//iterate through actors overlapping and add mass
	TArray<AActor*> actorsOverlapping;
	this->m_TriggerVolume->GetOverlappingActors(OUT actorsOverlapping);
	// iterate through overlapping actors
	for (int aIndex = 0; aIndex < actorsOverlapping.Num(); aIndex++)
	{
		totalMass += actorsOverlapping[aIndex]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}

