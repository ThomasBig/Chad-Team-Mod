class RAD_RadiationDamageEffect : SCR_PersistentDamageEffect
{
	protected static ref RAD_RadiationDamageConfig m_sRadiationDamageConfiguration;
	const static ResourceName RADIATION_CONFIG_RESOUCE_NAME = "{2A2D5A08EBAE5C57}Configs/Radiation/RadiationDamageConfiguration.conf";
	
	ref array<RAD_RadiationDamageArea> m_aRadiationAreas = {};
	protected float m_fRadiationPoisoningLevel = 0; //! Amount of accumulated radiation damage consumed by the hit zone (abstract unit)
	protected float m_fRadiationPoisoningLevelDecay = 0; // Amount of radiation damage (abstract unit) the body self repair per seconds
	protected const float DAMAGE_PER_POISON_LEVEL = 1;
	protected const float EXPOSURE_PER_DISTACE = 1; 
	
	protected IEntity m_lastInstigator;
	
	//------------------------------------------------------------------------------------------------
	static RAD_RadiationDamageConfig GetRadiationDamageConfig()
	{
		if(!m_sRadiationDamageConfiguration)
		{
			Resource resource = BaseContainerTools.LoadContainer(RADIATION_CONFIG_RESOUCE_NAME);
			const BaseContainer container = resource.GetResource().ToBaseContainer();
			Managed containerInstance = BaseContainerTools.CreateInstanceFromContainer(container);
			
			m_sRadiationDamageConfiguration = RAD_RadiationDamageConfig.Cast(containerInstance);
		}
		
		return m_sRadiationDamageConfiguration;
	}
	
	//------------------------------------------------------------------------------------------------
	override event void EOnFrame(float timeSlice, SCR_ExtendedDamageManagerComponent dmgManager)
	{
		if (!dmgManager)
			return;
		
		HitZone affectedHitZone = GetAffectedHitZone();
		RAD_RadiationDamageConfig radConfig = GetRadiationDamageConfig();
		
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
			float maxRange = 20.000; //sphere.GetDiameter()
			float baseDistance = vector.Distance(source.GetParent().GetOrigin(), dmgManager.GetOwner().GetOrigin());
			m_lastInstigator = source.GetParent();
			
			int soucreTraceIndex = tracedEntities.Get(tracedEntities.Count()-1);
			float distaceToSource = Math.Max(baseDistance, 0.0001);
			float distanceScaler = Math.Min(1/(distaceToSource*distaceToSource), 1);
			
			// Increse the radiation poisoning level
			m_fRadiationPoisoningLevel += radConfig.m_fPoisonLevelPerEmition * source.m_fEmissionRate * distanceScaler;
		}
		
		// Radiation Poisoning Decay (linear)
		float decay = timeSlice / radConfig.m_fTimeToCurePoisonLevel;
		if (m_aRadiationAreas.IsEmpty())
			decay = 0.5*timeSlice;
		
		m_fRadiationPoisoningLevel = Math.Max(m_fRadiationPoisoningLevel - decay, 0);
		
		// Damage to the hit zone
		float damagePercPerPoisonLevel = timeSlice / radConfig.m_fTimeToKillPerPoisonLevel;
		float damageAmount = m_fRadiationPoisoningLevel * damagePercPerPoisonLevel * affectedHitZone.GetMaxHealth();
		
		//Attribute the instigator to the last source affecting the player
		affectedHitZone.HandleDamage(damageAmount, EDamageType.RADIATION, m_lastInstigator);
		
//#ifdef ENABLE_DIAG
//		DbgUI.Begin("Radiation");
//		DbgUI.Text(string.Format("Radiation Poison Level: %1", m_fRadiationPoisoningLevel));
//		DbgUI.End();		
//#endif
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
