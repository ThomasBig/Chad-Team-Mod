class RAD_RadiationDamageEffect : SCR_PersistentDamageEffect
{
	
	[Attribute(desc: "Configuration of how the damage effects the character.")]
	protected ref RAD_RadiationDamageConfig m_RadiationDamageConfiguration;
	
	ref array<RAD_RadiationDamageArea> m_aRadiationAreas = {};
	protected float m_fRadiationPoisoningLevel = 0; //! Amount of accumulated radiation damage consumed by the hit zone (abstract unit)
	protected float m_fRadiationPoisoningLevelDecay = 0; // Amount of radiation damage (abstract unit) the body self repair per seconds
	protected const float DAMAGE_PER_POISON_LEVEL = 1;
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
			
			DamageAreaShapeSphere sphere = DamageAreaShapeSphere.Cast(source.GetShape());
			float maxRange = sphere.GetDiameter()/2;
			float baseDistance = vector.Distance(source.GetParent().GetOrigin(), source.GetParent().GetOrigin());
			m_lastInstigator = source.GetParent();
			
			int soucreTraceIndex = tracedEntities.Get(tracedEntities.Count()-1);
			float distaceToSource = baseDistance - baseDistance * tracedDistances.Get(soucreTraceIndex);
			
			m_fRadiationPoisoningLevel += m_RadiationDamageConfiguration.m_fPoisonLevelPerEmition * source.m_fEmissionRate * 1/(distaceToSource*distaceToSource);
		}
		
		// Radiation Poisoning Decay (linear)
		float decay = timeSlice/m_RadiationDamageConfiguration.m_fTimeToCurePoisonLevel;
		m_fRadiationPoisoningLevel = Math.Max(m_fRadiationPoisoningLevel - decay, 0);
		
		// Damage to the hit zone
		float damagePercPerPoisonLevel = timeSlice/m_RadiationDamageConfiguration.m_fTimeToKillPerPoisonLevel;
		float damageAmount = m_fRadiationPoisoningLevel * damagePercPerPoisonLevel * affectedHitZone.GetMaxHealth();
		
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
