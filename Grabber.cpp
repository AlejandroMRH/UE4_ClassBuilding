// Alejandro Montenegro Reyes

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	//You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleFunc();
	SetupInputComponentFunc();	
}

FHitResult UGrabber::GetFirstPhysicBodyInReachFunc() const
{
	//Get player point of View
	FRotator PlayerViewRotation;
	FVector PlayerViewLocation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
												(
													OUT PlayerViewLocation, 
													OUT PlayerViewRotation
												);

//Draw Line debug from player to objet to reach
	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	DrawDebugLine
		(
			GetWorld(),
			PlayerViewLocation,
			LineTraceEnd,
			FColor(0, 255, 0),
			false,
			0.f,
			0.f,
			5.f
		);
	
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
					(
						OUT Hit,
						PlayerViewLocation,
						LineTraceEnd,
						FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
						TraceParams
					);

	//log out hit object
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("TraceLine hit: %s"), *ActorHit->GetName());
	}

	return Hit;
}

void UGrabber::SetupInputComponentFunc()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("GrabShit", IE_Pressed, this, &UGrabber::GrabFunc);
		InputComponent->BindAction("GrabShit", IE_Released, this, &UGrabber::ReleaseFunc);
	}
}

void UGrabber::FindPhysicsHandleFunc()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//no code need here physics handle found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR NO PhysicsHandle on %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::GrabFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));

	FHitResult HitResult = GetFirstPhysicBodyInReachFunc();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	//try to reach and grab collision physics objects
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
						(
							ComponentToGrab,
							NAME_None,
							LineTraceEnd
						);
	}
	
}

void UGrabber::ReleaseFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));

	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
	//if physics handle is attyach
		//move object being hold

}

