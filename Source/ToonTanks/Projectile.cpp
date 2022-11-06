// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movement Component"));
	MovementComponent->InitialSpeed = InitialSpeed;
	MovementComponent->MaxSpeed = MaxSpeed;

	TrailParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(
		TEXT("Trail Particle Component"));
	TrailParticleComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LaunchSound,
			GetActorLocation(),
			GetActorRotation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	const auto ProjectileOwner = GetOwner();

	if (ProjectileOwner != nullptr &&
		OtherActor != nullptr &&
		OtherActor != this &&
		OtherActor != ProjectileOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			ProjectileOwner->GetInstigatorController(),
			this,
			UDamageType::StaticClass());

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(
				HitCameraShakeClass);
		}
	}

	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
		this,
		HitParticles,
		GetActorLocation(),
		GetActorRotation());
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			GetActorLocation(),
			GetActorRotation());
	}
	
	Destroy();
}

