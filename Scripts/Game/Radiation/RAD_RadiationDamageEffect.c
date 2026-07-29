class RAD_RadiationDamageEffect : SCR_PersistentDamageEffect
{
	ref array<IEntity> m_aRadiationAreas = {};
	protected float m_fRadiationPoisonLevel = 0; //! Amount of radiation damage consumed by the hit zone 
	
	//------------------------------------------------------------------------------------------------
	override event void EOnFrame(float timeSlice, SCR_ExtendedDamageManagerComponent dmgManager)
	{
		if (!dmgManager)
			return;
		
		HitZone affectedHitZone = GetAffectedHitZone();
		
		foreach (IEntity source : m_aRadiationAreas)
		{
			SCR_Trace sourceTrace = new SCR_Trace();
			
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void AddRadiationAreas(notnull IEntity entityArea)
	{
		if (!m_aRadiationAreas.Contains(entityArea))
		{
			m_aRadiationAreas.Insert(entityArea);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void RemoveRadiationArea(notnull IEntity entityArea)
	{
		m_aRadiationAreas.RemoveItem(entityArea);
	}
}
