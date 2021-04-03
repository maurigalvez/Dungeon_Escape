// Copyright Mauricio Galvez 2021

#pragma once
#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate();

protected:	
	float m_StartYaw;
	float m_CurrentYaw;
	float m_DoorLastOpened = 0.f;	
	bool OpenDoorIsPlaying = false;
	bool CloseDoorIsPlaying = true;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = .5f;

	UPROPERTY(EditAnywhere)
	float CloseSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float DelayBeforeClosing = 1.f;

	UPROPERTY(EditAnywhere)
	float MassNeededToOpen = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* m_TriggerVolume = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
