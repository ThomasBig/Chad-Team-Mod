class RAD_RadiationDamageEffect : SCR_PersistentDamageEffect
{
	ref array<RAD_RadiationDamageArea> m_aRadiationAreas = {};
	protected float m_fRadiationPoisoningLevel = 0; //! Amount of accumulated radiation damage consumed by the hit zone (abstract unit)
	protected float m_fRadiationPoisoningLevelDecay = 0; // Amount of radiation damage (abstract unit) the body self repair per seconds
	protected const float DAMAGE_PER_POISON_LEVEL = 0;
	protected const float EXPOSURE_PER_DISTACE = 1; 
	
	protected IEntity m_lastInstigator;
	
	//------------------------------------------------------------------------------------------------
	override event void EOnFrame(float timeSlice, SCR_ExtendedDamageManagerComponent dmgManager)
	{
		if (!dmgManager)
			return;
		
		HitZone affectedHitZone = GetAffectedHitZone();
		
		foreach (RAD_RadiationDamageArea source : m_aRadiationAreas)
		{
			SCR_Trace sourceTrace = new SCR_Trace();
			array<IEntity> tracedEntities = {};
			array<GameMaterial> tracedMaterials = {};
			array<float> tracedDistances = {}; 
			sourceTrace.TraceFromEntityToEntity(source.GetParent(), dmgManager.GetOwner(), tracedEntities, tracedMaterials, tracedDistances);
			if(tracedEntities.IsEmpty())
				continue;
			
			m_lastInstigator = source.GetParent();
			
			int soucreTraceIndex = tracedEntities.Get(tracedEntities.Count()-1);
			float distaceToSource = tracedDistances.Get(soucreTraceIndex); // units?
			float exposureLevel = EXPOSURE_PER_DISTACE * distaceToSource * timeSlice; //db TODO: Change this for caluclation based on the trace
			
			m_fRadiationPoisoningLevel += exposureLevel;
		}
		
		// Radiation Poisoning Decay (linear)
		m_fRadiationPoisoningLevel = Math.Max(m_fRadiationPoisoningLevel - m_fRadiationPoisoningLevelDecay * timeSlice, 0);
		
		// Damage to the hit zone
		float damageAmount = m_fRadiationPoisoningLevel * DAMAGE_PER_POISON_LEVEL;
		
		//Attribute the instigator to the last source affecting the player
		affectedHitZone.HandleDamage(damageAmount, EDamageType.RADIATION, m_lastInstigator); 
	}
	
	//------------------------------------------------------------------------------------------------
	void AddRadiationAreas(notnull RAD_RadiationDamageArea area)
	{
		if (!m_aRadiationAreas.Contains(area))
		{
			m_aRadiationAreas.Insert(area);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void RemoveRadiationArea(notnull RAD_RadiationDamageArea area)
	{
		m_aRadiationAreas.RemoveItem(area);
	}
}
