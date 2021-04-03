// Copyright Mauricio Galvez 2021


#include "AudioTriggerVolume.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AAudioTriggerVolume::AAudioTriggerVolume()
{

}

void AAudioTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	if (this->ActorWithAudio == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No actor with audio was found in %s!"), *this->GetName());;
	}
	this->OnActorBeginOverlap.AddDynamic(this, &AAudioTriggerVolume::OnOverlapBegin);
}

void AAudioTriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AActor* playerActor = this->GetWorld()->GetFirstPlayerController()->GetPawn();
	// check if actor is player
	if (OtherActor && (OtherActor != this) && OtherActor != playerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Not player actor %s!"), *OtherActor->GetName());;
		return;
	}
	if (this->ActorWithAudio != nullptr)
	{
		UAudioComponent* audio = this->ActorWithAudio->FindComponentByClass<UAudioComponent>();
		if (audio != NULL)
		{
			audio->Play();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No audio component was found in %s!"), *this->ActorWithAudio->GetName());;
		}
	}
}

