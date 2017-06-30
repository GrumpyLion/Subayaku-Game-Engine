index = 0

function Init()
	-- Camera Object
	local trans = Transform.new();
	local gameObject = Scene:InstantiateGameObject("Camera", trans, true)
	
	local script = gameObject:AddScriptComponent()
	script:Initialize(gameObject, "Assets/Scripts/Camera.lua")
	
	local camera = gameObject:AddCameraComponent();
	camera:Initialize(gameObject, 80.0, 1, 5000.0)
	
	-- Test Mesh (Rotation Teapot)
	
	image = Image.new("Assets/Textures/TreeMap.tga");	
	noiseImage = Image.new("Assets/Textures/Noise.tga");	
	
	-- Bank
	
	trans.Position = Vector3f.new(0, 15.5, 0)
	trans.Scale = Vector3f.new(0.1, 0.1, 0.1);
	
	gameObject = Scene:InstantiateGameObject("Seating", trans, false)
	local mesh = gameObject:AddMeshRenderer()
	local material = mesh:SetNewMaterial()
	
	material:AddShader("Small.vs")
	material:AddShader("Small.fs")
	
	texDesc = TextureDesc.new()
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uTexture"
	texDesc.FilePath = "Assets/Textures/Diffuse.tga"
	material:AddTexture(texDesc)
	
	mesh:Initialize(gameObject, "Assets/Models/Seating.obj", material)
	
	-- Boat
	
	trans.Position = Vector3f.new(850, 1, 0)
	trans.Rotation = Vector3f.new(0, 30, 0)
	trans.Scale = Vector3f.new(0.1, 0.1, 0.1);
	
	gameObject = Scene:InstantiateGameObject("Boat", trans, false)
	local mesh = gameObject:AddMeshRenderer()
	local material = mesh:SetNewMaterial()
	
	material:AddShader("Small.vs")
	material:AddShader("Small.fs")
	
	texDesc = TextureDesc.new()
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uTexture"
	texDesc.FilePath = "Assets/Textures/Diffuse.tga"
	material:AddTexture(texDesc)
	
	mesh:Initialize(gameObject, "Assets/Models/Boat.obj", material)
	
	trans.Position = Vector3f.new(790, 0, 0)
	trans.Scale = Vector3f.new(0.15, 0.15, 0.15);
	trans.Rotation = Vector3f.new(0, 0, 0)
	
	gameObject = Scene:InstantiateGameObject("Plank", trans, false)
	local mesh = gameObject:AddMeshRenderer()
	local material = mesh:SetNewMaterial()
	
	material:AddShader("Small.vs")
	material:AddShader("Small.fs")
	
	texDesc = TextureDesc.new()
	texDesc.RegisterIndex = 0
	texDesc.UniformName = "uTexture"
	texDesc.FilePath = "Assets/Textures/Diffuse.tga"
	material:AddTexture(texDesc)
	
	mesh:Initialize(gameObject, "Assets/Models/Plank.obj", material)
	
	trans.Rotation = Vector3f.new(0, 0, 0)
	for index=0, 1500, 1 do
		trans.Scale = Vector3f.new(0.25, 0.25, 0.25);
		trans.Position = Vector3f.new(math.random(0, 2000), 35, math.random(0, 2000))
		
		if image:GetPixelAt(trans.Position.x, trans.Position.z).x > 250 then
			
			trans.Position.y = (noiseImage:GetPixelAt(trans.Position.x, trans.Position.z).x /255) * 50 - 26
			trans.Position.x = trans.Position.x - 1024
			trans.Position.z = trans.Position.z - 1024
			
			gameObject = Scene:InstantiateGameObject(tostring(index), trans, false)
			local mesh = gameObject:AddMeshRenderer()
			local material = mesh:SetNewMaterial()
			
			material:AddShader("Small.vs")
			material:AddShader("Small.fs")
			
			texDesc.RegisterIndex = 0
			texDesc.UniformName = "uTexture"
			texDesc.FilePath = "Assets/Textures/Diffuse.tga"
			material:AddTexture(texDesc)
			
			mesh:Initialize(gameObject, "Assets/Models/Tree.obj", material)
			
		end
	end 
	
	-- Terrain	
	texDesc = TextureDesc.new()
	meshDesc = MeshDesc.new()
	
	trans = Transform.new()
	trans.Scale = Vector3f.new(15, 15, 15)
	
	gameObject = Scene:InstantiateGameObject("Terrain", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader("Terrain.vs")
	material:AddShader("Terrain.fs")
	
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
	
	mesh:Initialize(gameObject, meshDesc, material)
	
	-- Water	
	texDesc = TextureDesc.new()
	meshDesc = MeshDesc.new()
	
	trans = Transform.new()
	trans.Scale = Vector3f.new(15, 15, 15)
	
	gameObject = Scene:InstantiateGameObject("Water", trans, false)
	mesh = gameObject:AddMeshRenderer()
	material = mesh:SetNewMaterial()
	
	material:AddShader("Water.vs")
	material:AddShader("Water.fs")
	
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
	
	mesh:Initialize(gameObject, meshDesc, material)
	
end

function Update()

end