#include "Weapons.h"

AWeapons::AWeapons()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Damage = 10.0f;
	FireRate = 0.5f;
	Ammo = 6;

	WeaponParent = CreateDefaultSubobject<USceneComponent>(TEXT("GunParent"));
	WeaponParent->SetupAttachment(GetRootComponent());

	WeaponFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponFlipbook"));
	WeaponFlipbook->SetupAttachment(WeaponParent);

	BulletSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPosition"));
	BulletSpawnPosition->SetupAttachment(WeaponFlipbook);
}

void AWeapons::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapons::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Fired"));
}



/*Weapons::Weapons()
{
}

Weapons::~Weapons()
{
}*/
