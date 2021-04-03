// Copyright Mauricio Galvez 2021


#include "GargoyleSpotlight.h"

// Sets default values for this component's properties
UGargoyleSpotlight::UGargoyleSpotlight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGargoyleSpotlight::BeginPlay()
{
	Super::BeginPlay();
	// reset spotlight
	this->SpotLightToActivate = this->GetOwner()->FindComponentByClass<USpotLightComponent>();
}

// Called every frame
void UGargoyleSpotlight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (this->BronzeTrigger != nullptr && this->SilverTrigger != nullptr)
	{
		this->SpotLightToActivate->SetVisibility(this->BronzeTrigger->CheckIfActivated() && this->SilverTrigger->CheckIfActivated());
	}
}

