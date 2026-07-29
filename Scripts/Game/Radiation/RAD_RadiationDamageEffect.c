class RAD_RadiationDamageEffect : SCR_PersistentDamageEffect
{
	ref array<IEntity> m_aRadiationAreas = {};
	protected float m_fRadiationPoisoningLevel = 0; //! Amount of accumulated radiation damage consumed by the hit zone (abstract unit)
	protected float m_fRadiationPoisoningLevelDecay = 5; // Amount of radiation damage (abstract unit) the body self repair per seconds
	
	//------------------------------------------------------------------------------------------------
	override event void EOnFrame(float timeSlice, SCR_ExtendedDamageManagerComponent dmgManager)
	{
		if (!dmgManager)
			return;
		
		HitZone affectedHitZone = GetAffectedHitZone();
		
		foreach (IEntity source : m_aRadiationAreas)
		{
			SCR_Trace sourceTrace = new SCR_Trace();
			array<IEntity> tracedEntities = {};
			array<GameMaterial> tracedMaterials = {};
			sourceTrace.TraceFromEntityToHitzone(source, dmgManager.GetOwner(), affectedHitZone, tracedEntities, tracedMaterials);
		}
		
		// Radiation Poisoning Decay
		
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
