index = 0

function Init()
	-- Camera Object
	trans = Transform.new();
	trans.Rotation = Vector3f.new(-40, 40, 0)
	
	gameObject = Scene:InstantiateGameObject("Camera", trans, true)
	
	script = gameObject:AddScriptComponent()
	script:Initialize("Assets/Scripts/Camera.lua")
	
	camera = gameObject:AddCameraComponent();
	camera:Initialize(80.0, 1, 5000.0)
	
	--image = Image.new("Assets/Textures/TreeMap.tga");	
	--noiseImage = Image.new("Assets/Textures/Noise.tga");	
	
	-- Seating
	
	trans.Position = Vector3f.new(0, 14.5, 0)
	trans.Rotation = Vector3f.new(2,0,-2)
	trans.Scale = Vector3f.new(0.1, 0.1, 0.1);
	
	gameObject = Scene:InstantiateGameObject("Seating", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader(0, "Small.vs")
	material:AddShader(0, "Small.fs")
	material:AddShader(1, "Shadow/Depth.vs")
	material:AddShader(1, "Shadow/Depth.fs")
	
	texDesc = TextureDesc.new()
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uTexture"
	texDesc.FilePath = "Assets/Textures/Diffuse.tga"
	material:AddTexture(texDesc)
	
	mesh:Initialize("Assets/Models/Seating.obj", material)
	
	-- Boat
	
	trans.Position = Vector3f.new(850, 0.5, 0)
	trans.Rotation = Vector3f.new(0, 30, 0)
	trans.Scale = Vector3f.new(0.2, 0.2, 0.2);
	
	gameObject = Scene:InstantiateGameObject("Boat", trans, true)
	
	script = gameObject:AddScriptComponent()
	script:Initialize("Assets/Scripts/Boat.lua")
	
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader(0, "Small.vs")
	material:AddShader(0, "Small.fs")
	material:AddShader(1, "Shadow/Depth.vs")
	material:AddShader(1, "Shadow/Depth.fs")
	
	texDesc = TextureDesc.new()
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uTexture"
	texDesc.FilePath = "Assets/Textures/Diffuse.tga"
	material:AddTexture(texDesc)
	
	mesh:Initialize("Assets/Models/Boat.obj", material)
	
	-- Planks
	
	trans.Position = Vector3f.new(790, 0, 0)
	trans.Scale = Vector3f.new(0.2, 0.2, 0.2);
	trans.Rotation = Vector3f.new(0, 0, 0)
	
	gameObject = Scene:InstantiateGameObject("Plank", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader(0, "Small.vs")
	material:AddShader(0, "Small.fs")
	material:AddShader(1, "Shadow/Depth.vs")
	material:AddShader(1, "Shadow/Depth.fs")
	
	texDesc = TextureDesc.new()
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uTexture"
	texDesc.FilePath = "Assets/Textures/Diffuse.tga"
	material:AddTexture(texDesc)
	
	mesh:Initialize("Assets/Models/Plank.obj", material)
	
	trans.Rotation = Vector3f.new(0, 0, 0)
	for index=0, 500, 1 do
	
		scale = math.random() * 0.25 + 0.2
		trans.Rotation = Vector3f.new(math.random(-2, 2), math.random(0, 360), math.random(-2, 2))
		trans.Scale = Vector3f.new(scale, scale, scale);
		trans.Position = Vector3f.new(math.random(0, 2000), 35, math.random(0, 2000))
		
		--if image:GetPixelAt(trans.Position.x, trans.Position.z).x > 250 then
			
			--trans.Position.y = (noiseImage:GetPixelAt(trans.Position.x, trans.Position.z).x /255) * 50 - 26
			trans.Position.y = 15
			trans.Position.x = trans.Position.x - 1024
			trans.Position.z = trans.Position.z - 1024
			
			gameObject = Scene:InstantiateGameObject(tostring(index), trans, false)
			mesh = gameObject:AddMeshRenderer()
			material = mesh:SetNewMaterial()
			
			material:AddShader(0, "Tree.vs")
			material:AddShader(0, "Tree.fs")
			
			material:AddShader(1, "Shadow/DepthTree.vs")
			material:AddShader(1, "Shadow/DepthTree.fs")
			
			texDesc.RegisterIndex = 0
			texDesc.UniformName = "uTexture"
			texDesc.FilePath = "Assets/Textures/Diffuse.tga"
			material:AddTexture(texDesc)
			
			texDesc.RegisterIndex = 1
			texDesc.UniformName = "uLeaves"
			texDesc.FilePath = "Assets/Textures/Leaves.tga"
			material:AddTexture(texDesc)
			
			mesh:Initialize("Assets/Models/Tree.obj", material)
			
		--end
	end 
	
	-- Terrain	
	texDesc = TextureDesc.new()
	meshDesc = MeshDesc.new()
	
	trans = Transform.new()
	trans.Scale = Vector3f.new(15, 15, 15)
	
	gameObject = Scene:InstantiateGameObject("Terrain", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader(0, "Terrain.vs")
	material:AddShader(0, "Terrain.fs")
	
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uNoise"
	texDesc.FilePath = "Assets/Textures/Noise.tga"
	material:AddTexture(texDesc)
	
	texDesc.RegisterIndex = 1
	texDesc.UniformName = "uColor"
	texDesc.FilePath = "Assets/Textures/Colormap.tga"
	material:AddTexture(texDesc)
	
	-- Primitives is static
	Primitives.GetPlaneTri(meshDesc, 150, 0, 150)
	meshDesc.HasIndices = true
	meshDesc.FilePath = "Primitive"
	meshDesc.ShouldCull = true
	
	mesh:Initialize(meshDesc, material)
	
	-- Water	
	texDesc = TextureDesc.new()
	meshDesc = MeshDesc.new()
	
	trans = Transform.new()
	trans.Scale = Vector3f.new(15, 15, 15)
	
	gameObject = Scene:InstantiateGameObject("Water", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader(0, "Water.vs")
	material:AddShader(0, "Water.fs")
	
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uNoise"
	texDesc.FilePath = "Assets/Textures/Noise.tga"
	material:AddTexture(texDesc)
	
	texDesc.RegisterIndex = 1
	texDesc.UniformName = "uColor"
	texDesc.FilePath = "Assets/Textures/Colormap.tga"
	material:AddTexture(texDesc)
	
	-- Primitives is static
	Primitives.GetPlaneTri(meshDesc, 200, 0, 200)
	meshDesc.HasIndices = true
	meshDesc.FilePath = "Primitive 200 200"
	
	mesh:Initialize(meshDesc, material)
	
	trans = Transform.new()
	trans.Position = Vector3f.new(0, -15, 0)
	trans.Scale = Vector3f.new(15, 1, 15)
	
	gameObject = Scene:InstantiateGameObject("GROUND FOR SHADOW MAPPING", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader(1, "Shadow/Depth.vs")
	material:AddShader(1, "Shadow/Depth.fs")
	
	-- Primitives is static
	Primitives.GetPlaneTri(meshDesc, 1, 1, 1)
	meshDesc.HasIndices = true
	meshDesc.ShouldCull = false
	meshDesc.FilePath = "Primitive 1 1"
	
	mesh:Initialize(meshDesc, material)
	
end

function Update()

end