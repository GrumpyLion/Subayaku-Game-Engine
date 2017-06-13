function Init()

	-- Camera Object
	local trans = Transform.new();
	local gameObject = Scene:InstantiateGameObject("Camera", trans)
	
	local script = gameObject:AddScriptComponent()
	script:Initialize(gameObject, "Assets/Scripts/Camera.lua")
	
	local camera = gameObject:AddCameraComponent();
	camera:Initialize(gameObject, 80.0, 1, 5000.0)
	
	-- Test Mesh (Rotation Teapot)
	local mesh = gameObject:AddMeshRenderer()
	local material = mesh:SetNewMaterial()
	
	material:AddShader("Small.vs")
	material:AddShader("Small.fs")
	
	mesh:Initialize(gameObject, "Assets/Models/teapot.obj", material)

	-- Terrain	
	local texDesc = TextureDesc.new()
	local meshDesc = MeshDesc.new()
	
	trans = Transform.new()
	trans.Scale = Vector3f.new(15, 15, 15)
	
	gameObject = Scene:InstantiateGameObject("Terrain", trans)
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
	
	gameObject = Scene:InstantiateGameObject("Water", trans)
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