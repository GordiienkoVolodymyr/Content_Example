#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Demo_Display_Component.generated.h"

USTRUCT(BlueprintType)
struct FDisplay_ISM_Description
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	UStaticMesh *Mesh = 0;
};

USTRUCT(BlueprintType)
struct FDisplay_ISM_Params
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description ISM_Main;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Corner;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Curve;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Curve_Edge;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Side;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Title_Bar_Main;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Title_Bar_End;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Title_Bar_EndR;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Shadow_Straight;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Shadow_Round;
	UPROPERTY(BlueprintReadWrite)
	FDisplay_ISM_Description The_ISM_Shadow_Straight_Top;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONTENTEXAMPLES_API UDemo_Display_Component : public USceneComponent
{
	GENERATED_BODY()

public:
	UDemo_Display_Component();

	UFUNCTION(BlueprintCallable)
	UMaterialInstanceDynamic *Make_Instanes(FLinearColor color, UMaterialInterface *parent_material, FDisplay_ISM_Params ism_param, bool need_separate_title_panel);

	UFUNCTION(BlueprintCallable)
	void Make_Title_Panel(double depth, double width);

	UFUNCTION(BlueprintCallable)
	bool Make_Shadow_Box(double width, double depth, double height, double shadow_cover);

	UFUNCTION(BlueprintCallable)
	void Make_Display(double height, double depth, double width, bool &add_curve, double &lenght_top_panel, double &lenght_down_panel, FTransform &top_panel_transform, FTransform &down_panel_transform);

	UFUNCTION(BlueprintCallable)
	void Make_Scalavle_Panel (FTransform base_position, double lenght, double width);

private:
	void Setup_ISM(UInstancedStaticMeshComponent *ism_component, UMaterialInstanceDynamic *new_material, FDisplay_ISM_Description &ism_descriprion);
	void Scale_Safe_Instance(FTransform side_transform);

	UInstancedStaticMeshComponent *The_ISM_Main = 0;
	UInstancedStaticMeshComponent *The_ISM_Corner = 0;
	UInstancedStaticMeshComponent *The_ISM_Curve = 0;
	UInstancedStaticMeshComponent *The_ISM_Curve_Edge = 0;
	UInstancedStaticMeshComponent *The_ISM_Side = 0;
	UInstancedStaticMeshComponent *The_ISM_Title_Bar_Main = 0;
	UInstancedStaticMeshComponent *The_ISM_Title_Bar_End = 0;
	UInstancedStaticMeshComponent *The_ISM_Title_Bar_EndR = 0;
	UInstancedStaticMeshComponent *The_ISM_Shadow_Straight = 0;
	UInstancedStaticMeshComponent *The_ISM_Shadow_Round = 0;
	UInstancedStaticMeshComponent *The_ISM_Shadow_Straight_Top = 0;
};
