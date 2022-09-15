// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryManCharacter.h"
#include "DrawDebugHelpers.h"
#include "Pickable.h"

// Sets default values
ABatteryManCharacter::ABatteryManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;

	GetCharacterMovement()->JumpZVelocity = 300.0f;
	GetCharacterMovement()->AirControl = 60.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	Collector = CreateDefaultSubobject<USphereComponent>(TEXT("Collector"));
	Collector->AttachTo(RootComponent);
	Collector->InitSphereRadius(CollectorRadius);
	Collector->SetCollisionProfileName(TEXT("Trigger"));
	Collector->OnComponentBeginOverlap.AddDynamic(this, &ABatteryManCharacter::OnCollectorBeginOverlap);
}

// Called when the game starts or when spawned
void ABatteryManCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugSphere(GetWorld(), Collector->GetComponentLocation(), Collector->GetScaledSphereRadius(), 26, FColor::Green, false, -1.0f, 0u, 2.0f);

	StoredPower = InitialStoredPower;
}

// Called every frame
void ABatteryManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), Collector->GetComponentLocation(), Collector->GetScaledSphereRadius(), 26, FColor::Green, false, -1.0f, 0u, 2.0f);
}

// Called to bind functionality to input
void ABatteryManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryManCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryManCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ABatteryManCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABatteryManCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

float ABatteryManCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	StoredPower -= Damage;

	if (StoredPower <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Player is dead", true);
	}

	return Damage;
}

void ABatteryManCharacter::OnCollectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass()->ImplementsInterface(UPickable::StaticClass()))
		{
			Cast<IPickable>(OtherActor)->Execute_Collected(OtherActor);
		}
	}
}

