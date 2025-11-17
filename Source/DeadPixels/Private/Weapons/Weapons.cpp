#include "Weapons.h"
#include "Bullet.h"
#include "Characters/Player/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

AWeapons::AWeapons()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Damage = 10.0f;
	FireRate = 0.3f;
	Ammo = 6;

	//WeaponParent = CreateDefaultSubobject<USceneComponent>(TEXT("GunParent"));
	//WeaponParent->SetupAttachment(GetRootComponent());
	
	//AMainCharacter* Player= Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	WeaponFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponFlipbook"));
	WeaponFlipbook->SetupAttachment(RootComponent);

	BulletSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPosition"));
	BulletSpawnPosition->SetupAttachment(WeaponFlipbook);
}

void AWeapons::BeginPlay()
{
	Super::BeginPlay();

	AMainCharacter* Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (Player && Player->WeaponParent)
	{
		AttachToComponent(Player->WeaponParent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		Player->SetEquippedWeapon(this);
	}
}

void AWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapons::Fire()
{
	if (CanAttack)
	{
		CanAttack = false;

		//Bullet spawn
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Shoot"));
		ABullet *Bullet = GetWorld()->SpawnActor<ABullet>(BulletActorToSpawn, BulletSpawnPosition->GetComponentLocation(), FRotator(0, 0, 0));
		check(Bullet);
		
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		check(PlayerController);
		FVector MWorldLoc, MWorldDir;
		PlayerController->DeprojectMousePositionToWorld(MWorldLoc,MWorldDir);

		FVector CurrentLoc = GetActorLocation();
		FVector2D BulletDirection = FVector2D(MWorldLoc.X - CurrentLoc.X, MWorldLoc.Y - CurrentLoc.Y);
		BulletDirection.Normalize();

		float BulletSpeed = Bullet->MovementSpeed;
		Bullet->Launch(BulletDirection, BulletSpeed);

		GetWorldTimerManager().SetTimer(CooldownTimer, this, &AWeapons::OnCooldownTimerTimeout, 1.0f, false, FireRate);
	}
}

void AWeapons::OnCooldownTimerTimeout()
{
	CanAttack = true;
}



/*Weapons::Weapons()
{
}

Weapons::~Weapons()
{
}*/
