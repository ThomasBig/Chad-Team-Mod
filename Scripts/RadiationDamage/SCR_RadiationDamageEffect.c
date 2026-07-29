class SCR_RadiationDamageEffect : PersistentDamageEffect
{
	ref array<ref IEntity> m_aRadiationAreas = {};
	
	//------------------------------------------------------------------------------------------------
	void AddRadiationAreas(IEntity entityArea)
	{
		if (!m_aRadiationAreas.Contains(entityArea))
		{
			m_aRadiationAreas.Insert(entityArea);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void RemoveRadiationArea(IEntity entityArea)
	{
		if (m_aRadiationAreas.Contains(entityArea))
		{
			m_aRadiationAreas.Remove(entityArea);
		}
	}
}
