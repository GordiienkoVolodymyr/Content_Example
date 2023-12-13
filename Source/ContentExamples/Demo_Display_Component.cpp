#include "Demo_Display_Component.h"

UDemo_Display_Component::UDemo_Display_Component()
{
	The_ISM_Main = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Main");
	The_ISM_Corner = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Corner");
	The_ISM_Curve = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Curve");
	The_ISM_Curve_Edge = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Curve_Edge");
	The_ISM_Side = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Side");
	The_ISM_Title_Bar_Main = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Title_Bar_Main");
	The_ISM_Title_Bar_End = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Title_Bar_End");
	The_ISM_Title_Bar_EndR = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Title_Bar_EndR");
	The_ISM_Shadow_Straight = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Shadow_Straight");
	The_ISM_Shadow_Round = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Shadow_Round");
	The_ISM_Shadow_Straight_Top = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_Shadow_Straight_Top");
}

UMaterialInstanceDynamic *UDemo_Display_Component::Make_Instanes(FLinearColor color, UMaterialInterface *parent_material, FDisplay_ISM_Params ism_param, bool need_separate_title_panel)
{
	UMaterialInstanceDynamic *new_material = UMaterialInstanceDynamic::Create(parent_material, 0);

	if (new_material != 0)
	{
		new_material->SetVectorParameterValue(TEXT("Colour"), color);
	}

	Setup_ISM(The_ISM_Main, new_material, ism_param.ISM_Main);
	Setup_ISM(The_ISM_Corner, new_material, ism_param.The_ISM_Corner);
	Setup_ISM(The_ISM_Curve, new_material, ism_param.The_ISM_Curve);
	Setup_ISM(The_ISM_Curve_Edge, new_material, ism_param.The_ISM_Curve_Edge);
	Setup_ISM(The_ISM_Side, new_material, ism_param.The_ISM_Side);

	if (need_separate_title_panel)
	{
		Setup_ISM(The_ISM_Title_Bar_Main, new_material, ism_param.The_ISM_Title_Bar_Main);
		Setup_ISM(The_ISM_Title_Bar_End, new_material, ism_param.The_ISM_Title_Bar_End);
		Setup_ISM(The_ISM_Title_Bar_EndR, new_material, ism_param.The_ISM_Title_Bar_EndR);
	}

	Setup_ISM(The_ISM_Shadow_Straight, new_material, ism_param.The_ISM_Shadow_Straight);
	Setup_ISM(The_ISM_Shadow_Round, new_material, ism_param.The_ISM_Shadow_Round);
	Setup_ISM(The_ISM_Shadow_Straight_Top, new_material, ism_param.The_ISM_Shadow_Straight_Top);

	return new_material;
}

void UDemo_Display_Component::Make_Title_Panel(double depth, double width)
{
	FVector location((depth - 1.0) * 100, 0.0, 0.0);
	FVector scale(1.0, width - 3.0, 1.0);

	FTransform title_bar_main_transform(FRotator(EForceInit::ForceInit), location, scale);

	The_ISM_Title_Bar_Main->AddInstance(title_bar_main_transform, false);

	FVector left_part = location + FVector(0.0, (width - 3.0) * -50.0, 0.0);
	FVector right_part = location + FVector(0.0, (width - 3.0) * 50.0, 0.0);

	FTransform title_bar_end_transform(FRotator(EForceInit::ForceInit), left_part, FVector(1.0, -1.0, 1.0));
	FTransform title_bar_endr_transform(FRotator(EForceInit::ForceInit), right_part, FVector(1.0, 1.0, 1.0));

	The_ISM_Title_Bar_End->AddInstance(title_bar_end_transform, false);
	The_ISM_Title_Bar_EndR->AddInstance(title_bar_endr_transform, false);
}

