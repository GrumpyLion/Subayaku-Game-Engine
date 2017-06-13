function Init()
	xSpeed = 0
	ySpeed = 0
	m_Radius = 350
	OldHeight = Parent.Transform.Position.y
end

function Update()
	xSpeed = xSpeed * 0.8
	ySpeed = ySpeed * 0.8
	
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
	
	Parent.Transform.Position.x = xOffset
	Parent.Transform.Position.y = OldHeight + CalculateVerticalDistance()
	Parent.Transform.Position.z = -zOffset 
end

function CalculateHorizontalDistance()
	return -m_Radius * math.cos(math.rad(Parent.Transform.Rotation.x))
end

function CalculateVerticalDistance()
	return -m_Radius * math.sin(math.rad(Parent.Transform.Rotation.x))
end