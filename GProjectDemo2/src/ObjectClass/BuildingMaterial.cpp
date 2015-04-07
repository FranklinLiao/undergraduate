#include "stdafx.h"
#include "BuildingMaterial.h"

BuildingMaterial BuildingMaterial::getObject(vector<string> param) {
	BuildingMaterial buildingMaterial = BuildingMaterial(param);
	return buildingMaterial;
}

vector<BuildingMaterial> BuildingMaterial::getObjectSet(vector<vector<string>> param) {
	vector<BuildingMaterial> buildingMaterialSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		BuildingMaterial buildingMaterial = BuildingMaterial::getObject(*iter++);
		buildingMaterialSet.push_back(buildingMaterial);
	}
	return buildingMaterialSet;
}