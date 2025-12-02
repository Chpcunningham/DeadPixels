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
	BulletSpeed = 2.0f;
	BulletSpread = 100.f;

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
	if (IsReloading) return;

	if (Ammo <= 0)
	{
		StartReload();
		return;
	}

	if (!CanAttack) return;

	CanAttack = false;

	if (NumOfBullets == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Shoot"));

		ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletActorToSpawn,
		                                                  BulletSpawnPosition->GetComponentLocation(),
		                                                  FRotator(0, 0, 0));
		check(Bullet);

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		check(PlayerController);
		FVector MWorldLoc, MWorldDir;
		PlayerController->DeprojectMousePositionToWorld(MWorldLoc, MWorldDir);

		FVector CurrentLoc = GetActorLocation();
		FVector2D BulletDirection = FVector2D(MWorldLoc.X - CurrentLoc.X, MWorldLoc.Y - CurrentLoc.Y);
		BulletDirection.Normalize();

		//BulletSpeed = Bullet->MovementSpeed;
		if (Bullet)
		{
			Bullet->SetWeapon(this);
			Bullet->Launch(BulletDirection, BulletSpeed);
		}
		Ammo--;
		GetWorldTimerManager().SetTimer(CooldownTimer, this, &AWeapons::OnCooldownTimerTimeout, 1.0f, false,
		                                FireRate);
	}
	else
	{
		for (int i = 0; i < NumOfBullets; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Shoot"));
			float BulletSpreadX = FMath::RandRange(-BulletSpread, BulletSpread);
			float BulletSpreadY = FMath::RandRange(-BulletSpread, BulletSpread);

			ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletActorToSpawn,
			                                                  BulletSpawnPosition->GetComponentLocation(),
			                                                  FRotator(0, 0, 0));
			check(Bullet);

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			check(PlayerController);
			FVector MWorldLoc, MWorldDir;
			PlayerController->DeprojectMousePositionToWorld(MWorldLoc, MWorldDir);
			MWorldLoc.X = MWorldLoc.X + BulletSpreadX;
			MWorldLoc.Y = MWorldLoc.Y + BulletSpreadY;
			FVector CurrentLoc = GetActorLocation();
			FVector2D BulletDirection = FVector2D(MWorldLoc.X - CurrentLoc.X, MWorldLoc.Y - CurrentLoc.Y);
			BulletDirection.Normalize();

			//float BulletSpeed = Bullet->MovementSpeed;

			if (Bullet)
			{
				Bullet->SetWeapon(this);
				Bullet->Launch(BulletDirection, BulletSpeed);
			}
		}
		Ammo--;
		GetWorldTimerManager().SetTimer(CooldownTimer, this, &AWeapons::OnCooldownTimerTimeout, 1.0f, false,
		                                FireRate);
	}
}


void AWeapons::OnCooldownTimerTimeout()
{
	CanAttack = true;
}

void AWeapons::OnReloadTimerTimeout()
{
	Ammo = MaxAmmo;
	CanAttack = true;
	IsReloading = false;
}

void AWeapons::StartReload()
{
	if (IsReloading) return;
	if (Ammo == MaxAmmo) return;

	IsReloading = true;
	CanAttack = false;

	GetWorldTimerManager().SetTimer(ReloadTimer, this, &AWeapons::OnReloadTimerTimeout, ReloadRate, false);
}
