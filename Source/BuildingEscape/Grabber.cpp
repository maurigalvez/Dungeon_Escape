// Copyright Mauricio Galvez 2021
#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	FindInputComponent();
}

void UGrabber::FindPhysicsHandle()
{
	// get physics handle
	this->PhysicsHandle = this->GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// check if handle was not found
	if (this->PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found in %s"), *this->GetOwner()->GetName());
	}
}

void UGrabber::FindInputComponent()
{
	// get input component
	this->PlayerInput = this->GetOwner()->FindComponentByClass<UInputComponent>();
	if (this->PlayerInput == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No input component found in %s"), *this->GetOwner()->GetName());
	}
	else
	{
		// bind actions
		// :: operators functions are in permanent storage
		// -> pointing an address in memory
		// .  using instance or reference to access
		this->PlayerInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		this->PlayerInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Get players viewpoint
	/*FVector viewLocation;
	FRotator viewRotation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewLocation, OUT viewRotation);
	//UE_LOG(LogTemp, Display, TEXT("View Location: %s"), *viewLocation.ToString());
	//UE_LOG(LogTemp, Display, TEXT("View Rotation: %s"), *viewRotation.ToString());
	FVector viewDirection = viewRotation.Vector();
	FVector lineTraceEnd = viewLocation + viewDirection * this->Reach;

	// Draw debug line
	DrawDebugLine(
		this->GetWorld(),
		viewLocation,
		lineTraceEnd,
		FColor::Green,
		false,
		0.f,
		0,
		5.f
	);*/	
	// If the physics handle is attached , move the object we are holding
	if (this->PhysicsHandle != nullptr && this->PhysicsHandle->GrabbedComponent)
	{
		// move the object we are holding
		this->PhysicsHandle->SetTargetLocation(this->GetPlayerReach());
	}
}

FHitResult UGrabber::GetPhysicsBodyInReach() const
{
	// Try and reach actors with physics body collision channel set
	// Raycast out to a certain distance
	FHitResult hit;
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());

	this->GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		this->GetPlayerViewLocation(),
		this->GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams);

	return hit;
}

FVector UGrabber::GetPlayerViewLocation() const
{
	FVector viewLocation;
	FRotator viewRotation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewLocation, OUT viewRotation);
	return viewLocation;
}

FVector UGrabber::GetPlayerReach()const
{
	FVector viewLocation;
	FRotator viewRotation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewLocation, OUT viewRotation);
	return viewLocation + viewRotation.Vector() * this->Reach;
}

void UGrabber::Grab()
{	
	FHitResult hitResult = this->GetPhysicsBodyInReach();
	UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
	// check if there was a component hit
	if (this->PhysicsHandle != nullptr && componentToGrab != nullptr)
	{
		// attach physics handle
		this->PhysicsHandle->GrabComponentAtLocation(componentToGrab, NAME_None, this->GetPlayerReach());
	}
}

void UGrabber::Release()
{	
	// release component if one was previously grabbed
	if (this->PhysicsHandle != nullptr && this->PhysicsHandle->GrabbedComponent != NULL)
	{
		this->PhysicsHandle->ReleaseComponent();
	}
}