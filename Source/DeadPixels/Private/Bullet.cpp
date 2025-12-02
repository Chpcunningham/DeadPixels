#include "Bullet.h"

#include "SkeletonTreeBuilder.h"
#include "Weapons/Weapons.h"
#include "Characters/Enemies/EnemyBase.h"
#include "DynamicMesh/MeshTransforms.h"
#include "Kismet/GameplayStatics.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp =  CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);

	BulletSprite =  CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BulletSprite"));
	BulletSprite->SetupAttachment(RootComponent);
	
	MovementDirection = FVector2D(1.0f, 0.0f);

	// Enable Hit Events on the Sphere Component
	SphereComp->SetNotifyRigidBodyCollision(true);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->UpdateOverlaps();
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapStart);
	//Launch(FVector2D(0.0f, 1.0f), 25.0f);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLaunched)
	{
		FVector2D DistanceToMove = MovementDirection * MovementSpeed * DeltaTime;

		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, DistanceToMove.Y, 0);
	
		SetActorLocation(NewLocation);
	}
}

void ABullet::SetWeapon(AWeapons* Weapon)
{
	CurrentWeapon = Weapon;
	if (SphereComp && CurrentWeapon)
	{
		SphereComp->SetWorldScale3D(FVector(CurrentWeapon->BulletSize));
	}
}


void ABullet::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
	{
		if (!CurrentWeapon) return;
		
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UGameplayStatics::ApplyDamage(Enemy, CurrentWeapon->Damage, PlayerController, PlayerController, UDamageType::StaticClass());
		this->Destroy();
	}
}

void ABullet::Launch(FVector2D Direction, float Speed)
{
	if (IsLaunched) return;
	
	IsLaunched = true;

	MovementDirection = Direction;
	MovementSpeed = Speed;

	GetWorldTimerManager().SetTimer(DeleteTimer, this, &ABullet::OnDeleteTimerTimeOut, 1.0f, false, DeleteTime);
}

void ABullet::OnDeleteTimerTimeOut()
{
	Destroy();
}