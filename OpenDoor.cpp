// Alejandro Montenegro Reyes

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"



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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw; // this set targt to 0 so we can handle in EXPOSE VARIABLE in editor

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor Component, but no PressurePlateComponent"), *GetOwner()->GetName());
	}	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoorFunc(DeltaTime);
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpen > DoorCloseDelay)
		{
			CloseDoorFunc(DeltaTime);
		}
	}
	
}

void UOpenDoor::OpenDoorFunc(float DeltaTime)
{
	/* UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw); */

	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoorFunc(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}