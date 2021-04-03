// Copyright Mauricio Galvez 2021


#include "PuzzleStatue.h"

// Sets default values for this component's properties
UPuzzleStatue::UPuzzleStatue()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPuzzleStatue::BeginPlay()
{
	Super::BeginPlay();
	// validate statue type
	if (this->StatueType == StatueType::NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("No valid statue type was found in %s!"), *this->GetOwner()->GetName());
	}	
}


// Called every frame
void UPuzzleStatue::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TEnumAsByte<StatueType> UPuzzleStatue::GetStatueType()
{
	return this->StatueType;
}

