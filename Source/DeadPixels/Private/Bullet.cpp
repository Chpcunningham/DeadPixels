#include "Bullet.h"

#include "Characters/Enemies/EnemyBase.h"
#include "Characters/Player/MainCharacter.h"
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
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapStart);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

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

void ABullet::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString(TEXT("Hit an enemy")));
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		UGameplayStatics::ApplyDamage(Enemy,1.f, MainCharacter->GetController(),MainCharacter, UDamageType::StaticClass() );
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