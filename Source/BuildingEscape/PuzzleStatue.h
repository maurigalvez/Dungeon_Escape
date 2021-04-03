// Copyright Mauricio Galvez 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleStatue.generated.h"
// -------
// Defines type of statue
// -------
UENUM()
enum StatueType
{
	NONE UMETA(DisplayName = "None"),
	BRONZE UMETA(DisplayName = "Bronze"),
	SILVER UMETA(DisplayName = "Silver")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPuzzleStatue : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	// Sets default values for this component's properties
	UPuzzleStatue();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Return the type of statue
	TEnumAsByte<StatueType> GetStatueType();

private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<StatueType> StatueType = StatueType::NONE;		
};