bool UDemo_Display_Component::Make_Shadow_Box(double width, double depth, double height, double shadow_cover)
{
	if (!(shadow_cover > 0.05 && height > 2.0))
	{
		return false;
	}
	TArray<FTransform> shadow_staright_arrya_transform;
	TArray<FTransform> shadow_round_arrya_transform;
	double scale_x = (depth - 1.0) * shadow_cover;


	//1.Shadow Staright Arrya Transform
	//1.1 Shadow Staright transform 1
	FVector shadow_staright_location0(0.0, (width * 50.0), 0.0);
	FVector shadow_staright_scale0(scale_x, 1.0, (height - 1.0) / 5.0);
	FTransform shadow_staright_transform0(FRotator(EForceInit::ForceInit), shadow_staright_location0, shadow_staright_scale0);


	//1.1 Shadow Staright transform 2
	FVector shadow_staright_location2 = shadow_staright_location0 * -1.0;
	shadow_staright_location2.Z = shadow_staright_location2.Z + ((height * 100.0) - 100.0);

	FTransform shadow_staright_transform1(FRotator(0.0, 0.0, 180.0), shadow_staright_location2, shadow_staright_scale0);

	shadow_staright_arrya_transform.Add(shadow_staright_transform0);
	shadow_staright_arrya_transform.Add(shadow_staright_transform1);

	The_ISM_Shadow_Straight->AddInstances(shadow_staright_arrya_transform, false, false);

	//2. Shadow Straight Top

	FVector shadow_straight_top_location(0.0, (width - 2.0) * 50.0, height * 100.0);
	FVector shadow_straight_top_scale(scale_x, 1.0, (width - 2.0) / 5.0);

	FTransform shadow_straight_top(FRotator(0.0, 0.0, -90.0), shadow_straight_top_location, shadow_straight_top_scale);

	The_ISM_Shadow_Straight_Top->AddInstance(shadow_straight_top, false);

	//3. Shadow Round
	//3.1 Shadow Round transform 1
	FVector shadow_round_location0(0.0, width * 50.0, (height - 1.0) * 100.0);
	FVector shadow_round_scale0(scale_x, 1.0, 1.0);

	FTransform shadow_round_transform0(FRotator(EForceInit::ForceInit), shadow_round_location0, shadow_round_scale0);

	//3.2 Shadow Round transform 2
	FVector shadow_round_location1 = shadow_round_location0;
	shadow_round_location1.Y = shadow_round_location1.Y * -1.0 + 100.0;
	shadow_round_location1.Z += 100.0;

	FTransform shadow_round_transform1(FRotator(0.0, 0.0, -90.0), shadow_round_location1, shadow_round_scale0);

	shadow_round_arrya_transform.Reset();
	shadow_round_arrya_transform.Add(shadow_round_transform0);
	shadow_round_arrya_transform.Add(shadow_round_transform1);

	The_ISM_Shadow_Round->AddInstances(shadow_round_arrya_transform, false, false);

	return true;
}

void UDemo_Display_Component::Make_Display(double height, double depth, double width, bool &add_curve, double &lenght_top_panel, double &lenght_down_panel, FTransform &top_panel_transform, FTransform &down_panel_transform)
{
	double y = (width - 2.0) / 2.0;
	double panel_height = (height / 2.0);
	double panel_depth = (depth / 2.0);
	if (height < 2.0 || depth < 2.0)
	{
		add_curve = true;
	}
	else
	{
		add_curve = false;

	}

	FTransform curve_transform;
	TArray<FTransform> curve_edge_array_transform;

	//1. Curve transform
	//1.1 Curve transform
	FVector curve_scale(1.0, y, 1.0);
	curve_transform = FTransform(FRotator(EForceInit::ForceInit), FVector(EForceInit::ForceInit), curve_scale);

	The_ISM_Curve->AddInstance(curve_transform, false);

	//1.2 Curve Edge Array Transform
	//1.3 Curve Edge transform 1
	FTransform curve_edge_transform0(FRotator(EForceInit::ForceInit), FVector(0.0, y * 100.0, 0.0), FVector(1.0, 1.0, 1.0));

	//1.4 Curve Edge transform 2
	FTransform curve_edge_transform1(FRotator(90.0, 360.0, 180.0), FVector(0.0, y * -100.0, 0.0), FVector(1.0, 1.0, 1.0));

	curve_edge_array_transform.Reset();
	curve_edge_array_transform.Add(curve_edge_transform0);
	curve_edge_array_transform.Add(curve_edge_transform1);

	The_ISM_Curve_Edge->AddInstances(curve_edge_array_transform, false, false);

	//2. Lenght and Transform Panel
	//2.1 Lenght Top Panel
	if (depth >= 2.0)
	{
		if (height >= 2.0)
		{
			lenght_top_panel = height;
			lenght_down_panel = depth;
			top_panel_transform = FTransform(FRotator(EForceInit::ForceInit), FVector(0.0, 0.0, -100.0), FVector(1.0, 1.0, 1.0));
			down_panel_transform = FTransform(FRotator(90.0, 180.0, 0.0), FVector(0.0, 0.0, -100.0), FVector(1.0, 1.0, 1.0));
		}
		else
		{
			lenght_top_panel = panel_depth + 1.0;
			lenght_down_panel = panel_depth + 1.0;
			top_panel_transform = FTransform(FRotator(-90.0, 0.0, 0.0), FVector(0.0, 0.0, panel_depth * 100.0), FVector(1.0, 1.0, 1.0));
			down_panel_transform = FTransform(FRotator(90.0, 180.0, 0.0), FVector(0.0, 0.0, panel_depth * -100.0), FVector(1.0, 1.0, 1.0));
		}
	}
	else
	{
		lenght_top_panel = panel_height + 1.0;
		lenght_down_panel = panel_height + 1.0;
		top_panel_transform = FTransform(FRotator(EForceInit::ForceInit), FVector(0.0, 0.0, panel_height * -100.0), FVector(1.0, 1.0, 1.0));
		down_panel_transform = FTransform(FRotator(180.0, 180.0, 0.0), FVector(0.0, 0.0, panel_height * 100.0), FVector(1.0, 1.0, 1.0));
	}

}

