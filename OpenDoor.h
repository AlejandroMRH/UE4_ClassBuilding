// Alejandro Montenegro Reyes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Math/UnrealMathUtility.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoorFunc(float DeltaTime);
	void CloseDoorFunc(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

float InitialYaw;
float CurrentYaw;

	UPROPERTY(EditAnywhere) // [SerializedFiel] equivalent of C#
	float OpenAngle;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float DoorLastOpen = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 4.f;	

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 4.f;
};
