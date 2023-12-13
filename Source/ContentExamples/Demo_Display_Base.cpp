#include "Demo_Display_Base.h"

ADemo_Display_Base::ADemo_Display_Base()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADemo_Display_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADemo_Display_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

