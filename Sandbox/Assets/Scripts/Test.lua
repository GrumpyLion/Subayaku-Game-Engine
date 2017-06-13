function Init()
	Parent.Transform.Position.y = 150
	
	local gameObject = Scene:InstantiateGameObject("Camera", Parent.Transform)
	local script = gameObject:AddScriptComponent()
	script:Initialize(gameObject, "Assets/Scripts/Camera.lua")
	
	local camera = gameObject:AddCameraComponent();
	camera:Initialize(gameObject, 70.0, 1, 5000.0)
end

function Update()
end