void UDemo_Display_Component::Make_Scalavle_Panel(FTransform base_position, double lenght, double width)
{
	double y = (width - 2.0) / 2.0;
	double z = (lenght - 2.0) / 2.0;
	double location_z = (lenght - 2.0) * 100.0;
	TArray<FTransform> corner_array_transform;

	//1. Main Relative transform
	FTransform main_transform(FRotator(EForceInit::ForceInit), FVector(0.0, 0.0, 0.0), FVector(1.0, y, z));
	main_transform = main_transform.GetRelativeTransform(base_position);

	The_ISM_Main->AddInstance(main_transform);

	//2. Corner Relative transform
	//2.1 Corner Relative transform1
	FTransform corner_transform0(FRotator(EForceInit::ForceInit), FVector(0.0, y * 100.0, location_z), FVector(1.0, 1.0, 1.0));
	corner_transform0 = corner_transform0.GetRelativeTransform(base_position);

	//2.2 Corner Relative transform2
	FTransform corner_transform1(FRotator(0.0, 0.0, -90.0), FVector(0.0, y * -100.0, location_z), FVector(1.0, 1.0, 1.0));
	corner_transform1 = corner_transform1.GetRelativeTransform(base_position);

	corner_array_transform.Add(corner_transform0);
	corner_array_transform.Add(corner_transform1);

	The_ISM_Corner->AddInstances(corner_array_transform, false, false);

	//3. Side Relative transform
	//3.1 Side Relative transform1
	FTransform side_transform1(FRotator(0.0, 0.0, 90.0), FVector(0.0, y * 100.0, z * 100.0), FVector(1.0, z, 1.0));
	side_transform1 = side_transform1.GetRelativeTransform(base_position);

	//3.2 Side Relative transform2
	FTransform side_transform2(FRotator(0.0, 0.0, -90.0), FVector(0.0, y * -100.0, z * 100.0), FVector(1.0, z, 1.0));
	side_transform2 = side_transform2.GetRelativeTransform(base_position);

	//3.3 Side Relative transform3
	FTransform side_transform3(FRotator(EForceInit::ForceInit), FVector(0.0, 0.0, location_z), FVector(1.0, y, 1.0));
	side_transform3 = side_transform3.GetRelativeTransform(base_position);

	Scale_Safe_Instance(side_transform1);
	Scale_Safe_Instance(side_transform2);
	Scale_Safe_Instance(side_transform3);
}

void UDemo_Display_Component::Scale_Safe_Instance(FTransform side_transform)
{
	if (side_transform.GetScale3D().X > 0 && side_transform.GetScale3D().Y > 0 && side_transform.GetScale3D().Z > 0)
	{
		The_ISM_Side->AddInstance(side_transform, false);
	}
}

void UDemo_Display_Component::Setup_ISM(UInstancedStaticMeshComponent *ism_component, UMaterialInstanceDynamic *new_material, FDisplay_ISM_Description &ism_descriprion)
{
	ism_component->SetMobility(EComponentMobility::Static);
	if (ism_descriprion.Mesh != 0)
	{
		ism_component->SetStaticMesh(ism_descriprion.Mesh);
	}
	if (new_material != 0)
	{
		ism_component->SetMaterial(0, new_material);
	}
	ism_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	ism_component->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	if (!ism_component->IsRegistered())
	{
		ism_component->RegisterComponent();
	}
}
