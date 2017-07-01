function Init()	
	m_Counter = 0
end

function Update()
	m_Counter = m_Counter + 0.01
	Parent.Transform.Position.y = Parent.Transform.Position.y + math.sin(m_Counter) * 0.01
	Parent.Transform.Position.z = Parent.Transform.Position.z + math.sin(m_Counter) * 0.025
end