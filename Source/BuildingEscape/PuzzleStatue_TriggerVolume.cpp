// Copyright Mauricio Galvez 2021

#include "PuzzleStatue_TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"

// constructor
APuzzleStatue_TriggerVolume::APuzzleStatue_TriggerVolume()
{	
}

void APuzzleStatue_TriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	// validate statue type
	if (this->SpecificStatueType == StatueType::NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("No valid statue type was found in %s!"), *this->GetName());
		return;
	}
	//Register event
	this->OnActorBeginOverlap.AddDynamic(this, &APuzzleStatue_TriggerVolume::OnOverlapBegin);
	this->OnActorEndOverlap.AddDynamic(this, &APuzzleStatue_TriggerVolume::OnOverlapEnd);
}

bool APuzzleStatue_TriggerVolume::CheckIfActivated()
{
	return this->IsActivated;
}

void APuzzleStatue_TriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// validate other actor
	if (OtherActor && (OtherActor != this))
	{
		UPuzzleStatue* statue = OtherActor->FindComponentByClass<UPuzzleStatue>();
		if (statue != NULL && statue->GetStatueType() == this->SpecificStatueType) 
		{
			ActivateEvents();
		}
	}
}

void APuzzleStatue_TriggerVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	// validate other actor
	if (OtherActor && (OtherActor != this))
	{
		UPuzzleStatue* statue = OtherActor->FindComponentByClass<UPuzzleStatue>();
		if (statue != NULL && statue->GetStatueType() == this->SpecificStatueType)
		{
			DeactivateEvents();
		}
	}
}

void APuzzleStatue_TriggerVolume::ActivateEvents()
{
	this->IsActivated = true;
	if (this->TorchToActivate != nullptr)
	{
		// turn on torch particle
		UParticleSystemComponent* particles = this->TorchToActivate->FindComponentByClass<UParticleSystemComponent>();
		if (particles != NULL)
		{
			particles->Activate();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No particle system was found in %s!"), *this->TorchToActivate->GetName());
		}
		// turn on light
		UPointLightComponent* light = this->TorchToActivate->FindComponentByClass<UPointLightComponent>();
		if (light != NULL)
		{
			light->SetVisibility(true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No light was found in %s!"), *this->TorchToActivate->GetName());
		}
		// turn torch audio on
		UAudioComponent* audio = this->TorchToActivate->FindComponentByClass<UAudioComponent>();
		if (audio != NULL)
		{
			audio->Play();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No audio was found in %s!"), *this->TorchToActivate->GetName());
		}
	}
}

void APuzzleStatue_TriggerVolume::DeactivateEvents()
{
	this->IsActivated = false;
	if (this->TorchToActivate != nullptr)
	{
		// turn off torch particle
		UParticleSystemComponent* particles = this->TorchToActivate->FindComponentByClass<UParticleSystemComponent>();
		if (particles != NULL)
		{
			particles->Deactivate();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No particle system was found in %s!"), *this->TorchToActivate->GetName());
		}
		// turn on light
		UPointLightComponent* light = this->TorchToActivate->FindComponentByClass<UPointLightComponent>();
		if (light != NULL)
		{
			light->SetVisibility(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No light was found in %s!"), *this->TorchToActivate->GetName());
		}
		// turn torch audio off
		UAudioComponent* audio = this->TorchToActivate->FindComponentByClass<UAudioComponent>();
		if (audio != NULL)
		{
			audio->Stop();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No audio was found in %s!"), *this->TorchToActivate->GetName());
		}
	}
}
