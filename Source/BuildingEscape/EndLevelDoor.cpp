// Copyright Mauricio Galvez 2021


#include "EndLevelDoor.h"

// constructor
UEndLevelDoor::UEndLevelDoor()
{

}

bool UEndLevelDoor::ShouldOpenDoor()
{	
	return this->SilverTrigger->CheckIfActivated() && this->BronzeTrigger->CheckIfActivated() && this->TotalMassOfActors() > this->MassNeededToOpen;
}

void UEndLevelDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	if(this->ShouldOpenDoor())
	{
		OpenDoor(DeltaTime);
	}	
}