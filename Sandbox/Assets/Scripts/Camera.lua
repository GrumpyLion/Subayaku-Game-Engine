function Init()
	xSpeed = 0
	ySpeed = 0
	m_Radius = 150
	OldHeight = 0
	m_Offset = Vector3f.new(0,0,0)
end

function Update()
	xSpeed = xSpeed * 0.8
	ySpeed = ySpeed * 0.8
	
	-- Calculating the forward vector
	mat = Parent:GetModelTransform()
	
	forward = Vector3f.new(mat.m13, mat.m23, mat.m33)
	up = Vector3f.new(mat.m12, mat.m22, mat.m32)
	strafe = Vector3f.new(mat.m11, mat.m21, mat.m31)
	
	-- W
	if Keyboard:IsKeyDown(87) then
		m_Offset.x = m_Offset.x - (forward.x + up.x) * 5
		m_Offset.z = m_Offset.z - (forward.z + up.z) * 5   
	end

	-- S
	if Keyboard:IsKeyDown(83) then
		m_Offset.x = m_Offset.x + (forward.x + up.x) * 5
		m_Offset.z = m_Offset.z + (forward.z + up.z) * 5   
	end
	
	-- A
	if Keyboard:IsKeyDown(65) then
		m_Offset.x = m_Offset.x + strafe.x * 5
		m_Offset.z = m_Offset.z + strafe.z * 5    
	end
	
	-- D
	if Keyboard:IsKeyDown(68) then	
		m_Offset.x = m_Offset.x - strafe.x * 5
		m_Offset.z = m_Offset.z - strafe.z * 5    
	end
	
	if Mouse.LeftButton then
		xSpeed = xSpeed + Mouse.xD * 0.025
		ySpeed = ySpeed + Mouse.yD * 0.025
	end 
	
	if Mouse.RightButton then
		m_Radius = m_Radius + Mouse.yD
	end 	
	
	Parent.Transform.Rotation.x = Parent.Transform.Rotation.x + ySpeed
	Parent.Transform.Rotation.y = Parent.Transform.Rotation.y + xSpeed
	
	xOffset = CalculateHorizontalDistance() * math.sin(math.rad(Parent.Transform.Rotation.y))
	zOffset = CalculateHorizontalDistance() * math.cos(math.rad(Parent.Transform.Rotation.y))
	
	Parent.Transform.Position.x = xOffset + m_Offset.x
	Parent.Transform.Position.y = OldHeight + CalculateVerticalDistance()
	Parent.Transform.Position.z = -zOffset + m_Offset.z
end

function CalculateHorizontalDistance()
	return -m_Radius * math.cos(math.rad(Parent.Transform.Rotation.x))
end

function CalculateVerticalDistance()
	return -m_Radius * math.sin(math.rad(Parent.Transform.Rotation.x))
end